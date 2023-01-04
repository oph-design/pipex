/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:13:10 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/04 10:42:25 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str_arr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free(ptr[i]);
	free(ptr);
	ptr = NULL;
}

void	change_src(char *file, int src)
{
	int	fd;

	fd = open(file, 0);
	dup2(fd, src);
	close(fd);
}

char	*get_path(char **env, char *arg)
{
	char	**paths;
	char	*res;

	res = NULL;
	while (!ft_strncmp(env, "PATH=", 5))
		env++;
	paths = ft_split(env + 5, ':');
	while (paths)
	{
		res = strdup(*paths);
		free(*paths);
		ft_strlcat(res, "/", ft_strlen(res) + 1);
		ft_strlcat(res, arg, ft_strlen(res) + ft_strlen(arg));
		if (!acccess(res, X_OK))
			return (free_str_arr(paths), res);
		free(res);
		paths++;
	}
	return (free(paths), NULL);
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
	change_src(argv[1], 1);
	child = fork();
	pipe(src);
	if (child == 0)
	{
		dup2(src[1], 1);
		close(src[0]);
		exec_cmd(argv[4], env);
		change_src(argv[5], 0);
	}
	else
	{
		dup2(src[0], 0);
		close(src[1]);
		exec_cmd(argv[3], env);
	}
	return (0);
}
