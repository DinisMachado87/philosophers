/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/04 17:01:22 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	update_next_death(t_philo *ph, t_state *s)
{
	if (OK != safe_sem_wait(ph->sem_death_lock))
		return (ERR);
	ph->nxt_death = now(&ph->time) + s->t_die;
	if (OK != safe_sem_post(ph->sem_death_lock))
		return (ERR);
	return (OK);
}

static int	take_forks(t_philo *ph, t_state *s)
{
	int	forks_taken;

	forks_taken = 0;
	while (forks_taken < 2)
	{
		if (!(OK == safe_sem_wait(s->sem_forks) && ++forks_taken)
			|| OK != safe_print("has taken a fork", ph, s))
		{
			while (forks_taken--)
				safe_sem_post(s->sem_forks);
			return (ERR);
		}
	}
	return (update_next_death(ph, s));
}

static void	if_philo_full_exit(t_state *s, t_philo *ph)
{
	if (s->n_eats > 0 && ph->n_eats >= s->n_eats)
	{
		close_semaphores(s);
		exit (FULL);
	}
}

static int	eat(t_philo *ph, t_state *s)
{
	wait_and_watch(s->t_eat);
	ph->n_eats++;
	if_philo_full_exit(s, ph);
	if (OK == safe_sem_post(s->sem_forks)
		&& OK == safe_sem_post(s->sem_forks))
		return (OK);
	return (ERR);
}

void	philo_routine(t_philo *ph)
{
	t_state	*s;
	char	uniname[50];

	s = ph->s;
	free_and_null_pids(s);
	open_unique_sem(uniname, ph, s);
	launch_death_monitor(ph);
	usleep(ph->id % 2 * s->t_eat * 500);
	while (OK == take_forks(ph, s)
		&& OK == safe_print("is eating", ph, s)
		&& OK == eat(ph, s)
		&& OK == safe_print("is sleeping", ph, s)
		&& OK == wait_and_watch(s->t_sleep)
		&& OK == safe_print("is thinking", ph, s))
		;
	sem_close(ph->sem_death_lock);
	sem_unlink(uniname);
	close_semaphores(s);
	exit (ERR);
}
