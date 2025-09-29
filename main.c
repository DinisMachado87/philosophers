/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/09/30 00:11:03 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *ph, t_state *s, size_t i)
{
	ph->left = i - 1;
	ph->right = (i + 1) % s->n_philos;
	return (1);
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
	if (!init_state(argc, argv, &s))
		return (1);
	ph = malloc(s.n_philos * sizeof(t_philo));
	while (i < s.n_philos)
	{
		if (!init_philo(&ph[i], &s, i))
			return (1);
		i++;
	}
}
