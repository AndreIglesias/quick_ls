/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 01:07:09 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/04 20:35:03 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
**	strins(&ls->files, &hola, 0, ls->size_f);
*/

void	strins(char ***array, char **str, size_t pos, size_t size)
{
	ft_memins((void **)array, str, sizeof(char *) * pos,
		(t_sizes){sizeof(char *) * size, sizeof(char **)});
}

int	alpha_cmp(char *a, char *b)
{
	char	la;
	char	lb;

	while (*a && *b)
	{
		la = *a;
		if ('A' <= *a && *a <= 'Z')
			la = (*a) + ('a' - 'A');
		lb = *b;
		if ('A' <= *b && *b <= 'Z')
			lb = (*b) + ('a' - 'A');
		if (la != lb)
			return ((la - lb) < 0);
		a++;
		b++;
	}
	return (0);
}

int	alpha_rev(char *a, char *b)
{
	char	la;
	char	lb;

	while (*a && *b)
	{
		la = *a;
		if ('A' <= *a && *a <= 'Z')
			la = (*a) + ('a' - 'A');
		lb = *b;
		if ('A' <= *b && *b <= 'Z')
			lb = (*b) + ('a' - 'A');
		if (la != lb)
			return ((la - lb) > 0);
		a++;
		b++;
	}
	return (0);
}

int	time_cmp(char *a, char *b)
{
	struct stat	buf;
	struct stat	buf_next;

	if (lstat(a, &buf) == -1)
		return (0);
	if (lstat(b, &buf_next) == -1)
		return (0);
	return (buf.st_mtime > buf_next.st_mtime);
}

int	time_rev(char *a, char *b)
{
	struct stat	buf;
	struct stat	buf_next;

	if (lstat(a, &buf) == -1)
		return (0);
	if (lstat(b, &buf_next) == -1)
		return (0);
	return (buf.st_mtime < buf_next.st_mtime);
}
