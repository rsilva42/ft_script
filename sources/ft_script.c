/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 21:47:50 by rsilva            #+#    #+#             */
/*   Updated: 2018/07/14 21:47:52 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <stdio.h>

struct termios g_og;

void	fixflags(struct termios *t)
{
	t->c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
	t->c_iflag &= ~(BRKINT | ICRNL | IGNBRK | IGNCR | INLCR |
		INPCK | ISTRIP | IXON | PARMRK);
	t->c_cc[VMIN] = 1;
	t->c_cc[VTIME] = 0;
}

void	readstdin(int master, int file, char **av)
{
	char	buf[4096];
	int		bufsize;

	if ((bufsize = read(STDIN_FILENO, buf, 4095)) > 0)
	{
		write(master, buf, bufsize);
	}
	else if (!bufsize)
	{
		ioctl(STDIN_FILENO, TIOCSETA, &g_og);
		print_end(av, file);
		_exit(0);
	}
	else
	{
		ioctl(STDIN_FILENO, TIOCSETA, &g_og);
		_exit(-1);
	}
}

void	readmaster(int master, int file, char **av)
{
	char	buf[4096];
	int		bufsize;

	if ((bufsize = read(master, buf, 4095)) > 0)
	{
		write(STDOUT_FILENO, buf, bufsize);
		write(file, buf, bufsize);
	}
	else if (!bufsize)
	{
		ioctl(STDIN_FILENO, TIOCSETA, &g_og);
		print_end(av, file);
		_exit(0);
	}
	else
	{
		ioctl(STDIN_FILENO, TIOCSETA, &g_og);
		_exit(-1);
	}
}

void	do_parent(int master, char **av, struct termios t)
{
	int		fd;
	fd_set	fds;
	char	*filename;

	filename = findname(av);
	t = g_og;
	fixflags(&t);
	ioctl(STDIN_FILENO, TIOCSETAF, &t);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0755);
	print_start(av, fd);
	while (1)
	{
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);
		FD_SET(master, &fds);
		select(master + 1, &fds, NULL, NULL, NULL);
		if (FD_ISSET(STDIN_FILENO, &fds))
			readstdin(master, fd, av);
		if (FD_ISSET(master, &fds))
			readmaster(master, fd, av);
	}
}

int		main(int ac, char **av, char **envp)
{
	pid_t			pid;
	int				master;
	struct termios	t;
	struct winsize	w;
	char			*args[2];

	(void)ac;
	args[0] = findshell(envp);
	args[1] = NULL;
	ioctl(STDIN_FILENO, TIOCGETA, &g_og);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	pid = ft_forkpty(&master, &t, &w);
	if (pid > 0)
	{
		do_parent(master, av, t);
	}
	else if (!pid)
	{
		execve(args[0], args, envp);
	}
	else
		ft_putstr_fd("fork error\n", STDERR_FILENO);
	return (0);
}
