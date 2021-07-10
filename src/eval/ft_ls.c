/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:53:36 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/10 23:51:39 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*path_file(char *path, char *name, int lslash)
{
	char	*tmp;
	char	*file;

	if ((path[lslash + 1] && path[lslash] == '/')
		|| (!lslash && path[0] != '/'))
	{
		file = ft_strjoin(path, "/");
		tmp = file;
	}
	else
		file = path;
	file = ft_strjoin(file, name);
	if ((path[lslash + 1] && path[lslash] == '/')
		|| (!lslash && path[0] != '/'))
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

int	measure_dir(char *name, char *path, t_ls *ls)
{
	struct stat			buf;
	char				*file;
	int					file_size;
	int					link_count;

	file = path_file(path, name, ls->lslash);
	ft_memset(&buf, 0, sizeof(struct stat *));
	if (lstat(file, &buf) == -1)
	{
		ft_printf_fd(2, WLSTAT, file, strerror(errno));
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

void	init_lsdir(t_ls *ls, int lslash)
{
	ls->total = 0;
	ls->lslash = lslash;
	ls->link_count = 0;
	ls->file_size = 0;
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
	print_dirs(ls->dirs, ls->flags, ls);
}
