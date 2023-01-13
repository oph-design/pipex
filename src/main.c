/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:13:10 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/13 13:43:26 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	change_src(char *file, int src)
{
	int	fd;

	if (src == 1)
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
		ft_error(ft_strjoin("command not found: ", cmd[0]), 2);
}

void	pipex(int *src, int fd, char **argv, char **env)
{
	int		i;
	pid_t	pid;

	i = 1;
	while (argv[++i + 1] != NULL)
	{
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
		if (pipe(src))
			ft_error("piping failed", 0);
		fd = 0;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int	fd;
	int	src[2];

	if (argc != 5)
		return (ft_putendl_fd("pipex: wrong number of args", 2), 0);
	fd = change_src(argv[1], 0);
	if (pipe(src))
		ft_error("piping failed", 0);
	pipex(src, fd, argv, env);
	return (0);
}
