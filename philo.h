/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:01 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/28 15:56:06 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define END	-2
# define ERR	-1
# define OK		0

# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher	t_philo;

typedef struct s_state
{
	long long		n_philos;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	long long		n_eats;
	long long		start;
	int				end;
	pthread_mutex_t	mtx_end;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	struct timeval	time;
}	t_state;

struct s_philosopher
{
	t_state			*s;
	long long		id;
	long long		last_meal;
	long long		n_eats;
	pthread_mutex_t	mtx_philo;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_t		life;
	struct timeval	time;
};

// init
int			init_state(int argc, char **argv, t_state *s);
int			init_forks(t_state *s);
int			init_philos(t_philo **phs, t_state *s);

int			eat(t_philo *ph, t_state *s);
void		*routine(void *philosopher);

int			is_end(t_state *s);
int			now(struct timeval *time, t_state *s);
int			wait_and_watch(size_t duration, t_state *s, struct timeval *tv);
int			safe_print(char *str, t_philo *ph, t_state *s);
int			set_and_print_error(t_state *s, char *str);

long long	ft_atoll(char *original);

#endif
