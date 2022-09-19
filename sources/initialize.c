/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:45:40 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 14:39:00 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	rec_args_in_variables(t_com *com_struct, int argc, char **av)
{
	com_struct->nb_phil = (int)ft_atoi(av[1]);
	com_struct->time_to_die = (int)ft_atoi(av[2]);
	com_struct->time_eating = (int)ft_atoi(av[3]);
	com_struct->time_sleeping = (int)ft_atoi(av[4]);
	if (argc == 6)
		com_struct->number_of_times_each_phi_must_eat = (int)ft_atoi(av[5]);
	else
		com_struct->number_of_times_each_phi_must_eat = -1;
	return (0);
}

int	in_com_var(t_com *com_struct, int argc, char **argv)
{
	struct timeval	time;
	long long int	nb;
	int				i;
	int				have_to_eat;

	have_to_eat = 0;
	i = 0;
	if (rec_args_in_variables(com_struct, argc, argv) != 0)
		return (1);
	have_to_eat = com_struct->number_of_times_each_phi_must_eat;
	com_struct->time_at_bg = get_time_nw();
	com_struct->time_spent = 0;
	com_struct->is_a_phi_dead = 0;
	if (pthread_mutex_init(&com_struct->mutex_printf, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&com_struct->mutex_exit, NULL) != 0)
		return (1);
	return (0);
}

int	in_philo_datas(t_phi *philos, t_com *com_struct, int i)
{
	struct timeval	struc;

	philos->comm = com_struct;
	philos->phil_id = i;
	philos->time_spt_eating = 0;
	philos->time_since_last_eat = 0;
	philos->time_spent_sleep = 0;
	philos->nb_meals = 0;
	pthread_mutex_init(&philos->mutex_fork, NULL);
	if (gettimeofday(&struc, NULL) != 0)
		return (1);
	philos->time_bg_eating = (struc.tv_sec * 1000 + struc.tv_usec / 1000);
	return (0);
}

int	init_phi_linked_list(t_phi *philos_l, t_com *com_struct)
{
	t_phi	*next_node;
	t_phi	*first_node;
	int		i;

	next_node = NULL;
	first_node = philos_l;
	i = 0;
	while (i < (com_struct->nb_phil - 1))
	{
		if (in_philo_datas(philos_l, com_struct, i + 1) != 0)
			return (1);
		next_node = malloc(sizeof(t_phi));
		if (! next_node)
			return (1);
		philos_l->next = next_node;
		next_node->prev = philos_l;
		next_node->next = NULL;
		philos_l = next_node;
		i++;
	}
	if (in_philo_datas(philos_l, com_struct, i + 1) != 0)
		return (1);
	philos_l->next = first_node;
	first_node->prev = philos_l;
	return (0);
}
