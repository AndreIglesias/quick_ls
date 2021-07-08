/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:53:36 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/08 23:27:05 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
**	TODO
**		files+dirs array
**		sort files, dirs, files+dirs array
*/

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

int	last_slash(char *str)
{
	int	i;
	int	slash;

	i = 0;
	slash = 0;
	while (str[i])
	{
		if (str[i] == '/')
			slash = i;
		i++;
	}
	return (slash);
}

void	print_content(char content[][256], char *path, t_ls *ls, size_t size)
{
	size_t	i;
	char	*file;
	char	*tmp;
	int		lslash;

	i = 0;
	lslash = last_slash(path);
	ft_printf("total\n");
	while (i < size)
	{
		if (content[i][0] != '.' || (content[i][0] == '.' && ls->flags['a']))
		{
			if ((path[lslash + 1] && path[lslash] == '/') || !lslash)
			{
				file = ft_strjoin(path, "/");
				tmp = file;
			}
			else
				file = path;
			file = ft_strjoin(file, content[i]);
			print_element(file, content[i], ls->flags, ls);
			if (!ls->flags['l'] && (i + 1 < size))
				ft_putstr("  ");
			else
				ft_putchar('\n');
			free(file);
			if ((path[lslash + 1] && path[lslash] == '/') || !lslash)
				free(tmp);
		}
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
	while (dp && c < NDIR)
	{
		str[0] = 0;
		ft_strcat(str, dp->d_name);
		if (flags['r'] && !flags['t'])
			binsert(content, str, c++, &alpha_rev);
		else if (flags['r'] && flags['t'])
			binsert(content, str, c++, &time_rev);
		else if (flags['t'])
			binsert(content, str, c++, &time_cmp);
		else
			binsert(content, str, c++, &alpha_cmp);
		dp = readdir(dir);
	}
	print_content(content, path, ls, c);
	// if c == NDIR -> print_dir
	// print_dirs
}

void	print_dirs(char **dirs, t_u_char *flags, t_ls *ls)
{
	DIR	*dir;

	while (*dirs)
	{
		//if (is_dir(dp->d_name))
		dir = opendir(*dirs);
		if (dir)
		{
			print_dir(dir, *dirs, flags, ls);
			closedir(dir);
		}
		else
			ft_printf_fd(2, WDIROP, *dirs, strerror(errno));
		dirs++;
	}
}

void	ft_ls(t_ls *ls)
{
	if (ls->flags['r'] && !ls->flags['t'])
	{
		strquick(ls->files, ls->size_f, &alpha_rev);
		strquick(ls->dirs, ls->size_d, &alpha_rev);
	}
	else if (ls->flags['r'] && ls->flags['t'])
	{
		strquick(ls->files, ls->size_f, &time_rev);
		strquick(ls->dirs, ls->size_d, &time_rev);
	}
	else if (ls->flags['t'])
	{
		strquick(ls->files, ls->size_f, &time_cmp);
		strquick(ls->dirs, ls->size_d, &time_cmp);
	}
	else
	{
		strquick(ls->files, ls->size_f, &alpha_cmp);
		strquick(ls->dirs, ls->size_d, &alpha_cmp);
	}
	print_files(ls->files, ls->flags, ls);
	print_dirs(ls->dirs, ls->flags, ls);//
}
