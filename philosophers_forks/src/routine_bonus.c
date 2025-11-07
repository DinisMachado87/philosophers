/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 15:25:05 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline void	cleanup_exit(t_state *s, int status)
{
	safe_sem_post_forks(status, s->sem_forks, s);
	close_semaphores(s);
	exit(status);
}

static int	take_forks(t_philo *ph, t_state *s)
{
	if (OK == track(&s->track, FORK_1,
			safe_sem_wait(s->sem_forks))
		&& OK == safe_print("has taken a fork", ph, s)
		&& OK == track(&s->track, FORK_2,
			safe_sem_wait(s->sem_forks))
		&& OK == safe_print_two("has taken a fork",
			"is eating", ph, s))
		return (OK);
	return (ERR);
}

static int	update_next_death(t_philo *ph, t_state *s)
{
	if (OK != safe_sem_wait(s->sem_next_death))
		return (ERR);
	ph->nxt_death = ph->cache_now + s->t_die;
	if (OK != safe_sem_post(s->sem_next_death))
		return (ERR);
	return (OK);
}

static int	eat(t_philo *ph, t_state *s)
{
	update_next_death(ph, s);
	ph->n_eats++;
	if (s->n_eats && ph->n_eats >= s->n_eats)
		cleanup_exit(s, FULL);
	if (OK != usleep(s->t_eat * 1000))
		return (ret_and_print_err("Err: usleep"));
	safe_sem_post_forks(OK, s->sem_forks, s);
	return (OK);
}

void	philo_routine(t_philo *ph)
{
	t_state		*s;
	pthread_t	monitor;

	s = ph->s;
	free_and_null_pids(s);
	if (OK != pthread_create(&monitor, NULL, death_monitor, ph))
		cleanup_exit(s, ERR);
	pthread_detach(monitor);
	usleep((ph->id % 2) * 1000);
	while (OK == take_forks(ph, s)
		&& OK == eat(ph, s)
		&& OK == safe_print("is sleeping", ph, s)
		&& OK == usleep(s->t_sleep * 1000)
		&& OK == safe_print("is thinking", ph, s)
		&& OK == usleep(1000))
		;
	cleanup_exit(s, ERR);
}
