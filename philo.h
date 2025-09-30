/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:26:01 by dimachad          #+#    #+#             */
/*   Updated: 2025/09/30 19:54:38 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#define	ERR	-1
#define	OK	0

#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_state {
	pthread_mutex_t	print;
	ssize_t			n_philos;
	pthread_mutex_t	*forks;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	ssize_t			n_eats;
}	t_state;

typedef struct s_philosopher {
	t_state			*s;
	ssize_t			id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		life;
}	t_philo;

int	init_state(int argc, char **argv, t_state *s);
int	routine(t_philo *ph);
int safe_print(char *str, t_philo *ph);

#endif
