/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:27:42 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 14:36:05 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	get_time_nw(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*threads_do(void *arg)
{
	t_phi	*philo;

	philo = arg;
	if (philo->phil_id % 2 == 0 && philo->comm->nb_phil > 1)
		usleep(philo->comm->time_eating * 1000);
	while (1)
	{
		philo_takes_forks(philo);
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		philo_is_thinking(philo);
	}
	return (NULL);
}

void	check_meals_eaten(t_phi *philo)
{
	int	i;
	int	nb_phi;
	int	nb_times_to_eat;

	i = 0;
	nb_phi = philo->comm->nb_phil;
	nb_times_to_eat = philo->comm->number_of_times_each_phi_must_eat;
	while (i < nb_phi)
	{
		if (philo->nb_meals < nb_times_to_eat)
			return ;
		philo = philo->next;
		i++;
	}
	pthread_mutex_lock(&philo->comm->mutex_printf);
	printf("all philosophers have eaten %i times\n", nb_times_to_eat);
	pthread_mutex_unlock(&philo->comm->mutex_exit);
}

void	check_death_philo(t_phi *philo)
{
	int				i;
	int				nb_phi;
	long long int	time_nw;

	i = 0;
	nb_phi = philo->comm->nb_phil;
	time_nw = get_time_nw();
	while (i < nb_phi)
	{
		if (time_nw - philo->time_bg_eating > philo->comm->time_to_die)
		{
			pthread_mutex_lock(&philo->comm->mutex_printf);
			get_time_spent_since_begin(philo->comm);
			disp_to_term(philo, "died");
			pthread_mutex_unlock(&philo->comm->mutex_exit);
		}
		philo = philo->next;
		i++;
	}
}

void	*th_omniscient(void *arg)
{
	t_phi	*philo;

	philo = arg;
	while (1)
	{
		check_death_philo(philo);
		if (philo->comm->number_of_times_each_phi_must_eat > 0)
			check_meals_eaten(philo);
		usleep (150);
	}
	return (NULL);
}
