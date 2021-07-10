/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 23:44:07 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/10 21:33:53 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
**	ENOENT == errno -> dir doesn't exist
*/

int	is_dir(char *filename)
{
	DIR	*dir;

	dir = opendir(filename);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	is_file(char *filename)
{
	struct stat	buf;

	lstat(filename, &buf);
	return ((S_ISDIR(buf.st_mode) * -1) ^ (S_ISBLK(buf.st_mode) * 6)
		^ (S_ISLNK(buf.st_mode) * 5) ^ (S_ISREG(buf.st_mode) * 4)
		^ (S_ISCHR(buf.st_mode) * 3) ^ (S_ISSOCK(buf.st_mode) * 2)
		^ S_ISFIFO(buf.st_mode));
}

char	file_type(mode_t st_mode)
{
	if (S_ISLNK(st_mode))
		return ('l');
	if (S_ISREG(st_mode))
		return ('-');
	if (S_ISDIR(st_mode))
		return ('d');
	if (S_ISBLK(st_mode))
		return ('b');
	if (S_ISCHR(st_mode))
		return ('c');
	if (S_ISSOCK(st_mode))
		return ('s');
	if (S_ISFIFO(st_mode))
		return ('p');
	return ('?');
}

int	is_dot(char	*name)
{
	if (name[0] == '.')
	{
		if (!name[1])
			return (1);
		if (name[1] == '.' && !name[2])
			return (1);
	}
	return (0);
}
