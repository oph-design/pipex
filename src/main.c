/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:13:10 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/04 09:26:29 by oheinzel         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
		return (ft_putendl_fd("ERROR: Too few arguments", 2), 0);
}
