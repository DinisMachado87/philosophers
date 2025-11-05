/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 02:15:52 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	take_forks(t_philo *ph, t_state *s)
{
	if (OK != safe_sem_wait(s->sem_forks))
		return (ERR);
	if (OK != safe_print("has taken a fork", ph, s))
	{
		safe_sem_post(s->sem_forks);
		return (ERR);
	}
	if (OK != safe_sem_wait(s->sem_forks))
	{
		safe_sem_post(s->sem_forks);
		return (ERR);
	}
	if (OK != safe_print("has taken a fork", ph, s))
	{
		safe_sem_post(s->sem_forks);
		safe_sem_post(s->sem_forks);
		return (ERR);
	}
	return (OK);
}

static int	eat(t_philo *ph, t_state *s)
{
	if (OK != safe_print("is eating", ph, s))
		return (ERR);
	
	// Update death time when eating actually starts
	ph->nxt_death = now(&ph->time) + s->t_die;
	ph->n_eats++;
	
	if (OK != wait_and_watch(s->t_eat))
		return (ERR);
	
	// Check if philosopher is full
	if (s->n_eats > 0 && ph->n_eats >= s->n_eats)
	{
		close_semaphores(s);
		exit(FULL);
	}
	
	if (OK != safe_sem_post(s->sem_forks)
		|| OK != safe_sem_post(s->sem_forks))
		return (ERR);
	
	return (OK);
}

void	philo_routine(t_philo *ph)
{
	t_state		*s;
	pthread_t	monitor;

	s = ph->s;
	free_and_null_pids(s);
	
	// Create death monitor thread
	if (OK != pthread_create(&monitor, NULL, death_monitor, ph))
	{
		close_semaphores(s);
		exit(ERR);
	}
	pthread_detach(monitor);
	
	// Stagger even philosophers
	if (ph->id % 2 == 0)
		usleep(1000);
	
	// Main philosopher loop
	while (OK == take_forks(ph, s)
		&& OK == eat(ph, s)
		&& OK == safe_print("is sleeping", ph, s)
		&& OK == wait_and_watch(s->t_sleep)
		&& OK == safe_print("is thinking", ph, s))
		;
	
	close_semaphores(s);
	exit(ERR);
}
