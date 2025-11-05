/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:38:00 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 14:21:32 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	safe_sem_wait(sem_t *sem)
{
	if (OK != sem_wait(sem))
		return (ret_and_print_err("Error: sem_wait failure\n"));
	return (OK);
}

int	safe_sem_post(sem_t *sem)
{
	if (OK != sem_post(sem))
		return (ret_and_print_err("Error: sem_post failure\n"));
	return (OK);
}

int	track(int *track, int i_tracked, int ret)
{
	if (OK == ret)
	{
		*track |= (1 << i_tracked);
		return (OK);
	}
	return (ret_and_print_err("Err: init_mutex/create_thread error"));
}

int	safe_calloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!*ptr)
		return (ret_and_print_err("Error: Malloc\n"));
	memset(*ptr, 0, size);
	return (OK);
}
