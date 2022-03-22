/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:51:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/22 18:07:43 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean(t_vars *vars)
{
	int	i;

	pthread_mutex_unlock(&vars->death);
	if (vars->forks)
	{
		i = -1;
		while (++i < vars->num_philo)
			pthread_mutex_destroy(&vars->forks[i]);
		free(vars->forks);
	}
	if (vars->phils)
	{
		i = -1;
		while (++i < vars->num_philo)
			pthread_mutex_destroy(&vars->phils[i].arb);
		free(vars->phils);
	}
	pthread_mutex_destroy(&vars->access);
	pthread_mutex_destroy(&vars->guard_d);
	pthread_mutex_destroy(&vars->death);
	exit(0);
}
