/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:29:37 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/28 02:07:38 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

static inline long long	now(t_state *s)
{
	if (OK != gettimeofday(&s->time, NULL))
		return (set_and_print_error(s, "Err printing"));
	return (s->time.tv_sec * 1000LL + s->time.tv_usec / 1000);
}

static inline int	is_end(t_state *s)
{
	int	end;

	pthread_mutex_lock(&s->mtx_end);
	end = s->end;
	pthread_mutex_unlock(&s->mtx_end);
	return (end);
}

static int	check_and_set_end(t_state *s)
{
	long long	cur_time;
	int			end;

	cur_time = now(s);
	end = is_end(s);
	if (end)
		return (end);
	if ((cur_time - s->start) > s->t_die)
	{
		pthread_mutex_lock(&s->mtx_end);
		s->end = END;
		pthread_mutex_unlock(&s->mtx_end);
		return (END);
	}
	return (OK);
}

void	*monitor(t_state *s)
{
	t_philo		*cur_ph;
	int			end;

	cur_ph = s->philos;
	s->start = now(s);
	while (!end)
		end = check_and_set_end(s);
	return (NULL);
}
