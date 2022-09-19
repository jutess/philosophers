/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:38:26 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 10:43:38 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_takes_forks(t_phi *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	pthread_mutex_lock(&philo->comm->mutex_printf);
	get_time_spent_since_begin(philo->comm);
	disp_to_term(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->comm->mutex_printf);
	pthread_mutex_lock(&philo->prev->mutex_fork);
	pthread_mutex_lock(&philo->comm->mutex_printf);
	get_time_spent_since_begin(philo->comm);
	disp_to_term(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->comm->mutex_printf);
	return (0);
}

int	philo_is_sleeping(t_phi *philo)
{
	pthread_mutex_lock(&philo->comm->mutex_printf);
	philo->time_bg_sleep = get_time_nw();
	get_time_spent_since_begin(philo->comm);
	disp_to_term(philo, "is sleeping");
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->comm->mutex_printf);
	while (philo->time_spent_sleep < philo->comm->time_sleeping)
	{
		philo->comm->time_nw = get_time_nw();
		philo->time_spent_sleep = philo->comm->time_nw - philo->time_bg_sleep;
		usleep(150);
	}
	philo->time_spent_sleep = 0;
	return (0);
}

void	philo_is_thinking(t_phi *philo)
{
	pthread_mutex_lock(&philo->comm->mutex_printf);
	get_time_spent_since_begin(philo->comm);
	disp_to_term(philo, "is thinking");
	pthread_mutex_unlock(&philo->comm->mutex_printf);
}

int	philo_is_eating(t_phi *philo)
{
	pthread_mutex_lock(&philo->comm->mutex_printf);
	get_time_spent_since_begin(philo->comm);
	philo->time_bg_eating = get_time_nw();
	disp_to_term(philo, "is eating");
	pthread_mutex_unlock(&philo->comm->mutex_printf);
	while (philo->time_spt_eating < philo->comm->time_eating)
	{
		philo->comm->time_nw = get_time_nw();
		philo->time_spt_eating = philo->comm->time_nw - philo->time_bg_eating;
		usleep(150);
	}
	philo->time_spt_eating = 0;
	pthread_mutex_unlock(&philo->mutex_fork);
	pthread_mutex_unlock(&philo->next->mutex_fork);
	return (0);
}
