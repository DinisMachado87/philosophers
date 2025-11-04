/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:01 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/04 14:50:02 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define ERR		-1
# define OK			0

# include <stdio.h>
# include <limits.h>
# include <stddef.h>
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
	struct timeval	time;
};

// src
void		philo_routine(t_philo *ph);

// init
int			init_state(int argc, char **argv, t_state *s);
int			init_semaphores(t_state *s);
int			init_philosophers(t_state *s);

// utils
long long	now(struct timeval *time);
int			wait_and_watch(size_t duration, struct timeval *time, t_philo *ph);
int			safe_print(char *str, t_philo *ph, t_state *s);
int			ret_and_print_err(char *str);
int			safe_sem_wait(sem_t *sem);
int			safe_sem_post(sem_t *sem);
int			track(int *track, int i_tracked, int ret);
long long	ft_atoll(char *str_num);
int			safe_calloc(void **ptr, size_t size);

// cleanup
void		close_semaphores(t_state *s);
void		kill_pids_left(t_state *s);
void		free_and_null_pids(t_state *s);
void		free_all(t_state *s);

#endif
