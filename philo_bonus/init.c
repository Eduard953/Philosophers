/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:22:28 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/10 19:42:09 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_vars *vars)
{
	int	i;

	i = -1;
	vars->phils = malloc(sizeof(struct s_info) * vars->num_philo);
	if (!vars->phils)
		return (error("malloc failed"));
	while (++i < vars->num_philo)
	{
		vars->phils[i].philo_id = i;
		vars->phils[i].last_eat = 0;
		vars->phils[i].eaten = 0;
		vars->phils[i].vars = vars;
	}
	return (0);
}

void	init_info(t_vars *vars, int argc, char **argv)
{
	vars->num_philo = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->max_eat = -1;
	vars->dead = 0;
	if (argc == 6)
		vars->max_eat = ft_atoi(argv[5]);
	vars->start = 0;
}

int	init_semaphor(t_vars *vars)
{
	sem_unlink("arb");
	sem_unlink("access");
	sem_unlink("routine");
	sem_unlink("forks");
	vars->arb = sem_open("arb", O_CREAT, 0600, 1);
	vars->access = sem_open("access", O_CREAT, 0600, 1);
	vars->routine = sem_open("routine", O_CREAT, 0600, 1);
	vars->forks = sem_open("forks", O_CREAT, 0600, vars->num_philo);
	return (0);
}
