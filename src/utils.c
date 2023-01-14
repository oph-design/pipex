/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:36:05 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/14 16:09:24 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err(char *mess, int exit_code, char **cmd)
{
	char	*err;

	if (cmd != NULL)
		ft_free_arr(cmd);
	err = ft_strjoin("pipex: ", mess);
	ft_putendl_fd(err, 2);
	free(mess);
	free(err);
	exit(exit_code);
}

char	*format_cmd(char *cmd)
{
	if (!ft_strncmp(cmd, "awk ", 4))
	{
		cmd[4] = ' ';
		cmd[ft_strlen(cmd) - 1] = ' ';
		ft_swap(cmd, '\\', ' ');
		return (cmd);
	}
	ft_swap(cmd, '\"', ' ');
	ft_swap(cmd, '\'', ' ');
	return (cmd);
}

char	**join_cmd(char **cmd)
{
	char	**res;
	int		i;
	char	*tmp;

	if (!cmd)
		return (NULL);
	i = 1;
	res = malloc(3 * sizeof(char *));
	res[0] = ft_strdup(cmd[0]);
	tmp = ft_strjoin_alt(ft_strdup(""), cmd[i++]);
	while (cmd[i] != NULL)
		tmp = ft_strjoin_alt(ft_strjoin_alt(tmp, " "), cmd[i++]);
	res[1] = tmp;
	res[2] = NULL;
	return (ft_free_arr(cmd), res);
}
