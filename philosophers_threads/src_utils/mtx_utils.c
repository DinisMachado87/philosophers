/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:08:49 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/31 14:14:57 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

int	mtx_lock_tracked(pthread_mutex_t *mtx, t_state *s)
{
	if (OK != pthread_mutex_lock(mtx))
		return (set_and_print_error(s, "Error: Mutex lock failure"));
	return (OK);
}

int	mtx_unlock_tracked(pthread_mutex_t *mtx, t_state *s)
{
	if (OK != pthread_mutex_unlock(mtx))
		return (set_and_print_error(s, "Error: Mutex lock failure"));
	return (OK);
}

int	track(int *track, int i_tracked, t_state *s, int ret)
{
	if (OK == ret)
	{
		*track |= (1 << i_tracked);
		return (OK);
	}
	return (set_and_print_error(s, "Err: init_mutex/create_thread error"));
}
