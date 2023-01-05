/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:13:10 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/05 17:30:15 by oheinzel         ###   ########.fr       */
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
		fd = open(file, O_WRONLY);
	else
		fd = open(file, O_RDONLY);
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

void	exec_cmd(char *arg, char **env)
{
	char	**cmd;

	cmd = ft_split(arg, ' ');
	execve(get_path(env, cmd[0]), cmd, env);
	free_str_arr(cmd);
}

int	main(int argc, char *argv[], char *env[])
{
	int		src[2];
	pid_t	child;

	if (argc != 5)
		return (ft_putendl_fd("ERROR: Wrong arguments count", 2), 0);
	change_src(argv[1], 0);
	pipe(src);
	child = fork();
	if (child == 0)
	{
		dup2(src[0], 0);
		close(src[1]);
		change_src(argv[4], 1);
		exec_cmd(argv[3], env);
	}
	else
	{
		dup2(src[1], 1);
		close(src[0]);
		exec_cmd(argv[2], env);
	}
	return (0);
}
