/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/04 14:32:28 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

long long	now(struct timeval *time)
{
	long long	sec_to_milisec;
	long long	microsec_to_milisec;

	if (OK != gettimeofday(time, NULL))
		return (ret_and_print_err("Error: gettimeofday failed\n"));
	sec_to_milisec = time->tv_sec * 1000LL;
	microsec_to_milisec = time->tv_usec / 1000;
	return (sec_to_milisec + microsec_to_milisec);
}

int	wait_and_watch(size_t duration, struct timeval *time, t_philo *ph)
{
	t_state		*s;
	long long	sleep_end;
	long long	cur_time;
	long long	next_death;

	s = ph->s;
	cur_time = now(time);
	sleep_end = cur_time + duration;
	next_death = ph->nxt_death;
	while (cur_time < sleep_end)
	{
		usleep(500);
		cur_time = now(time);
		if (cur_time > next_death)
		{
			safe_print("died", ph, s);
			close_semaphores(s);
			exit(DEAD);
		}
	}
	return (OK);
}

int	safe_print(char *str, t_philo *ph, t_state *s)
{
	long long	time;

	time = now(&ph->time) - s->start;
	if (OK != safe_sem_wait(s->sem_write))
		return (ERR);
	printf("%lld %lld %s\n", time, ph->id, str);
	if (OK != safe_sem_post(s->sem_write))
		return (ERR);
	return (OK);
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
