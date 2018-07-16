/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forkpty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 16:48:32 by rsilva            #+#    #+#             */
/*   Updated: 2018/07/15 16:48:34 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

char	isflag(char **av, int i, char ret)
{
	int c;

	c = 1;
	while (av[i][c])
	{
		if (av[i][c] != 'a' && av[i][c] != 'q' && av[i][c] != 'r' &&
			av[i][c] != 'p' && av[i][c] != 'f' && av[i][c] != 'd' &&
			av[i][c] != 't' && av[i][c] != 'k')
			return (-1);
		ret = ret | ((av[i][c] == 'a') ? FLAG_A : 0);
		ret = ret | ((av[i][c] == 'q') ? FLAG_Q : 0);
		ret = ret | ((av[i][c] == 'r') ? FLAG_R : 0);
		ret = ret | ((av[i][c] == 'p') ? FLAG_P : 0);
		ret = ret | ((av[i][c] == 'f') ? FLAG_F : 0);
		ret = ret | ((av[i][c] == 'd') ? FLAG_D : 0);
		ret = ret | ((av[i][c] == 't') ? FLAG_T : 0);
		ret = ret | ((av[i][c] == 'k') ? FLAG_K : 0);
		c++;
	}
	return (ret);
}

void	setflags(char **av, char **args)
{
	int		i;
	char	ret;

	i = 1;
	ret = 0;
	args[0][0] = -1;
	args[0][1] = '\0';
	args[2] = NULL;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			if ((ret = isflag(av, i, ret)) == -1)
				return ;
		}
		i++;
	}
	args[0][0] = ret;
	return ;
}

void	dupstuff(int slavfd, const struct termios *termp,
				const struct winsize *winp)
{
	ioctl(slavfd, TIOCSCTTY, 0);
	ioctl(slavfd, TIOCGETA, termp);
	ioctl(slavfd, TIOCSWINSZ, winp);
	dup2(slavfd, STDIN_FILENO);
	dup2(slavfd, STDOUT_FILENO);
	dup2(slavfd, STDERR_FILENO);
	close(slavfd);
}

int		ft_masteropen(char *slavname)
{
	int		masfd;
	char	newname[MAX_NAME_LEN];

	if ((masfd = open("/dev/ptmx", O_RDWR | O_NOCTTY)) == -1)
		return (-1);
	ioctl(masfd, TIOCPTYGRANT, 0);
	ioctl(masfd, TIOCPTYUNLK, 0);
	ioctl(masfd, TIOCPTYGNAME, newname);
	if (slavname)
		ft_strncpy(slavname, newname, MAX_NAME_LEN);
	return (masfd);
}

pid_t	ft_forkpty(int *master, const struct termios *termp,
					const struct winsize *winp)
{
	int		masfd;
	int		slavfd;
	char	slavname[MAX_NAME_LEN];
	pid_t	pid;

	if ((masfd = ft_masteropen(slavname)) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid > 0)
	{
		*master = masfd;
		return (pid);
	}
	else if (!pid)
	{
		setsid();
		close(masfd);
		if ((slavfd = open(slavname, O_RDWR)) == -1)
			return (-1);
		dupstuff(slavfd, termp, winp);
		return (0);
	}
	return (-1);
}
