/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:44:45 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/18 10:42:47 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*change_src(char *file, int src)
{
	int			fd;
	static int	append = 0;

	if (!ft_strncmp(file, "here_doc", 9))
		return (append++, NULL);
	if (src == 0 && access(file, F_OK) < 0)
		return (ft_strjoin(file, ": No such file or directory "));
	if (src == 0 && access(file, R_OK) < 0)
		return (ft_strjoin("permission denied: ", file));
	if (src == 1 && !access(file, F_OK) && (access(file, W_OK) < 0))
		err(ft_strjoin("permission denied: ", file), 1, NULL);
	if (src == 1 && append == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (src == 1 && append == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (src == 0)
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
	if (*env == NULL)
		return (NULL);
	paths = ft_split(*env + 5, ':');
	while (paths && paths[i])
	{
		res = ft_strjoin(paths[i++], "/");
		res = ft_strjoin_alt(res, arg);
		if (!access(res, X_OK | F_OK))
			return (ft_free_arr(paths), res);
		free(res);
	}
	return (ft_free_arr(paths), NULL);
}

void	exec_cmd(char **argv, char **env, int *src, int i)
{
	char	**cmd;
	char	*path;

	path = argv[i];
	dup2(src[1], 1);
	close(src[1]);
	close(src[0]);
	if (argv[i + 2] == NULL)
		change_src(argv[i + 1], 1);
	cmd = ft_split(format_cmd(argv[i]), ' ');
	if (cmd[3])
		cmd = join_cmd(cmd);
	if (access(argv[i], X_OK | F_OK) < 0)
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
	while (argv[++i + 1])
	{
		if (pipe(src))
			err(ft_strdup("failed to create pipe"), 1, NULL);
		pid = fork();
		if (pid == -1)
			err(ft_strdup("failed o create subprocess"), 1, NULL);
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

	if (argc < 4 || (!ft_strncmp(argv[1], "here_doc", 9) && argc < 5))
		return (1);
	infile = change_src(argv[1], 0);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		here_doc(argv++);
	pipex(infile, argv, env);
	return (0);
}
