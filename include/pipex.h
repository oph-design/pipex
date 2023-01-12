/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:53 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/12 13:31:48 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

void	ft_error(char *mess, int exit_code, int fd);
char	*format_cmd(char *cmd);
char	**join_cmd(char **str);

#endif
