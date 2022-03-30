/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:37:13 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/30 13:42:36 by ebeiline         ###   ########.fr       */
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

static
int	create_threads(t_vars *vars)
{
	int		i;
	void	*rout_v;

	vars->start = gettime();
	i = 0;
	while (i < (vars->num_philo))
	{
		rout_v = (void *)&(vars->phils[i]);
		if (pthread_create(&(vars->phils[i].th), NULL, &routine, rout_v))
			return (1);
		i++;
	}
	i = 0;
	usleep(500);
	while (i < (vars->num_philo))
	{
		pthread_join(vars->phils[i].th, NULL);
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
	init_mutex(&vars);
	init_philos(&vars);
	create_threads(&vars);
	clean(&vars);
	return (0);
}
