/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:30:30 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/04 16:37:32 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_itoa_cat(char *buf, long long n)
{
	int			len;
	long long	tmp;

	len = 0;
	tmp = n;
	if (n == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return ;
	}
	while (tmp > 0)
	{
		tmp /= 10;
		len++;
	}
	buf[len] = '\0';
	while (n > 0)
	{
		buf[--len] = (n % 10) + '0';
		n /= 10;
	}
}

void	unique_name(char *buf, long long id)
{
	const char	*prefix = "/philo_";
	int			i;

	i = 0;
	while (prefix[i])
	{
		buf[i] = prefix[i];
		i++;
	}
	ft_itoa_cat(&buf[i], id);
}
