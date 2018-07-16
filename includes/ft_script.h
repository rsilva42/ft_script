/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 21:47:17 by rsilva            #+#    #+#             */
/*   Updated: 2018/07/14 21:47:29 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <string.h>

# define MAX_NAME_LEN 1000

void	fixflags(struct termios *t);
void	readstdin(int master, int file, char **av);
void	readmaster(int master, int file, char **av);
void	do_parent(int master, char **av, struct termios t);
void	do_child(char **av, char **envp);

void	dupstuff(int slavfd, const struct termios *termp,
				const struct winsize *winp);
int		ft_masteropen(char *slavname);
pid_t	ft_forkpty(int	*master, const struct termios *termp,
					const struct winsize *winp);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strncpy(char *dst, const char *src, size_t len);

char	*findshell(char **envp);
char	*get_time(void);
char	*findname(char **av);
void	print_start(char **av, int fd);
void	print_end(char **av, int fd);

#endif
