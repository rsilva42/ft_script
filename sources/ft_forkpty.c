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
