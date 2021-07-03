/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:53:36 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/04 01:25:30 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

/*
**	TODO
**		files+dirs array
**		sort files, dirs, files+dirs array
*/

void	ft_ls(t_ls *ls)
{
	if (ls->flags['r'] && !ls->flags['t'])
		strquick(ls->files, ls->size_f, &alpha_rev);
	else if (ls->flags['r'] && ls->flags['t'])
		strquick(ls->files, ls->size_f, &time_rev);
	else if (ls->flags['t'])
		strquick(ls->files, ls->size_f, &time_cmp);
	else
		strquick(ls->files, ls->size_f, &alpha_cmp);
	for (size_t i = 0; i < ls->size_f; i++)
		ft_printf("%s ", ls->files[i]);
	for (size_t i = 0; i < ls->size_d; i++)
		ft_printf(CEL""BOLD"%s "E0M, ls->dirs[i]);
	ft_putchar('\n');
}
