/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/28 15:39:40 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_end(t_state *s)
{
	int	end;

	pthread_mutex_lock(&s->mtx_end);
	end = s->end;
	pthread_mutex_unlock(&s->mtx_end);
	return (end);
}

int	now(struct timeval *time, t_state *s)
{
	long long	sec_to_milisec;
	long long	microsec_to_milisec;

	if (OK != gettimeofday(time, NULL))
		return (set_and_print_error(s, "Error getting time"));
	sec_to_milisec = time->tv_sec * 1000LL;
	microsec_to_milisec = time->tv_usec / 1000;
	return (sec_to_milisec + microsec_to_milisec);
}

int	wait_and_watch(size_t duration, t_state *s, struct timeval *time)
{
	long long	sleep_end;
	int			end;

	sleep_end = now(time, s) + duration;
	while (now(time, s) < sleep_end)
	{
		end = is_end(s);
		if (end)
			return (end);
		usleep(500);
	}
	return (OK);
}

int	safe_print(char *str, t_philo *ph, t_state *s)
{
	long long	time;

	if (is_end(s))
		return (END);
	if (OK != gettimeofday(&ph->time, NULL))
	{
		time = ph->time.tv_sec * 1000LL + ph->time.tv_usec / 1000;
		if (OK == pthread_mutex_lock(&s->print)
			&& OK < printf("%lld ", time)
			&& OK < printf(str, ph->id)
			&& OK == pthread_mutex_unlock(&s->print))
			return (OK);
	}
	return (set_and_print_error(s, "Err printing"));
}
