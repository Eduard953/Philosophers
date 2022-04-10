/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:26:53 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/10 19:45:06 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philo)
	{
		kill(vars->phils[i].pid, SIGKILL);
		i++;
	}
	sem_close(vars->forks);
	sem_close(vars->arb);
	sem_close(vars->access);
	sem_close(vars->routine);
	sem_unlink("/forks");
	sem_unlink("/arb");
	sem_unlink("/access");
	sem_unlink("/routine");
	free(vars->phils);
}
