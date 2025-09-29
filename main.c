/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/09/30 01:32:25 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo **phs, t_state *s)
{
	char	*err_str = "Err: init_philos: ";
	t_philo	*ph;
	size_t	i;

	i = 0;
	*phs = malloc(s->n_philos * sizeof(t_philo));
	if (!*phs)
		return (perror(err_str), ERR);
	ph = *phs;
	while (i < s->n_philos)
	{
		ph[i].s = s;
		ph[i].left = &s->forks[i - 1];
		ph[i].right = &s->forks[(i + 1) % s->n_philos];
		if (OK != pthread_create(&ph[i].life, NULL, routine, ph[i]))
			return (perror(err_str), ERR);
		i++;
	}
	return (OK);
}

int	init_forks(t_state *s)
{
	char	*err_str = "ERR: init_forks:";
	ssize_t	i;

	i = 0;
	s->forks = malloc(s->n_philos * sizeof(pthread_mutex_t));
	if (!s->forks)
		return (perror(err_str), ERR);
	while (i < s->n_philos)
	{
		if (OK != pthread_mutex_init(&s->forks[i], NULL))
			return (perror(err_str), ERR);
		i++;
	}
	return (OK);
}

/* number_of_philosophers time_to_die time_to_eat
 * time_to_sleep, [number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	t_state	s;
	t_philo	*phs;
	ssize_t	i;

	i = 0;
	if (OK != init_state(argc, argv, &s)
		|| OK != init_forks(&s)
		|| OK != init_philos(&phs,&s))
		return (ERR);
	return (OK);
}
