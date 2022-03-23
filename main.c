/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:37:13 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/23 14:41:35 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_argv(t_vars *vars, int argc)
{
	if (argc != 6 && argc != 5)
		return(error("Error: wrong amount of args\n"));
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

void *arbitrator(void *vars_void)
{
	t_vars	*vars;
	int		i;
	int		count;

	i = 0;
	count = 0;
	vars = (t_vars *)vars_void;
	usleep(500);
	while (1)
	{
		i %= vars->num_philo;
		if (count == vars->num_philo)
			exit(1);
		pthread_mutex_lock(&vars->phils[i].arb);
		if (!vars->phils[i].ate && (vars->phils[i].eaten == vars->max_eat))
		{
			vars->phils[i].ate = 1;
			count++;
		}
		if ((gettime() - vars->phils[i].last_eat) > vars->time_to_die)
		{
			death(&vars->phils[i]);
			return ((void *)0);
		}
		pthread_mutex_unlock(&vars->phils[i].arb);
		usleep(500);
		i++;
	}
	pthread_mutex_unlock(&vars->death);
	return ((void *)0);
}

static
int create_threads(t_vars *vars)
{
	int				i;
	void 			*rout_v;
	pthread_t		arb;


	vars->start = gettime();
	if (pthread_create(&arb, NULL, arbitrator, vars))
		return (1);
	pthread_detach(arb);
	i = 0;
    while (i < (vars->num_philo))
	{
		pthread_mutex_lock(&vars->phils[i].arb);
		vars->phils[i].last_eat = gettime();
		pthread_mutex_unlock(&vars->phils[i].arb);
		rout_v = (void *)&(vars->phils[i]);
		if (pthread_create(&(vars->phils[i].th), NULL, &routine, rout_v))
			return (1);
		i++;
		usleep(100);
	}
	usleep(1000);
	i = 0;
    while (i < (vars->num_philo))
	{
		if (pthread_join(vars->phils[i].th, NULL))
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
    t_vars  vars;
    
	init_info(&vars, argc, argv);
	if (check_argv(&vars, argc))
		return (1);
	init_mutex(&vars);
	init_philos(&vars);
    create_threads(&vars);
	pthread_mutex_lock(&vars.death);
	pthread_mutex_unlock(&vars.death);
	clean(&vars);
    return (0);
}
