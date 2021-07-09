/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:41:42 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/10 00:15:02 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	color_link(char *cont, char *name, struct stat buf, t_u_char *flags)
{
	char	*buf2;
	ssize_t	bufsiz;
	ssize_t	nbytes;

	bufsiz = buf.st_size + 1;
	if (buf.st_size == 0)
		bufsiz = PATH_MAX;
	buf2 = malloc(bufsiz);
	nbytes = readlink(cont, buf2, bufsiz);
	buf2[nbytes] = '\0';
	if (flags['l'])
		ft_printf(BOLD"\e[96m%s"E0M" -> %s", name, buf2);
	else
		ft_printf(BOLD"\e[96m%s"E0M, name);
	free(buf2);
}

void	element_color(char *cont, char *name, struct stat buf, t_u_char *flags)
{
	char	type;

	type = file_type(buf.st_mode);
	if (type == 'l')
	{
		color_link(cont, name, buf, flags);
		return ;
	}
	else if (type == 'd')
		ft_putstr(BOLD""CEL);
	else if (buf.st_mode & S_IXUSR)
		ft_putstr(BOLD""GREEN);
	else if (type == 'b' || type == 'c')
		ft_putstr(BOLD""YELLOW);
	ft_printf("%s"E0M, name);
}
