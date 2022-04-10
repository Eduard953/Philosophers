/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:16:33 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/10 18:36:05 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_argv(t_vars *vars, int argc)
{
	if (argc != 6 && argc != 5)
		return (error("Error: wrong amount of args\n"));
	if (argc == 6 && vars->max_eat <= 0)
		return (error("ERROR: negative amount of must eat\n"));
	if (vars->num_philo < 0)
		return (error("ERROR: negative amount of philosophers\n"));
	if (vars->time_to_die < 0)
		return (error("ERROR: negative time to die\n"));
	if (vars->time_to_eat < 0)
		return (error("ERROR: negative time to eat\n"));
	if (vars->time_to_sleep < 0)
		return (error("ERROR: negative time to sleep\n"));
	return (0);
}

int	create_processes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_philo)
	{
		vars->phils[i].pid = fork();
		if (vars->phils[i].pid < 0)
			return (error("fork error"));
		if (vars->phils[i].pid == 0)
		{
			create_thread(&vars->phils[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_info(&vars, argc, argv);
	if (check_argv(&vars, argc))
		return (1);
	init_semaphor(&vars);
	init_philos(&vars);
	sem_wait(vars.routine);
	create_processes(&vars);
	sem_wait(vars.routine);
	clean(&vars);
	return (0);
}