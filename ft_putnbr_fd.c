/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcomic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:28:53 by kcomic            #+#    #+#             */
/*   Updated: 2021/10/24 19:29:04 by kcomic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	norme_style(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	len;
	int	temp;

	len = 1;
	n = norme_style(n, fd);
	temp = n / 10;
	while (temp > 0)
	{
		len *= 10;
		temp /= 10;
	}
	temp = n;
	while (len > 0)
	{
		ft_putchar_fd(temp / len + '0', fd);
		temp %= len;
		len /= 10;
	}
}
