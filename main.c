/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 16:22:22 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

/* number_of_philosophers time_to_die time_to_eat
 * time_to_sleep, [number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	t_state			s;
	t_philo			*phs;

	if (init_all(argc, argv, &s, &phs))
		return (ERR);
	return (OK);
}
