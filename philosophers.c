/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:12:20 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/29 22:15:36 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		clean(phil->vars);
		return (1);
	}
	return (0);
}

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
	{
		printf("hey%d\n", phil->philo_id);
		return (1);
	}
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

int check_eat(t_info *phil)
{
	if (phil->eaten == phil->vars->max_eat)
		return (1);
	return (0);
}

void	death(t_info *phil)
{
	usleep((phil->vars->time_to_die - (gettime() - phil->last_eat) * 1000));
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
		if (eat(phil))
		{
			death(phil);
			break;
		}
		drop(phil);
		if (check_eat(phil))
			break;
		if (sleep_p(phil))
		{
			death(phil);
			break;
		}
	}
	return ((void *)0);
}
