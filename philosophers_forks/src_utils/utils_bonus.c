/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 04:47:12 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	now(struct timeval *time, t_state *s)
{
	long long	sec_to_milisec;
	long long	microsec_to_milisec;

	if (OK != gettimeofday(time, NULL))
		return (set_and_print_error(s, "Error: gettimeofday failed\n"));
	sec_to_milisec = time->tv_sec * 1000LL;
	microsec_to_milisec = time->tv_usec / 1000;
	return (sec_to_milisec + microsec_to_milisec);
}

int	wait_and_watch(size_t duration, t_state *s, struct timeval *time)
{
	long long	sleep_end;

	sleep_end = now(time, s) + duration;
	while (now(time, s) < sleep_end)
	{
		if (is_end(s))
			return (END);
		usleep(500);
	}
	return (OK);
}

int	safe_print(char *str, t_philo *ph, t_state *s)
{
	long long	time;

	time = now(&ph->time, s) - s->start;
	if (OK == safe_sem_wait(s->sem_write, s))
	{
		if (!is_end(s))
			printf("%lld %lld %s\n", time, ph->id, str);
		safe_sem_post(s->sem_write, s);
		return (is_end(s));
	}
	return (set_and_print_error(s, "Error: safe_print\n"));
}

int	is_end(t_state *s)
{
	if (s->err || s->end)
		return (1);
	return (0);
}

int	set_and_print_error(t_state *s, char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	s->err = ERR;
	s->end = END;
	write(2, str, len);
	return (ERR);
}
