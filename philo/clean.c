/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:51:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/30 15:44:02 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean(t_vars *vars)
{
	int	i;

	if (vars->forks)
	{
		i = -1;
		while (++i < vars->num_philo)
			pthread_mutex_destroy(&vars->forks[i]);
		free(vars->forks);
		free(vars->phils);
	}
	pthread_mutex_destroy(&vars->access);
	pthread_mutex_destroy(&vars->guard_d);
}
