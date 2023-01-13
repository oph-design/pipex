/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:44:45 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/13 17:51:14 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	change_src(char *file, int src)
{
	int			fd;
	static int	append = 0;

	if (!ft_strncmp(file, "here_doc", 9))
		return (append = 1, 1);
	if (src == 1 && append == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (src == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd == -1)
		return (fd);
	dup2(fd, src);
	close(fd);
	return (fd);
}

char	*get_path(char **env, char *arg)
{
	char	**paths;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	paths = ft_split(*env + 5, ':');
	while (paths[i] != NULL)
	{
		res = ft_strjoin(paths[i], "/");
		res = ft_strjoin_alt(res, arg);
		if (!access(res, X_OK))
			return (ft_free_arr(paths), res);
		free(res);
		i++;
	}
	return (ft_free_arr(paths), NULL);
}

void	exec_cmd(char **argv, char **env, int *src, int i)
{
	char	**cmd;
	char	*err;
	char	*path;

	err = NULL;
	path = argv[i];
	cmd = ft_split(format_cmd(argv[i]), ' ');
	if (cmd[3])
		cmd = join_cmd(cmd);
	dup2(src[1], 1);
	if (argv[i + 2] == NULL)
		change_src(argv[i + 1], 1);
	close(src[1]);
	close(src[0]);
	if (access(argv[i], X_OK) < 0)
		path = get_path(env, cmd[0]);
	if (execve(path, cmd, env) == -1)
	{
		err = ft_strjoin("pipex: command not found: ", cmd[0]);
		ft_free_arr(cmd);
		ft_putendl_fd(err, 2);
		exit(2);
	}
}

void	pipex(int fd, char **argv, char **env)
{
	int		i;
	pid_t	pid;
	int		src[2];

	i = 1;
	while (argv[++i + 1] != NULL)
	{
		if (pipe(src))
			ft_error("piping failed", 0);
		pid = fork();
		if (pid == -1)
			ft_error("forking failed", 0);
		if (pid == 0 && fd == -1)
			ft_error(ft_strjoin("no such file or directory: ", argv[1]), 1);
		else if (pid == 0)
			exec_cmd(argv, env, src, i);
		dup2(src[0], 0);
		close(src[0]);
		close(src[1]);
		waitpid(pid, NULL, WNOHANG);
		fd = 0;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int	fd;

	i = 1;
	if (argc < 3 || (!ft_strncmp(argv[1], "here_doc", 9) && argc < 4))
		return (ft_putendl_fd("pipex: wrong number of args", 2), 0);
	if (ft_strncmp(argv[1], "here_doc", 9))
		fd = change_src(argv[1], 0);
	else
		fd = here_doc(argv++);
	pipex(fd, argv, env);
	return (0);
}
