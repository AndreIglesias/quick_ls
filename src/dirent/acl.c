/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:31:31 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/09 20:06:12 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	print_grp(gid_t st_gid, t_ls *ls)
{
	struct group	*grp;

	grp = getgrgid(st_gid);
	if (grp == NULL)
	{
		perror("getgrgid");
		exit_ls(ls, EXIT_FAILURE);
	}
	ft_printf("%5s ", grp->gr_name);
}

static void	print_user(uid_t st_uid, t_ls *ls)
{
	struct passwd	*user;

	user = getpwuid(st_uid);
	if (user == NULL)
	{
		perror("getpwuid");
		exit_ls(ls, EXIT_FAILURE);
	}
	ft_printf("%5s ", user->pw_name);
}

static void	print_permissions(mode_t st_mode)
{
	static const char	*rwx[8] = {"---", "--x", "-w-", "-wx",
								"r--", "r-x", "rw-", "rwx"};
	char				bits[10];

	ft_strcpy(bits, rwx[(st_mode >> 6) & 7]);
	ft_strcpy(bits + 3, rwx[(st_mode >> 3) & 7]);
	ft_strcpy(bits + 6, rwx[st_mode & 7]);
	ft_putchar(file_type(st_mode));
	if (st_mode & S_ISUID)
		bits[2] = 'S';
	if (st_mode & S_ISUID && st_mode & S_IXUSR)
		bits[2] = 's';
	if (st_mode & S_ISGID)
		bits[5] = 'l';
	if (st_mode & S_ISGID && st_mode & S_IXGRP)
		bits[5] = 's';
	if (st_mode & S_ISVTX)
		bits[8] = 'T';
	if (st_mode & S_ISVTX && st_mode & S_IXOTH)
		bits[8] = 't';
	bits[9] = 0;
	ft_putstr(bits);
}

void	print_element(char *cont, char *name, t_u_char *flags, t_ls *ls)
{
	struct stat			buf;
	security_context_t	sc;

	ft_memset(&buf, 0, sizeof(struct stat *));
	if (lstat(cont, &buf) == -1)
	{
		ft_printf_fd(2, WLSTAT, cont, strerror(errno));
		exit_ls(ls, EXIT_FAILURE);
	}
	if (flags['l'])
	{
		print_permissions(buf.st_mode);
		if (getfilecon(cont, &sc) > 0)
			ft_putstr(". ");
		else
			ft_putstr("  ");
		ft_printf("%4lu ", buf.st_nlink);
		print_user(buf.st_uid, ls);
		print_grp(buf.st_gid, ls);
		ft_printf("%7lu ", buf.st_size);
		ft_printf("%.12s ", &ctime(&buf.st_mtime)[4]);
	}
	element_color(cont, name, buf, flags);
}
