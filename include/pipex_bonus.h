/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:53 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/13 17:50:21 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

void	ft_error(char *mess, int exit_code);
char	*format_cmd(char *cmd);
char	**join_cmd(char **str);
int		here_doc(char **argv);
int		change_src(char *file, int src);

#endif
