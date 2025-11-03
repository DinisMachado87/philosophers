/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:25:28 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 12:48:23 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	terminate_philosophers(t_state *s)
{
	int	status;

	if (!s->pids)
		return ;
	while (waitpid(-1, &status, 0) > 0)
		;
}

int	main(int argc, char **argv)
{
	const char	*err_str = "Usage: %s n_philo t_die t_eat t_sleep [n_eats]\n";
	t_state		s;

	if (argc != 5 && argc != 6)
		return (printf(err_str, argv[0]), ERR);
	if (OK == init_state(argc, argv, &s)
		&& OK == init_semaphores(&s)
		&& OK == safe_malloc((void **)&s.pids,
			(sizeof(pid_t) * s.n_philos), &s))
		init_philosophers(&s);
	terminate_philosophers(&s);
	return (free_all(&s), 0);
}
