/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/09/30 19:35:57 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

int	take_forks(t_philo *ph)
{
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;

	if (ph->id % 2 == 0)
	{
		fork_1 = ph->left;
		fork_2 = ph->right;
	}
	else
	{
		fork_1 = ph->right;
		fork_2 = ph->left;
	}
	pthread_mutex_lock(fork_1);
	pthread_mutex_lock(fork_2);
	return (OK);
}

int	routine(t_philo *ph)
{
	while (1)
	{
		take_forks(ph);
	}
	return(OK);
}
