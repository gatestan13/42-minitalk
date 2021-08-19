/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gatan <gatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 04:16:22 by gatan             #+#    #+#             */
/*   Updated: 2021/05/29 21:42:55 by gatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_success(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr_fd("Message successfully received by server\n", 1);
}

void	send_char_by_bit(pid_t pid, char byte)
{
	uint8_t	counter;

	counter = 1 << 7;
	while (counter)
	{
		if (byte & counter)
		{
			if (kill(pid, SIGUSR1) == -1)
				error("Invalid PID");
		}	
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error("Invalid PID");
		}
		counter = counter >> 1;
		usleep(150);
	}
}

void	client_handler(char *pid_str, char *str)
{
	pid_t	pid;

	pid = ft_atoi(pid_str);
	while (*str)
	{
		send_char_by_bit(pid, *str);
		str++;
	}
	send_char_by_bit(pid, *str);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		error("Usage: ./client [PID] [Message]\n");
	signal(SIGUSR1, print_success);
	client_handler(argv[1], argv[2]);
	return (0);
}
