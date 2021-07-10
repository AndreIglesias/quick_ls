/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:12:52 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/11 00:21:25 by ciglesia         ###   ########.fr       */
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
# include <unistd.h>
# include <selinux/selinux.h>
# include <sys/xattr.h>
# include <sys/sysmacros.h>

# define WACCESS "ft_ls: cannot access '%s': %s\n"
# define WDIROP "ft_ls: cannot open directory '%s': %s\n"
# define WLSTAT "ft_ls: lstat '%s': %s\n"
# define NDIR 755//923

typedef struct s_ls
{
	char		**dirs;
	size_t		size_d;
	char		**files;
	size_t		size_f;
	t_u_char	flags[120];
	t_byte		filerr;
	int			total;
	int			lslash;
	int			link_count;
	int			file_size;
}	t_ls;

void	exit_ls(t_ls *ls, int status);

/*
**	dirent
*/

int		is_dot(char *name);
int		is_dir(char *filename);
int		is_file(char *filename);
char	file_type(mode_t st_mode);
void	print_element(char *cont, char *name, t_u_char *flags, t_ls *ls);
void	element_color(char *cont, char *name, struct stat buf, t_u_char *flags);

/*
**	eval
*/

int		measure_dir(char *name, char *path, t_ls *ls);
void	init_lsdir(t_ls *ls, int lslash);
char	*path_file(char *path, char *name, int lslash);
int		last_slash(char *str);
void	ft_ls(t_ls *ls);

/*
**		surfing
*/

void	print_dirs(char **dirs, t_u_char *flags, t_ls *ls);
void	print_dir(DIR *dir, char *path, t_u_char *flags, t_ls *ls);
void	print_files(char **files, t_u_char *flags, t_ls *ls);
void	print_recursive(char dirs[][256], size_t c, char *path, t_ls *ls);

/*
**		sort
*/

void	insert_content(char cont[][256], t_u_char *flags, size_t c, char *str);
int		alpha_cmp(char *a, char *b);
int		alpha_rev(char *a, char *b);
int		time_cmp(char *a, char *b);
int		time_rev(char *a, char *b);

#endif
