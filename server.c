/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gatan <gatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 04:16:25 by gatan             #+#    #+#             */
/*   Updated: 2021/05/29 18:35:20 by gatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_pid(void)
{
	pid_t	pid;
	char	*pid_str;

	pid = getpid();
	pid_str = ft_itoa(pid);
	ft_putstr_fd("The server's process ID is: ", 1);
	ft_putstr_fd(pid_str, 1);
	ft_putchar_fd('\n', 1);
	free(pid_str);
}

void	do_bit_on(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	if (!g_print.data_bit)
	{
		g_print.data_bit = 1 << 7;
		g_print.data_byte++;
	}
	g_print.string[g_print.data_byte] += g_print.data_bit;
	g_print.data_bit = g_print.data_bit >> 1;
	if (g_print.data_byte == BUFFERSIZE - 1 && !g_print.data_bit)
		g_print.overflow = 1;
}

void	do_bit_off(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (!g_print.data_bit)
	{
		g_print.data_bit = 1 << 7;
		g_print.data_byte++;
	}	
	g_print.data_bit = g_print.data_bit >> 1;
	if (g_print.data_byte == BUFFERSIZE - 1 && !g_print.data_bit)
		g_print.overflow = 1;
	else if (!g_print.string[g_print.data_byte] && !g_print.data_bit)
	{
		g_print.finished = 1;
		kill(info->si_pid, SIGUSR1);
	}
}

void	server_handler(void)
{
	while (1)
	{
		pause();
		if (g_print.finished == 1 || g_print.overflow == 1)
		{
			write(1, g_print.string, ft_strlen(g_print.string));
			ft_bzero(g_print.string, BUFFERSIZE);
			if (g_print.finished == 1)
				ft_putchar_fd('\n', 1);
			g_print.data_bit = 1 << 7;
			g_print.data_byte = 0;
			g_print.finished = 0;
			g_print.overflow = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	bit_on;
	struct sigaction	bit_off;

	bit_on.sa_sigaction = do_bit_on;
	bit_off.sa_sigaction = do_bit_off;
	bit_on.sa_flags = SA_SIGINFO;
	bit_off.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &bit_on, NULL) == -1)
		error("Error in receiving signal\n");
	if (sigaction(SIGUSR2, &bit_off, NULL) == -1)
		error("Error in receiving signal\n");
	print_pid();
	ft_bzero(g_print.string, BUFFERSIZE);
	server_handler();
}
