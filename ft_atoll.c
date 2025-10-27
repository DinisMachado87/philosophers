/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:56:17 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 16:05:13 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	return (c == ' '
		|| (c >= '\t' && c <= '\r'));
}

long long	ft_atoll(char *original)
{
	char		*str;
	long long	n;
	int			digit;

	str = original;
	n = 0;
	while (is_space(*str))
		str++;
	if (*str == '-')
		return (printf("Err: Negative arg: %s\n", original), ERR);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str++ - '0';
		if (n > (LLONG_MAX - digit) / 10)
			return (printf("Err: ft_atoll overflow: %s\n", original), ERR);
		n = n * 10 + digit;
	}
	if (*str)
		return (printf("Err: Arg with invalid chars: %s\n", original), ERR);
	return (n);
}
