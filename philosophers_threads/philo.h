/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:01 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 16:50:26 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR	-1
# define OK		0
# define END	1

# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher	t_philo;

enum e_track_philo
{
	FORK_MTX,
	PHILO_MTX,
	PHILO_THRD,
	FORK_1,
	FORK_2,
};

enum e_track_state
{
	STATE_MTX,
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
	pthread_mutex_t	state_mtx;
	pthread_mutex_t	*mtx_forks;
	t_philo			*philos;
	struct timeval	time;
	int				track;
}	t_state;

struct s_philosopher
{
	t_state			*s;
	long long		id;
	long long		nxt_death;
	long long		n_eats;
	pthread_mutex_t	mtx_philo;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_t		life;
	struct timeval	time;
	int				track;
};

// init
int			init_state(int argc, char **argv, t_state *s);
int			init_forks(t_state *s);
int			init_philos(t_philo *ph, t_state *s);

int			safe_malloc(void **ptr, size_t size, t_state *s);
// src
int			eat(t_philo *ph, t_state *s);
void		*routine(void *philosopher);
void		monitor(t_state *s);
// utils
int			is_end(t_state *s);
long long	now(struct timeval *time, t_state *s);
int			wait_and_watch(size_t duration, t_state *s, struct timeval *tv);
int			safe_print(char *str, t_philo *ph, t_state *s);
int			set_and_print_error(t_state *s, char *str);

int			mtx_lock_tracked(pthread_mutex_t *mtx, t_state *s);
int			mtx_unlock_tracked(pthread_mutex_t *mtx, t_state *s);
int			track(int *track, int i_tracked, t_state *s, int ret);

long long	ft_atoll(char *str_num);

void		free_track_arrs(t_state *s);
void		free_all(t_state *s);

#endif
