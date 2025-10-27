/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:01 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 17:27:18 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define END	-2
# define ERR	-1
# define OK		0

# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_state
{
	long long		n_philos;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	long long		n_eats;
	long long		start;
	int				end;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	struct timeval	tv;
}	t_state;

typedef struct s_philosopher
{
	t_state			*s;
	ssize_t			id;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_t		life;
}	t_philo;

int			init_all(int argc, char **argv, t_state *s, t_philo **phs);
long long	ft_atoll(char *original);
int			routine(void *philosopher);
int			wait_and_watch(size_t duration, int *end, struct timeval *tv);

#endif
