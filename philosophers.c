/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:12:20 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/30 14:45:52 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_routine(t_info *phil)
{
	if (phil->vars->num_philo == 1)
	{
		message(phil, 3);
		message(phil, 0);
		while (gettime() - phil->last_eat <= phil->vars->time_to_die)
			usleep(5);
	}
	if (phil->eaten == phil->vars->max_eat)
		return (1);
	if ((gettime() - phil->last_eat) > phil->vars->time_to_die)
	{
		message(phil, 4);
		// clean(phil->vars);
		// exit(0);
	}
	pthread_mutex_lock(&phil->vars->guard_d);
	if (phil->vars->dead)
	{
		pthread_mutex_unlock(&phil->vars->guard_d);
		return (1);
	}
	pthread_mutex_unlock(&phil->vars->guard_d);
	return (0);
}

int	check_death(t_info *phil, int time)
{
	long	start;

	start = gettime();
	usleep(5);
	while ((gettime() - start) < time)
	{
		if (check_routine(phil))
			return (1);
	}
	return (0);
}

int	eat(t_info *phil)
{
	message(phil, 1);
	if (check_death(phil, phil->vars->time_to_eat))
		return (1);
	phil->last_eat = gettime();
	phil->eaten++;
	return (0);
}

int	sleep_p(t_info *phil)
{
	message(phil, 2);
	if (check_death(phil, phil->vars->time_to_sleep))
		return (1);
	return (0);
}

void	*routine(void *philo)
{
	t_info	*phil;

	phil = (t_info *)philo;
	phil->last_eat = gettime();
	if (phil->philo_id % 2 == 0)
		usleep(500);
	while (!check_routine(phil))
	{
		message(phil, 3);
		take(phil);
		if (eat(phil))
		{
			drop(phil);
			break ;
		}
		drop(phil);
		if (check_eat(phil))
			break ;
		if (sleep_p(phil))
			break ;
	}
	return ((void *)0);
}
