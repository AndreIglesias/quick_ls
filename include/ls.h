/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:12:52 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/04 20:41:55 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libalgorithm.h"
# include "libstring.h"
# include "libstd.h"
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>

# define WACCESS "ft_ls: cannot access '%s': %s\n"

typedef struct s_ls
{
	char		**dirs;
	size_t		size_d;
	char		**files;
	size_t		size_f;
	t_u_char	flags[120];
}	t_ls;

void	destructor(void)__attribute__((destructor));

/*
**	dirent
*/

int		is_dir(char *filename);
int		is_file(char *filename);
char	file_type(mode_t st_mode);
void	print_element(char *cont, t_u_char *flags);
void	element_color(char *cont, struct stat buf);
/*
**	eval
*/

void	ft_ls(t_ls *ls);

/*
**		sort
*/

void	strins(char ***array, char **str, size_t pos, size_t size);
int		alpha_cmp(char *a, char *b);
int		alpha_rev(char *a, char *b);
int		time_cmp(char *a, char *b);
int		time_rev(char *a, char *b);

#endif
