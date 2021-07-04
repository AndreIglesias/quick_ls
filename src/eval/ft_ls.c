/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:53:36 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/05 00:48:42 by ciglesia         ###   ########.fr       */
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
		print_element(*files, flags, ls);
		if (!flags['l'] && *(files + 1))
			ft_putstr("  ");
		else
			ft_putchar('\n');
		files++;
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
	print_files(ls->dirs, ls->flags, ls);//
}
