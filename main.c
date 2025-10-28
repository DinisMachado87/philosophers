/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 19:39:24 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* number_of_philosophers time_to_die time_to_eat
 * time_to_sleep, [number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	t_state	s;
	t_philo	*phs;

	if (argc != 5 && argc != 6)
		return (
			printf(
				"Usage %s: n_philo, t_die, t_eat, t_sleep, [opt:n_eats]\n",
				argv[0]),
			ERR);
	if (OK != init_state(argc, argv, &s)
		|| OK != pthread_mutex_init(&s.print, NULL)
		|| OK != init_forks(&s)
		|| OK != init_philos(&phs, &s))
		return (ERR);
	return (OK);
}
