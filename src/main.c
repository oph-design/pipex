/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:13:10 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/09 17:14:25 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str_arr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free(ptr[i++]);
	free(ptr);
	ptr = NULL;
}

void	change_src(char *file, int src)
{
	int	fd;

	if (src == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(strerror(13));
		close(fd);
		return ;
	}
	dup2(fd, src);
	close(fd);
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
			return (free_str_arr(paths), res);
		free(res);
		i++;
	}
	return (free_str_arr(paths), NULL);
}

void	exec_cmd(char **argv, char **env, int *src, int i)
{
	char	**cmd;
	char	*err;

	cmd = ft_split(argv[i], ' ');
	err = NULL;
	if (argv[i + 2] != NULL)
		dup2(src[1], 1);
	else
		change_src(argv[i + 1], 1);
	close(src[1]);
	close(src[0]);
	if (execve(get_path(env, cmd[0]), cmd, env) == -1)
	{
		err = ft_strjoin("pipex: command not found: ", cmd[0]);
		free_str_arr(cmd);
		ft_putendl_fd(err, 2);
		exit(0);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int		src[2];
	pid_t	pid;
	int		i;

	change_src(argv[1], 0);
	i = 1;
	while (++i < argc - 1)
	{
		pipe(src);
		ft_printf("%d", src[0]);
		pid = fork();
		if (pid == -1)
			ft_error(10);
		if (pid == 0)
			exec_cmd(argv, env, src, i);
		else
		{
			dup2(src[0], 0);
			close(src[0]);
			close(src[1]);
		}
	}
	return (0);
}
