/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:48:37 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/31 16:47:29 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

int	safe_malloc(void **ptr, size_t size, t_state *s)
{
	*ptr = malloc(size);
	if (!*ptr)
		return (set_and_print_error(s, "Error: Malloc\n"));
	return (OK);
}
