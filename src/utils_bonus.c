/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:44:41 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/13 12:45:09 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *mess, int exit_code)
{
	char	*err;

	err = ft_strjoin("pipex: ", mess);
	ft_putendl_fd(err, 2);
	free(mess);
	free(err);
	exit(exit_code);
}

char	*format_awk(char *cmd)
{
	char	*tmp;

	tmp = ft_strtrim(cmd, "awk ");
	tmp[0] = ' ';
	tmp[ft_strlen(tmp) - 1] = ' ';
	ft_swap(tmp, '\\', ' ');
	cmd = ft_strjoin("awk ", tmp);
	free(tmp);
	return (cmd);
}

char	*format_cmd(char *cmd)
{
	int		i;

	i = 0;
	if (!ft_strncmp(cmd, "awk ", 4))
		return (format_awk(cmd));
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

int	here_doc(char **argv)
{
	char	*str;
	int		fd;

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (close(fd), fd);
	str = get_next_line(0);
	while (strncmp(str, argv[2], ft_strlen(str) - 1))
	{
		free(str);
		str = get_next_line(0);
		ft_putstr_fd(str, fd);
	}
	dup2(fd, 0);
	close(fd);
	return (free(str), fd);
}
