/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 23:44:07 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/03 12:27:45 by ciglesia         ###   ########.fr       */
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
	struct stat	path_stat;

	stat(filename, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}
