/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:59 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/04 17:01:33 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	launch_death_monitor(t_philo *ph)
{
	if (OK != pthread_create(&ph->monitor, NULL, death_monitor, ph)
		|| OK != pthread_detach(ph->monitor))
	{
		close_semaphores(ph->s);
		exit (ERR);
	}
	return (OK);
}

void	open_unique_sem(char *uniname, t_philo *ph, t_state *s)
{
	unique_name(uniname, ph->id);
	sem_unlink(uniname);
	ph->sem_death_lock = sem_open(uniname, O_CREAT, 0644, 1);
	if (ph->sem_death_lock == SEM_FAILED)
	{
		close_semaphores(s);
		exit(ERR);
	}
}
