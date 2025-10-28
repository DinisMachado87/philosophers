/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:44:59 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 17:45:12 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_state *s)
{
	const char	*err_str = "ERR: init_forks:";
	ssize_t		i;

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
