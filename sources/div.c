/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 21:35:19 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 13:12:47 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_time_spent_since_begin(t_com *d)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	d->time_spent = (time.tv_sec * 1000 + time.tv_usec / 1000) - d->time_at_bg;
	return (0);
}

void	disp_to_term(t_phi *philos_l, char *str)
{
	printf("%i %i %s\n", philos_l->comm->time_spent, philos_l->phil_id, str);
}
