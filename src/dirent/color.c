/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:41:42 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/04 20:51:58 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	color_link(struct stat buf)
{
	(void)buf;
	ft_putstr(BOLD"\e[96m");
}

void	element_color(char *cont, struct stat buf)
{
	char	type;

	type = file_type(buf.st_mode);
	if (type == 'l')
		color_link(buf);
	ft_printf("%s"E0M, cont);
}
