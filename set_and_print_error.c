/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_print_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:28:59 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/28 01:20:58 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_and_print_error(t_state *s, char *str)
{
	pthread_mutex_lock(&s->mtx_end);
	s->end = ERR;
	pthread_mutex_unlock(&s->mtx_end);
	pthread_mutex_lock(&s->print);
	printf(str);
	pthread_mutex_unlock(&s->print);
	return (ERR);
}
