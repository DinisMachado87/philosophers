/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:01 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 13:06:03 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define ERR		-1
# define OK			0
# define END		1
# define ANY_CHILD	-1

# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_philosopher	t_philo;

enum e_dead_or_full
{
	DEAD,
	FULL,
};

enum e_track
{
	SEM_FORKS,
	SEM_WRITE,
	SEM_END,
	MONITOR_THRD,
	END_MONITOR_THRD,
};

typedef struct s_state
{
	long long		n_philos;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	long long		n_eats;
	long long		start;
	int				end;
	int				err;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_end;
	pid_t			*pids;
	struct timeval	time;
	int				track;
}	t_state;

struct s_philosopher
{
	long long		id;
	long long		nxt_death;
	long long		n_eats;
	t_state			*s;
	pthread_t		monitor_thread;
	pthread_t		end_monitor_thread;
	struct timeval	time;
};

// init
int			init_state(int argc, char **argv, t_state *s);
int			init_semaphores(t_state *s);
int			init_philosophers(t_state *s);

// src
void		philo_routine(t_philo *ph);
void		*monitor_death(void *arg);
void		*monitor_end(void *arg);

// utils
int			is_end(t_state *s);
long long	now(struct timeval *time, t_state *s);
int			wait_and_watch(size_t duration, t_state *s, struct timeval *time);
int			safe_print(char *str, t_philo *ph, t_state *s);
int			set_and_print_error(t_state *s, char *str);
int			safe_sem_wait(sem_t *sem, t_state *s);
int			safe_sem_post(sem_t *sem, t_state *s);
int			track(int *track, int i_tracked, t_state *s, int ret);
long long	ft_atoll(char *str_num);
int			safe_malloc(void **ptr, size_t size, t_state *s);

// cleanup
void		cleanup_semaphores(t_state *s);
void		free_all(t_state *s);

#endif
