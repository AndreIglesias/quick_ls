/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:53:36 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/09 23:59:08 by ciglesia         ###   ########.fr       */
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

char	*path_file(char *path, char *name, t_ls *ls)
{
	char	*tmp;
	char	*file;

	if ((path[ls->lslash + 1] && path[ls->lslash] == '/') || !ls->lslash)
	{
		file = ft_strjoin(path, "/");
		tmp = file;
	}
	else
		file = path;
	file = ft_strjoin(file, name);
	if ((path[ls->lslash + 1] && path[ls->lslash] == '/') || !ls->lslash)
		free(tmp);
	return (file);
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

	i = 0;
	if (ls->flags['l'])
		ft_printf("total %d\n", ls->total / 2);
	while (i < size)
	{
		file = path_file(path, content[i], ls);
		print_element(file, content[i], ls->flags, ls);
		if (!ls->flags['l'] && (i + 1 < size))
			ft_putstr("  ");
		else
			ft_putchar('\n');
		free(file);
		i++;
	}
}

int		measure_dir(char *name, char *path, t_ls *ls)
{
	struct stat			buf;
	char				*file;
	int					file_size;
	int					link_count;

	file = path_file(path, name, ls);
	ft_memset(&buf, 0, sizeof(struct stat *));
	if (lstat(file, &buf) == -1)
	{
		ft_printf_fd(2, WLSTAT, name, strerror(errno));
		exit_ls(ls, EXIT_FAILURE);
	}
	free(file);
	file_size = ft_sizei(buf.st_size);
	if (file_size > ls->file_size)
		ls->file_size = file_size;
	link_count = ft_sizei(buf.st_nlink);
	if (link_count > ls->link_count)
		ls->link_count = link_count;
	return (buf.st_blocks);
}

void	init_lsdir(char *path, t_ls *ls)
{
	ls->total = 0;
	ls->lslash = last_slash(path);
	ls->link_count = 0;
	ls->file_size = 0;
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
	init_lsdir(path, ls);
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
