/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:29:37 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/01 04:18:16 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	are_philos_full(t_state *s, t_philo *phs)
{
	const long long	must_eats = s->n_eats;
	long long		n_meals;
	long long		i;

	i = 0;
	while (i < s->n_philos)
	{
		mtx_lock_tracked(&phs[i].mtx_philo, s);
		n_meals = phs[i].n_eats;
		mtx_unlock_tracked(&phs[i].mtx_philo, s);
		if (n_meals < must_eats)
			return (0);
		i++;
	}
	return (END);
}

static int	are_dead_philos(t_state *s, t_philo *phs)
{
	const long long	cur_time = now(&s->time, s);
	long long		i;

	i = 0;
	while (i < s->n_philos)
	{
		mtx_lock_tracked(&phs[i].mtx_philo, s);
		if (phs[i].nxt_death < cur_time)
		{
			mtx_unlock_tracked(&phs[i].mtx_philo, s);
			safe_print("died\n", &phs[i], s);
			return (END);
		}
		mtx_unlock_tracked(&phs[i].mtx_philo, s);
		i++;
	}
	return (OK);
}

static int	set_end(t_state *s)
{
	pthread_mutex_lock(&s->state_mtx);
	s->end = END;
	pthread_mutex_unlock(&s->state_mtx);
	return (END);
}

void	monitor(t_state *s)
{
	t_philo	*phs;

	phs = s->philos;
	while (!is_end(s))
	{
		if (are_dead_philos(s, phs)
			|| (s->n_eats > 0 && are_philos_full(s, phs)))
			set_end(s);
		usleep(100);
	}
	return ;
}
