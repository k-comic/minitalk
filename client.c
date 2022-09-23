/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:39:12 by marvin            #+#    #+#             */
/*   Updated: 2022/03/05 22:39:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_send_endzero(int server_pid)
{
	static int	i = 0;

	if (i <= 8)
		if (kill(server_pid, SIGUSR1) == -1)
			ft_error("Error: failed to send \\0.\n");
	i++;
}

static void	ft_send_signal(int server_pid, char *message)
{
	static int	bit = 0;
	static char	*str = 0;
	char		c;

	c = 1;
	if (message)
		str = message;
	if (*str)
	{
		if ((((unsigned char)*str >> bit) & c) != c)
			if (kill(server_pid, SIGUSR1) == -1)
				ft_error("Error: failed to send 0.\n");
		if ((((unsigned char)*str >> bit) & c) == c)
			if (kill(server_pid, SIGUSR2) == -1)
				ft_error("Error: failed to send 1.\n");
		bit++;
		if (bit == 8)
		{
			str++;
			bit = 0;
		}
	}
	else
		ft_send_endzero(server_pid);
}

static void	ft_reception(int sig, siginfo_t *info, void *context)
{
	static int	server_pid;

	(void)context;
	if (info->si_pid != 0)
		server_pid = info->si_pid;
	if (sig == SIGUSR1)
		ft_send_signal(server_pid, NULL);
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("Server acknowledged the message.\n", 1);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_reception;
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
		ft_error("Error: failed to handle signal.\n");
	if (argc != 3)
		ft_error("Error: wrong arguments. (./client <server_PID> <message>)\n");
	ft_send_signal(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
