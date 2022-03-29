/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:51:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/29 22:08:46 by ebeiline         ###   ########.fr       */
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
		{
			pthread_mutex_unlock(&vars->forks[i]);
			pthread_mutex_destroy(&vars->forks[i]);
		}
		free(vars->forks);
	}
	pthread_mutex_unlock(&vars->access);
	pthread_mutex_destroy(&vars->access);
}
