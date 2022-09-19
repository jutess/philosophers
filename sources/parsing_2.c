/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:46:03 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 12:56:22 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] == '\t'))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	return (res * sign);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	verif_if_nb_are_int(char **tab)
{
	int	j;

	j = 1;
	while (tab[j])
	{
		if (ft_strlen(tab[j]) > 11)
			return (1);
		if (ft_atoi(tab[j]) > 2147483647)
			return (1);
		j++;
	}
	return (0);
}

int	verif_if_zero(char **tab)
{
	int	j;

	j = 1;
	while (tab[j])
	{
		if (ft_atoi(tab[j]) == 0)
			return (1);
		j++;
	}
	return (0);
}

int	launch_parsing(int nb_args, char **argv)
{
	if (nb_args != 4 && nb_args != 5)
		return (ft_error("Nb args are wrong."));
	if (verif_if_args_are_numbers(argv) != 0)
		return (ft_error("Args aren't only composed of numbers."));
	if (verif_if_nb_are_neg(argv) != 0)
		return (ft_error("At least one nb is negative."));
	if (verif_if_nb_are_int(argv) != 0)
		return (ft_error("Only int numbers are accepted."));
	if (verif_if_zero(argv) != 0)
		return (ft_error("Number zero isn't accepted in arguments"));
	return (0);
}
