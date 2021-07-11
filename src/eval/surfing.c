/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surfing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 23:50:33 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/11 17:19:55 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_files(char **files, t_u_char *flags, t_ls *ls)
{
	while (*files)
	{
		print_element(*files, *files, flags, ls);
		if (!flags['l'] && *(files + 1))
			ft_putstr("  ");
		else
			ft_putchar('\n');
		files++;
	}
}

void	print_content(char content[][256], char *path, t_ls *ls, size_t size)
{
	size_t	i;
	char	*file;

	i = 0;
	if (ls->flags['l'])
		ft_printf("total %d\n", ls->total / 2);
	while (i < size)
	{
		file = path_file(path, content[i], ls->lslash);
		print_element(file, content[i], ls->flags, ls);
		if (!ls->flags['l'] && (i + 1 < size))
			ft_putstr("  ");
		else
			ft_putchar('\n');
		free(file);
		i++;
	}
}

void	print_dir(DIR *dir, char *path, t_u_char *flags, t_ls *ls)
{
	char			content[NDIR][256];
	size_t			c;
	char			str[256];
	struct dirent	*dp;

	ft_bzero(content, sizeof(content));
	dp = readdir(dir);
	c = 0;
	init_lsdir(ls, last_slash(path));
	while (dp && c < NDIR)
	{
		str[0] = 0;
		ft_strcat(str, dp->d_name);
		if (str[0] != '.' || (str[0] == '.' && flags['a']))
		{
			insert_content(content, flags, c++, str);
			ls->total += measure_dir(str, path, ls);
		}
		dp = readdir(dir);
	}
	print_content(content, path, ls, c);
	if (flags['R'])
		print_recursive(content, c, path, ls);
}

void	print_recursive(char dirs[][256], size_t c, char *path, t_ls *ls)
{
	DIR		*dir;
	size_t	i;
	char	*file;

	i = 0;
	while (i < c)
	{
		file = path_file(path, dirs[i], last_slash(path));
		if (is_file(file) == -1 && is_dir(file) && !is_dot(dirs[i]))
		{
			dir = opendir(file);
			if (dir)
			{
				ft_printf("\n%s:\n", file);
				print_dir(dir, file, ls->flags, ls);
				closedir(dir);
			}
			else
				ft_printf_fd(2, WDIROP, *dirs, strerror(errno));
		}
		else if (is_file(file) <= 0 && !is_dot(dirs[i]))
			ft_printf_fd(2, WACCESS, file, strerror(errno));
		free(file);
		i++;
	}
}

void	print_dirs(char **dirs, t_u_char *flags, t_ls *ls)
{
	DIR	*dir;

	while (*dirs)
	{
		dir = opendir(*dirs);
		if (dir)
		{
			if (ls->size_f || ls->size_d > 1 || ls->filerr || flags['R'])
				ft_printf("%s:\n", *dirs);
			print_dir(dir, *dirs, flags, ls);
			closedir(dir);
		}
		else
			ft_printf_fd(2, WDIROP, *dirs, strerror(errno));
		dirs++;
		if (*dirs)
			ft_putchar('\n');
	}
}
