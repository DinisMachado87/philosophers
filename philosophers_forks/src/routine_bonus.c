/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/06 02:59:38 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline void	cleanup_exit(t_state *s, int status)
{
	close_semaphores(s);
	printf("FULL");
	exit(status);
}

static int	take_forks(t_philo *ph, t_state *s)
{
	int	fork_count;

	fork_count = 0;
	if (OK == safe_sem_wait(s->sem_forks) && ++fork_count
		&& OK == safe_print("has taken a fork", ph, s)
		&& OK == safe_sem_wait(s->sem_forks) && ++fork_count
		&& OK == safe_print_two("has taken a fork",
			"is eating", ph, s))
	{
		return (OK);
	}
	else
		return (
			safe_sem_post_forks(s->sem_forks, fork_count,
				ERR));
}

static inline int	is_philo_full(t_state *s, t_philo *ph)
{
	return (s->n_eats && ph->n_eats >= s->n_eats);
}

static int	eat(t_philo *ph, t_state *s)
{
	const long long	eat_end = ph->cache_now + s->t_eat;
	long long		remaining;

	ph->nxt_death = now(ph) + s->t_die;
	ph->n_eats++;
	if (is_philo_full(s, ph))
		cleanup_exit(s, FULL);
	remaining = eat_end - now(ph);
	if (remaining > 0
		&& OK != usleep(remaining * 1000))
		return (safe_sem_post_forks(s->sem_forks, 2, ERR));
	return (safe_sem_post_forks(s->sem_forks, 2, OK));
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
		&& OK == safe_print("is thinking", ph, s))
		;
	cleanup_exit(s, ERR);
}
