/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:13:10 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/17 09:07:48 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*change_src(char *file, int src)
{
	int	fd;

	if (src == 0 && access(file, F_OK) < 0)
		return (ft_strjoin(file, ": No such file or directory "));
	if (src == 0 && access(file, R_OK) < 0)
		return (ft_strjoin("permission denied: ", file));
	if (src == 1 && !access(file, F_OK) && (access(file, W_OK) < 0))
		err(ft_strjoin("permission denied: ", file), 1, NULL);
	if (src == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_RDONLY);
	dup2(fd, src);
	close(fd);
	return (NULL);
}

char	*get_path(char **env, char *arg)
{
	char	**paths;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	paths = ft_split(*env + 5, ':');
	while (paths[i] != NULL)
	{
		res = ft_strjoin(paths[i], "/");
		res = ft_strjoin_alt(res, arg);
		if (!access(res, X_OK | F_OK))
			return (ft_free_arr(paths), res);
		free(res);
		i++;
	}
	return (ft_free_arr(paths), NULL);
}

void	exec_cmd(char **argv, char **env, int *src, int i)
{
	char	**cmd;
	char	*path;

	path = argv[i];
	cmd = ft_split(format_cmd(argv[i]), ' ');
	if (cmd[3])
		cmd = join_cmd(cmd);
	dup2(src[1], 1);
	if (argv[i + 2] == NULL)
		change_src(argv[i + 1], 1);
	close(src[1]);
	close(src[0]);
	if (access(path, X_OK | F_OK) < 0)
		path = get_path(env, cmd[0]);
	if (execve(path, cmd, env) == -1)
		err(ft_strjoin(cmd[0], ": command not found"), 127, cmd);
}

void	pipex(char *infile, char **argv, char **env)
{
	int		i;
	pid_t	pid;
	int		src[2];

	i = 1;
	while (argv[++i + 1] != NULL)
	{
		if (pipe(src))
			err(ft_strdup("piping failed"), 1, NULL);
		pid = fork();
		if (pid == -1)
			err(ft_strdup("forking failed"), 1, NULL);
		if (pid == 0 && infile != NULL)
			err(infile, 0, NULL);
		if (pid == 0)
			exec_cmd(argv, env, src, i);
		dup2(src[0], 0);
		close(src[0]);
		close(src[1]);
		waitpid(pid, NULL, WNOHANG);
		if (infile != NULL)
			free(infile);
		infile = NULL;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*infile;

	if (argc != 5)
		return (ft_putendl_fd("pipex: wrong number of args", 2), 0);
	if (*env == NULL)
		err("no neviroment", 1, NULL);
	infile = change_src(argv[1], 0);
	pipex(infile, argv, env);
	return (0);
}
