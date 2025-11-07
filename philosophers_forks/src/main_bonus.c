/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 13:47:58 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

static int	handle_philosophers_exit(t_state *s)
{
	pid_t	exited_pid;
	int		ret;
	int		status;
	int		i;

	ret = OK;
	i = 0;
	while (i < s->n_philos)
	{
		exited_pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != FULL)
		{
			kill_pids_left(s);
			if (WEXITSTATUS(status) == ERR)
				ret = ERR;
			break ;
		}
		null_pid(s, exited_pid);
		i++;
	}
	while (i < s->n_philos)
		waitpid(s->pids[i++], NULL, 0);
	return (ret);
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
		return (handle_philosophers_exit(&s));
	return (free_all(&s), ERR);
}
