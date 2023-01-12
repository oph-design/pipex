/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:36:05 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/12 17:04:24 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *mess, int exit_code, int fd)
{
	if (fd > 0)
		close(fd);
	perror(ft_strjoin("piex: ", mess));
	free(mess);
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

	if (strncmp(argv[1], "here_doc", 9))
		return (0);
	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	str = get_next_line(0);
	while (strncmp(str, argv[2], ft_strlen(argv[2])))
	{
		free(str);
		str = get_next_line(0);
	}
	ft_putstr_fd(str, fd);
	return (free(str), 1);
}
