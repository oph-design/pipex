/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:44:41 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/15 18:05:40 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	here_doc(char **argv)
{
	char	*str;
	char	*limiter;
	int		src[2];

	if (pipe(src))
		err(ft_strdup("here_doc error"), 0, NULL);
	limiter = ft_strjoin(argv[2], "\n");
	str = get_next_line(0);
	if (str == NULL)
		err(ft_strdup("here_doc error"), 0, NULL);
	while (ft_strncmp(limiter, str, ft_strlen(str) - 1))
	{
		free(str);
		ft_putstr_fd(str, src[1]);
		str = get_next_line(0);
		if (str == NULL)
			err(ft_strdup("here_doc error"), 0, NULL);
	}
	dup2(src[0], 0);
	close(src[0]);
	close(src[1]);
	free(str);
	free(limiter);
}
