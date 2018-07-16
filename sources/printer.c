/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 20:19:44 by rsilva            #+#    #+#             */
/*   Updated: 2018/07/15 20:20:20 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

char	*findshell(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], "SHELL=", 6)))
			return (envp[i] + 6);
		i++;
	}
	return ("/bin/sh");
}

char	*get_time(void)
{
	time_t	curr_time;

	curr_time = time(NULL);
	return (ctime(&curr_time));
}

char	*findname(char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] != '-')
			return (av[i]);
		i++;
	}
	return ("typescript");
}

void	print_start(char **av, int fd)
{
	ft_putstr("Script started, output file is ");
	ft_putstr(findname(av));
	ft_putstr("\n");
	ft_putstr_fd("Script started on ", fd);
	ft_putstr_fd(get_time(), fd);
}

void	print_end(char **av, int fd)
{
	ft_putstr("\nScript done, output file is ");
	ft_putstr(findname(av));
	ft_putstr("\n");
	ft_putstr_fd("\nScript done on ", fd);
	ft_putstr_fd(get_time(), fd);
}
