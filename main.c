/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:51:43 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 14:35:44 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	main(int argc, char **argv)
{
	t_com	*com_struct;
	t_phi	*philos_l;

	com_struct = NULL;
	philos_l = NULL;
	if (launch_parsing(argc -1, argv) != 0)
		return (1);
	if (make_ptr_struct(&com_struct, &philos_l) != 0)
		return (1);
	if (in_com_var(com_struct, argc, argv) != 0)
		return (1);
	if (init_phi_linked_list(philos_l, com_struct) != 0)
		return (1);
	if (init_and_launch_threads(philos_l) != 0)
		return (1);
	pthread_mutex_lock(&philos_l->comm->mutex_exit);
	pthread_mutex_lock(&philos_l->comm->mutex_exit);
	free (philos_l);
	return (0);
}
