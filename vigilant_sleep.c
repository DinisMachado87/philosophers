/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vigilant_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:55:16 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 02:38:20 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_and_watch(size_t duration, int *end, struct timeval *tv)
{
	size_t			sleep_start;
	size_t			time_slept;

	sleep_start = gettimeofday(tv, NULL);
	time_slept = gettimeofday(tv, NULL) - sleep_start;
	while (time_slept > duration)
	{
		time_slept = gettimeofday(tv, NULL) - sleep_start;
		if (*end)
			return (END);
		usleep(500);
	}
	return (OK);
}
