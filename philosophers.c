/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:12:20 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/24 16:30:26 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take(t_info *phil)
{
	pthread_mutex_lock(&phil->vars->forks[phil->left_fork]);
	message(phil, 0);
	pthread_mutex_lock(&phil->vars->forks[phil->right_fork]);
	message(phil, 0);
}

void	drop(t_info *phil)
{
	pthread_mutex_unlock(&phil->vars->forks[phil->left_fork]);
	pthread_mutex_unlock(&phil->vars->forks[phil->right_fork]);
}

void	eat(t_info *phil)
{
	message(phil, 1);
	usleep(phil->vars->time_to_eat * 1000);
	phil->last_eat = gettime();
	phil->eaten++;
}

void	sleep_p(t_info *phil)
{
	message(phil, 2);
	usleep(phil->vars->time_to_sleep * 1000);
}

int check_eat(t_info *phil)
{
	if (phil->eaten == phil->vars->max_eat)
		return (1);
	return (0);
}

int check_routine(t_info *phil)
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
		return (1);
	}
	return (0);
}

void    *routine(void *philo)
{
	t_info 	*phil;
	
	phil = (t_info *)philo;
	phil->last_eat = gettime();
	if (phil->philo_id % 2 == 0)
		usleep(500);
	while (!check_routine(phil))
	{
		message(phil, 3);
		take(phil);
		eat(phil);
		drop(phil);
		if (check_eat(phil))
			break;
		sleep_p(phil);
	}
	return ((void *)0);
}
