/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:58:18 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 13:12:47 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	make_ptr_struct(t_com **com_struct, t_phi **philos_l)
{
	*com_struct = malloc(sizeof(t_com));
	if (! *com_struct)
		return (1);
	*philos_l = malloc(sizeof(t_phi));
	if (! *philos_l)
		return (1);
	return (0);
}

int	lch_phi_th(t_phi *philos_l, pthread_t *th, pthread_t th_meals)
{
	int		i;
	t_phi	*first_node;

	i = 0;
	first_node = philos_l;
	if (pthread_create(&th_meals, NULL, &th_omniscient, first_node) != 0)
		return (1);
	while (i < philos_l->comm->nb_phil)
	{
		if (pthread_create(&th[i], NULL, &threads_do, philos_l) != 0)
			return (1);
		philos_l = philos_l->next;
		i++;
	}
	return (0);
}

int	init_and_launch_threads(t_phi *philos_l)
{
	pthread_t	*th;
	pthread_t	th_meals;
	int			i;
	int			nb_of_phi;

	nb_of_phi = philos_l->comm->nb_phil;
	i = 0;
	th = NULL;
	th = malloc(sizeof(pthread_t) * philos_l->comm->nb_phil + 1);
	if (! th)
		return (1);
	th[nb_of_phi] = NULL;
	if (lch_phi_th(philos_l, th, th_meals) != 0)
		return (1);
	free(th);
	return (0);
}
