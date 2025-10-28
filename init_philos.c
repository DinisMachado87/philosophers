/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:43:48 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/28 01:44:29 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *ph,
	pthread_mutex_t *right, pthread_mutex_t *left)
{
	if (ph->id % 2 == 0)
	{
		ph->fork_1 = right;
		ph->fork_2 = left;
	}
	else
	{
		ph->fork_1 = left;
		ph->fork_2 = right;
	}
}

int	init_philos(t_philo **phs, t_state *s)
{
	const char	*err_str = "Err: init_philos: ";
	t_philo		*ph;
	long long	i;

	i = 0;
	*phs = malloc(s->n_philos * sizeof(t_philo));
	if (!*phs)
		return (perror(err_str), ERR);
	ph = *phs;
	while (i < s->n_philos)
	{
		ph[i].id = i;
		ph[i].s = s;
		assign_forks(&ph[i],
			&s->forks[i - 1],
			&s->forks[(i + 1) % s->n_philos]);
		if (OK != pthread_create(&ph[i].life, NULL, routine, (void *)&ph[i]))
			return (perror(err_str), ERR);
		i++;
	}
	return (OK);
}
