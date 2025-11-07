/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:01 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 13:18:49 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define ERR	-1
# define OK		0

# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_philosopher	t_philo;

enum e_dead_or_full
{
	FULL,
	DEAD,
};

enum e_track
{
	SEM_FORKS,
	SEM_WRITE,
	SEM_NEXT_DEATH,
	FORK_1,
	FORK_2,
};

typedef struct s_state
{
	long long		n_philos;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	long long		n_eats;
	long long		start;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_next_death;
	pid_t			*pids;
	int				track;
}	t_state;

struct s_philosopher
{
	long long		id;
	long long		nxt_death;
	long long		n_eats;
	long long		cache_now;
	t_state			*s;
	pthread_t		monitor;
};

// src
void		philo_routine(t_philo *ph);
void		*death_monitor(void *arg);

// init
int			init_state(int argc, char **argv, t_state *s);
int			init_semaphores(t_state *s);
int			init_philosophers(t_state *s);

// utils
long long	now(t_philo *ph);
int			safe_print(char *str, t_philo *ph, t_state *s);
int			safe_print_two(char *str, char *str2, t_philo *ph, t_state *s);
int			ret_and_print_err(char *str);
int			safe_sem_wait(sem_t *sem);
int			safe_sem_post(sem_t *sem);
int			safe_sem_post_forks(int ret, sem_t *sem, t_state *s);
int			track(int *track, int i_tracked, int ret);
long long	ft_atoll(char *str_num);
int			safe_calloc(void **ptr, size_t size);

// cleanup
void		close_semaphores(t_state *s);
void		kill_pids_left(t_state *s);
void		free_and_null_pids(t_state *s);
void		null_pid(t_state *s, pid_t pid);
void		free_all(t_state *s);

#endif
