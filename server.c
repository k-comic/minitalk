/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:00:13 by marvin            #+#    #+#             */
/*   Updated: 2022/03/05 19:00:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_handle(int sig, siginfo_t *info, void *context)
{
	static int				bit = 1;
	static int				client_pid = 0;
	static unsigned char	value = 0;

	(void)context ;
	if (info->si_pid != 0)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		value += 0;
	if (sig == SIGUSR2)
		value += bit;
	bit *= 2;
	if (bit == 256)
	{
		bit = 1;
		if (value == 0)
			if (kill(client_pid, SIGUSR2) == -1)
				ft_error("Error: failed to acknowledge message.\n");
		if (value != 0)
			write(1, &value, 1);
		value = 0;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		ft_error("Error: failed to acknowledge signal.\n");
}

int	main(void)
{
	struct sigaction	s_handle_signal;

	ft_putstr_fd("Server's PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	s_handle_signal.sa_sigaction = ft_handle;
	s_handle_signal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s_handle_signal, NULL)
		|| sigaction(SIGUSR2, &s_handle_signal, NULL))
		ft_error("Error: failed to handle signal.\n");
	while (1)
		pause();
	return (0);
}
