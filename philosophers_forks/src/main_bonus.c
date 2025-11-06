/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 21:27:19 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

static void	handle_philosophers_exit(t_state *s)
{
	pid_t	exited_pid;
	int		status;
	int		i;

	i = 0;
	while (i < s->n_philos)
	{
		exited_pid = waitpid(-1, &status, 0);
		if (exited_pid < 0
			|| (WIFEXITED(status) && WEXITSTATUS(status) != FULL))
		{
			kill_pids_left(s);
			break ;
		}
		i++;
	}
	while (i < s->n_philos)
	{
		waitpid(s->pids[i], NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	const char	*err_str = "Usage: %s n_philo t_die t_eat t_sleep [n_eats]\n";
	t_state		s;

	if (argc != 5 && argc != 6)
		return (printf(err_str, argv[0]), ERR);
	if (OK == init_state(argc, argv, &s)
		&& OK == init_semaphores(&s)
		&& OK == init_philosophers(&s))
		handle_philosophers_exit(&s);
	return (free_all(&s), 0);
}
