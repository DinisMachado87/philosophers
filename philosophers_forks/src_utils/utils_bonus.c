/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 12:22:10 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	now(t_philo *ph)
{
	struct timeval	time;
	long long		sec_to_milisec;
	long long		microsec_to_milisec;

	if (OK != gettimeofday(&time, NULL))
		return (ret_and_print_err("Error: gettimeofday failed\n"));
	sec_to_milisec = time.tv_sec * 1000LL;
	microsec_to_milisec = time.tv_usec / 1000;
	if (ph)
		ph->cache_now = sec_to_milisec + microsec_to_milisec;
	return (sec_to_milisec + microsec_to_milisec);
}

int	safe_print(char *str, t_philo *ph, t_state *s)
{
	long long	time;

	if (OK == safe_sem_wait(s->sem_write))
	{
		time = now(NULL) - s->start;
		if (OK < printf("%lld %lld %s\n", time, ph->id, str)
			&& OK == safe_sem_post(s->sem_write))
			return (OK);
	}
	return (ret_and_print_err("Err: safe_print"));
}

int	safe_print_two(char *str, char *str2, t_philo *ph, t_state *s)
{
	long long	time;

	if (OK == safe_sem_wait(s->sem_write))
	{
		time = now(ph) - s->start;
		if (OK < printf("%lld %lld %s\n", time, ph->id, str)
			&& OK < printf("%lld %lld %s\n", time, ph->id, str2)
			&& OK == safe_sem_post(s->sem_write))
			return (OK);
	}
	return (ret_and_print_err("Err: safe_print"));
}

int	ret_and_print_err(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
	return (ERR);
}
