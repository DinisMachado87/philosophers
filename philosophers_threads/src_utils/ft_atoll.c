/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:56:17 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/01 03:08:39 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	return (c == ' '
		|| (c >= '\t' && c <= '\r'));
}

long long	ft_atoll(char *str_num)
{
	char		*str;
	long long	n;
	int			digit;

	str = str_num;
	n = 0;
	while (is_space(*str))
		str++;
	if (*str == '-')
		return (printf("Err: ft_atoll: Negative arg\n"), ERR);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str++ - '0';
		if (n > (LLONG_MAX - digit) / 10)
			return (
				printf("Err: ft_atoll: Overflow\n"),
				ERR);
		n = n * 10 + digit;
	}
	if (*str)
		return (printf("Err: ft_atoll: Arg w/ invalid chars\n"), ERR);
	return (n);
}
