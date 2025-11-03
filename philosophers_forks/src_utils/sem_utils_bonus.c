/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:38:00 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 04:37:53 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	safe_sem_wait(sem_t *sem, t_state *s)
{
	if (OK != sem_wait(sem))
		return (set_and_print_error(s, "Error: sem_wait failure\n"));
	return (OK);
}

int	safe_sem_post(sem_t *sem, t_state *s)
{
	if (OK != sem_post(sem))
		return (set_and_print_error(s, "Error: sem_post failure\n"));
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

int	safe_malloc(void **ptr, size_t size, t_state *s)
{
	*ptr = malloc(size);
	if (!*ptr)
		return (set_and_print_error(s, "Error: Malloc\n"));
	return (OK);
}
