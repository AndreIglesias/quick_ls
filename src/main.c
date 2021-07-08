/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:31:42 by ciglesia          #+#    #+#             */
/*   Updated: 2021/07/08 21:18:14 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	exit_ls(t_ls *ls, int status)
{
	free(ls->dirs);
	free(ls->files);
	exit(status);
}

static int	extract_flags(char *str, t_ls *ls)
{
	while (*str)
	{
		if (*str == 'l')
			ls->flags['l'] = 1;
		else if (*str == 'R')
			ls->flags['R'] = 1;
		else if (*str == 'a')
			ls->flags['a'] = 1;
		else if (*str == 'r')
			ls->flags['r'] = 1;
		else if (*str == 't')
			ls->flags['t'] = 1;
		else
		{
			if (*str != '-')
				ft_printf_fd(2, "ft_ls: invalid option -- '%c'\n", *str);
			else
				ft_printf_fd(2, "ft_ls: unrecognized option '-%s'\n", str);
			ft_printf_fd(2, "Try 'ft_ls --help' for more information.\n");
			return (0);
		}
		str++;
	}
	return (1);
}

static int	ft_usage(void)
{
	ft_printf_fd(2, BOLD"USAGE:\n\t\t"E0M"ls [OPTION]... [FILE]...\n");
	ft_printf_fd(2, BOLD"DESCRIPTION:\n\t\t"E0M"List information about the\
 FILEs (the current directory by default).\n");
	ft_printf_fd(2, "\t\tSort entries alphabetically if -t is not specified.");
	ft_printf_fd(2, BOLD"\nOPTIONS:\n"E0M);
	ft_printf_fd(2, BOLD"-l:\t\t"E0M"Use a long listing format\n");
	ft_printf_fd(2, BOLD"-a:\t\t"E0M"Do not ignore entries starting with .\n");
	ft_printf_fd(2, BOLD"-r:\t\t"E0M"Reverse order while sorting\n");
	ft_printf_fd(2, BOLD"-R:\t\t"E0M"List subdirectories recursively\n");
	ft_printf_fd(2, BOLD"-t:\t\t"E0M"Sort by modification time, newest\
 first\n");
	return (EXIT_SUCCESS);
}

static int	input_handler(int ac, char **av, t_ls *ls)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "--help"))
			exit_ls(ls, ft_usage());
		if (!(av[i][0] == '-' && av[i][1]) || !ft_strcmp(av[i], "--"))
		{
			if (is_dir(av[i]))
				ls->dirs[ls->size_d++] = av[i];
			else if (is_file(av[i]) > 0)
				ls->files[ls->size_f++] = av[i];
			else
				ft_printf_fd(2, WACCESS, av[i], strerror(errno));
		}
		else if (av[i][0] == '-' && av[i][1] && !extract_flags(&av[i][1], ls))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_ls	ls;

	ls.size_d = 0;
	ls.size_f = 0;
	ft_bzero(ls.flags, sizeof(ls.flags));
	ls.dirs = ft_calloc(ac, sizeof(char *));
	ls.files = ft_calloc(ac, sizeof(char *));
	if (!ls.dirs || !ls.files || !input_handler(ac - 1, &av[1], &ls))
		exit_ls(&ls, EXIT_FAILURE);
	ft_ls(&ls);
	exit_ls(&ls, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	destructor(void)
{
}
