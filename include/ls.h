/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:12:52 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/03 00:06:18 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libalgorithm.h"
# include "libstring.h"
# include "libstd.h"
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>

typedef struct	s_ls
{
	char		**dirs;
	char		**files;
	t_u_char	flags[120];
}	t_ls;

/*
**	dirent
*/

int	is_dir(char *filename);
int	is_file(char *filename);

#endif
