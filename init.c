/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:35:13 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/18 15:24:33 by ebeiline         ###   ########.fr       */
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
		vars->phils[i].birth = 0;
		vars->phils[i].last_eat = gettime();
		vars->phils[i].eaten = 0;
		vars->phils[i].ate = 0;
		vars->phils[i].right_fork = i;
		vars->phils[i].left_fork = (i + 1) % vars->num_philo;
		vars->phils[i].vars = vars;
		pthread_mutex_init(&vars->phils[i].arb, NULL);
	}
	return (0);
}

void    init_info(t_vars *vars, int argc, char **argv)
{
    vars->num_philo = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->max_eat = -1;
	vars->dead = 0;
    if (argc == 6)
        vars->max_eat = ft_atoi(argv[5]);
}

int	init_mutex(t_vars *vars)
{
	int	i;

	i = 0;
	pthread_mutex_init(&vars->death, NULL);
	pthread_mutex_lock(&vars->death);
	pthread_mutex_init(&vars->access, NULL);
	vars->forks = (pthread_mutex_t *)malloc(sizeof(*vars->forks) * vars->num_philo);
	if (!vars->forks)
		return (error("malloc failed"));
	while (i < vars->num_philo)
		pthread_mutex_init(&vars->forks[i++], NULL);
	return (0);
}