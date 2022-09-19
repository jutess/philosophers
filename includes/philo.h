/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:52:50 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 14:40:36 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_com_struct
{
	int					nb_phil;
	int					time_to_die;
	int					time_eating;
	int					time_sleeping;
	int					number_of_times_each_phi_must_eat;
	int					time_spent;
	long long int		time_at_bg;
	long long int		time_nw;
	int					is_a_phi_dead;
	pthread_mutex_t		mutex_exit;
	pthread_mutex_t		mutex_printf;
}	t_com;

typedef struct s_philos_var
{
	long long int		time_bg_eating;
	int					time_spt_eating;
	int					time_spent_sleep;
	int					time_bg_sleep;
	int					time_since_last_eat;
	int					phil_id;
	int					nb_meals;
	t_com				*comm;
	struct s_philos_var	*next;
	struct s_philos_var	*prev;
	pthread_mutex_t		mutex_fork;
}	t_phi;

//div.c
int				get_time_spent_since_begin(t_com *d);
void			disp_to_term(t_phi *philos_l, char *str);
//initialize.c
int				rec_args_in_variables(t_com *com_struct, int argc, char **argv);
int				in_com_var(t_com *com_struct, int argc, char **argv);
int				in_philo_datas(t_phi *philos_l, t_com *com_struct, int i);
int				init_phi_linked_list(t_phi *philos_l, t_com *com_struct);
//parsing_1.c
int				ft_error(char *str);
int				verif_if_args_are_numbers(char **argv);
int				verif_if_nb_are_neg(char **argv);
int				ft_isdigit(int c);
// parsing_2.c
long int		ft_atoi(const char *str);
int				ft_strlen(char *str);
int				verif_if_nb_are_int(char **tab);
int				verif_if_zero(char **tab);
int				launch_parsing(int nb_args, char **argv);
//launch.c
int				make_ptr_struct(t_com **com_struct, t_phi **philos_l);
int				lch_phi_th(t_phi *philos_l, pthread_t *th, pthread_t th_meals);
int				init_and_launch_threads(t_phi *philos_l);
//philo_states.c
int				philo_takes_forks(t_phi *philo);
int				philo_is_sleeping(t_phi *philo);
void			philo_is_thinking(t_phi *philo);
int				philo_is_eating(t_phi *philo);
//threads_do.c
long long int	get_time_nw(void);
void			*threads_do(void *arg);
void			check_meals_eaten(t_phi *philo);
void			check_death_philo(t_phi *philo);
void			*th_omniscient(void *arg);

#endif