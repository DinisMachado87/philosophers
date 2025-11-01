/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:35:47 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/01 04:16:02 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_end(t_state *s)
{
	int	end;

	mtx_lock_tracked(&s->state_mtx, s);
	if (s->err)
		end = s->err;
	else
		end = s->end;
	mtx_unlock_tracked(&s->state_mtx, s);
	return (end);
}

long long	now(struct timeval *time, t_state *s)
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

	time = now(&ph->time, s);
	if (OK == mtx_lock_tracked(&s->state_mtx, s)
		&& OK < printf("%lld %lld %s\n", time, ph->id, str)
		&& OK == mtx_unlock_tracked(&s->state_mtx, s))
		return (is_end(s));
	return (set_and_print_error(s, "Err: safe_print"));
}

/*
** Error handler - uses raw pthread calls to avoid recursion.
** Tracked mutex wrappers call this on failure, so this must not call them.
*/
int	set_and_print_error(t_state *s, char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	pthread_mutex_lock(&s->state_mtx);
	s->err = ERR;
	s->end = END;
	write(2, str, len);
	pthread_mutex_unlock(&s->state_mtx);
	return (ERR);
}
