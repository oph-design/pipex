/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:36:05 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/10 18:01:43 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *mess, int exit_code, int fd)
{
	if (fd > 0)
		close(fd);
	perror(mess);
	exit(exit_code);
}

char	*append(char ***split)
{
	char	*res;

	res = strdup(**split);
	(*split)++;
	while (ft_strchr(**split, '"') == NULL && ft_strchr(**split, '\'') == NULL)
	{
		ft_printf("%s\n", **split);
		res = ft_strjoin_alt(ft_strjoin_alt(res, " "), **split);
		(*split)++;
	}
	if (**split != NULL)
		res = ft_strjoin_alt(ft_strjoin_alt(res, " "), **split);
	ft_swap(res, '\'', '\"');
	return (res);
}

char	**format_cmd(char **cmd)
{
	char	*tmp;
	char	**res;
	char	**arr;
	int		i;

	i = 0;
	tmp = NULL;
	arr = cmd;
	res = malloc(ft_arr_len(cmd) * sizeof(char *));
	while (*arr != NULL)
	{
		tmp = *arr;
		if (ft_strchr(*arr, '"') != NULL || ft_strchr(*arr, '\'') != NULL)
			tmp = append(&arr);
		res[i] = strdup(tmp);
		arr++;
		i++;
	}
	res[i] = NULL;
	ft_free_arr(cmd);
	return (res);
}
