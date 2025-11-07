/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/06 03:02:33 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_philos_and_forks(t_state *s)
{
	size_t	size_forks;
	size_t	size_philos;

	size_forks = s->n_philos * sizeof(pthread_mutex_t);
	size_philos = s->n_philos * sizeof(t_philo);
	if (OK == safe_malloc((void **)&s->mtx_forks, size_forks, s)
		&& OK == safe_malloc((void **)&s->philos, size_philos, s))
		return (OK);
	return (set_and_print_error(s, "Error: Malloc philos and forks"));
}

/* number_of_philosophers time_to_die time_to_eat
 * time_to_sleep, [number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	const char	*err_str = "Usage %s: "
		"n_philo, t_die, t_eat, t_sleep, [opt:n_eats]\n";
	t_state		s;

	if (argc != 5 && argc != 6)
		return (printf(err_str, argv[0]), ERR);
	s.track = 0;
	s.start = now(&s.time, &s);
	if (OK == init_state(argc, argv, &s)
		&& OK == track(&s.track, STATE_MTX, &s,
			pthread_mutex_init(&s.state_mtx, NULL))
		&& OK == allocate_philos_and_forks(&s)
		&& OK == init_forks(&s)
		&& OK == init_philos(s.philos, &s))
		monitor(&s);
	free_all(&s);
	return (s.err);
}
