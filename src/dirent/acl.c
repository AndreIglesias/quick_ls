/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:31:31 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/11 06:51:13 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	print_grp(gid_t st_gid)
{
	struct group	*grp;

	grp = getgrgid(st_gid);
	if (grp == NULL)
		ft_printf("%5d", st_gid);
	else
		ft_printf("%5s ", grp->gr_name);
}

static void	print_user(uid_t st_uid)
{
	struct passwd	*user;

	user = getpwuid(st_uid);
	if (user == NULL)
		ft_printf("%5d ", st_uid);
	else
		ft_printf("%5s ", user->pw_name);
}

static char	*print_permissions(mode_t st_mode, int context, char *cont)
{
	static const char	*rwx[8] = {"---", "--x", "-w-", "-wx",
								"r--", "r-x", "rw-", "rwx"};
	static char			bits[12] = {0};

	bits[0] = file_type(st_mode);
	ft_strcpy(bits + 1, rwx[(st_mode >> 6) & 7]);
	ft_strcpy(bits + 4, rwx[(st_mode >> 3) & 7]);
	ft_strcpy(bits + 7, rwx[st_mode & 7]);
	if (st_mode & S_ISUID)
		bits[3] = 'S';
	if (st_mode & S_ISUID && st_mode & S_IXUSR)
		bits[3] = 's';
	if (st_mode & S_ISGID)
		bits[6] = 'S';
	if (st_mode & S_ISGID && st_mode & S_IXGRP)
		bits[6] = 's';
	if (st_mode & S_ISVTX)
		bits[9] = 'T';
	if (st_mode & S_ISVTX && st_mode & S_IXOTH)
		bits[9] = 't';
	bits[10] = ' ';
	if (listxattr(cont, NULL, 0) > 0)
		bits[10] = '+';
	bits[10] = (context) * '.' + (!context) * bits[10];
	return (bits);
}

void	major_minor(dev_t st_rdev, off_t st_size, t_ls *ls)
{
	t_byte			mm;
	unsigned int	major;
	unsigned int	minor;

	major = major(st_rdev);
	minor = minor(st_rdev);
	mm = (major || minor);
	if (mm)
	{
		ft_printf("%4d,", major);
		ft_repet(' ', ls->file_size - ft_sizei(minor));
		ft_printf("%d ", minor);
	}
	else
	{
		ft_putstr("     ");
		ft_repet(' ', ls->file_size - ft_sizei(st_size));
		ft_printf("%lu ", st_size);
	}
}

void	print_element(char *cont, char *name, t_u_char *flags, t_ls *ls)
{
	struct stat			buf;
	security_context_t	sc;
	char				*rwx;

	ft_memset(&buf, 0, sizeof(struct stat *));
	if (lstat(cont, &buf) == -1)
	{
		ft_printf_fd(2, WLSTAT, cont, strerror(errno));
		return ;
	}
	if (flags['l'])
	{
		rwx = print_permissions(buf.st_mode, (getfilecon(cont, &sc) > 0), cont);
		ft_putstr(rwx);
		ft_repet(' ', ls->link_count - ft_sizei(buf.st_nlink) + 1);
		ft_printf("%lu ", buf.st_nlink);
		print_user(buf.st_uid);
		print_grp(buf.st_gid);
		major_minor(buf.st_rdev, buf.st_size, ls);
		ft_printf("%.12s ", &ctime(&buf.st_mtime)[4]);
	}
	element_color(cont, name, buf, flags);
}
