/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/09/30 00:52:27 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *ph, t_state *s, size_t i)
{
	ph->left = i - 1;
	ph->right = (i + 1) % s->n_philos;
	return (1);
}

int	init_forks(t_state *s)
{
	char	*err_str = "ERR: malloc ph and forks:";
	ssize_t	i;

	i = 0;
	s->forks = malloc(s->n_philos * sizeof(pthread_mutex_t));
	if (!s->forks)
		return (perror(err_str), ERR);
	while (i < s->n_philos)
		if (OK != pthread_mutex_init(&s->forks[i], NULL))
			return (perror(err_str), ERR);
	return (OK);
}

/* number_of_philosophers time_to_die time_to_eat
 * time_to_sleep, [number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	t_state	s;
	t_philo	*ph;
	ssize_t	i;

	i = 0;
	if (!init_state(argc, argv, &s)
		|| !init_forks(&s))
		return (ERR);
	ph = malloc(s.n_philos * sizeof(t_philo));
	while (i < s.n_philos)
	{
		if (!init_philo(&ph[i], &s, i))
			return (ERR);
		i++;
	}
	return (OK);
}
