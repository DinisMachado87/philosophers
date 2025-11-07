/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:48:24 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 13:49:03 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	null_pid(t_state *s, pid_t pid)
{
	long long	i;

	i = 0;
	while (i < s->n_philos)
	{
		if (s->pids[i] == pid)
		{
			s->pids[i] = 0;
			break ;
		}
		i++;
	}
}

void	kill_pids_left(t_state *s)
{
	long long	i;

	if (!s->n_philos || !s->pids)
		return ;
	i = 0;
	while (i < s->n_philos)
	{
		if (s->pids[i])
			kill(s->pids[i], SIGKILL);
		i++;
	}
}
