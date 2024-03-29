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

# define FLAG_K 128
# define FLAG_T 64
# define FLAG_D 32
# define FLAG_F 16
# define FLAG_P 8
# define FLAG_R 4
# define FLAG_Q 2
# define FLAG_A 1

void	setterm(struct termios *t);
void	readstdin(int master, int file, char **av, char flags);
void	readmaster(int master, int file, char **av, char flags);
void	do_parent(int master, char **av, struct termios t, char flags);
void	do_child(char **av, char **envp);

char	isflag(char **av, int i, char ret);
void	setflags(char **av, char **args, char **envp);
void	dupstuff(int slavfd, const struct termios *termp,
				const struct winsize *winp);
int		ft_masteropen(char *slavname);
pid_t	ft_forkpty(int	*master, const struct termios *termp,
					const struct winsize *winp);

char	*get_time(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strncpy(char *dst, const char *src, size_t len);

char	*findshell(char **envp);
char	*findname(char **av);
void	print_start(char **av, int fd);
void	print_end(char **av, int fd);

#endif
