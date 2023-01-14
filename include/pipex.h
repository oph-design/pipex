/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:53 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/14 15:35:30 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

void	err(char *mess, int exit_code, char **cmd);
char	*format_cmd(char *cmd);
char	**join_cmd(char **str);
char	*format_ehre(char *cmd);

#endif
