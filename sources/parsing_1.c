/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:17:50 by jtessier          #+#    #+#             */
/*   Updated: 2022/09/16 12:54:27 by jtessier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *str)
{
	printf("Error :\n");
	printf("%s\n", str);
	return (1);
}

int	verif_if_args_are_numbers(char **argv)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (argv[j])
	{
		i = 0;
		if (argv[j][i] == '+' || argv[j][i] == '-')
		{
			i++;
			if (ft_isdigit(argv[j][i]) == 1)
				return (1);
		}
		while (argv[j][i])
		{
			if (ft_isdigit(argv[j][i]) != 0)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	verif_if_nb_are_neg(char **argv)
{
	int	j;

	j = 1;
	while (argv[j] != 0)
	{
		if (argv[j][0] == '-')
			return (1);
		j++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}
