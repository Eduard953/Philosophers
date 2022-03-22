/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:12:20 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/22 18:14:22 by ebeiline         ###   ########.fr       */
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
	take(phil);
	message(phil, 1);
	pthread_mutex_lock(&phil->arb);
	phil->last_eat = gettime();
	phil->eaten++;
	pthread_mutex_unlock(&phil->arb);
	usleep(phil->vars->time_to_eat * 1000);
	drop(phil);
}

void	sleep_p(t_info *phil)
{
	message(phil, 2);
	usleep(phil->vars->time_to_sleep * 1000);
}

void	think(t_info *phil)
{
	message(phil, 3);
}

void	death(t_info *phil)
{
	message(phil, 4);
	pthread_mutex_unlock(&phil->vars->death);
}

void    *routine(void *philo)
{
	t_info *phil;

	phil = (t_info *)philo;
	if (phil->philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat(phil);
		think(phil);
		sleep_p(phil);
	}
	return (NULL);
}
