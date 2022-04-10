/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:11:18 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/10 19:06:01 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_routine(void *route_v)
{
	t_info	*phil;
	
	phil = (t_info *)route_v;
	if (!phil->last_eat)
		phil->last_eat = gettime();
	while (1)
	{
		sem_wait(phil->vars->arb);
		if (phil->eaten == phil->vars->max_eat)
		{
			sem_post(phil->vars->routine);
			break ;
		}
		sem_post(phil->vars->arb);
		sem_wait(phil->vars->arb);
		if ((gettime() - phil->last_eat) > phil->vars->time_to_die)
		{
			message(phil, 4);
			sem_post(phil->vars->routine);
			break ;
		}
		sem_post(phil->vars->arb);
	}
	return (NULL);
}

int	eat(t_info *phil)
{
	message(phil, 1);
	usleep(phil->vars->time_to_eat * 1000);
	sem_wait(phil->vars->arb);
	phil->last_eat = gettime();
	phil->eaten++;
	sem_post(phil->vars->arb);
	return (0);
}

int	sleep_p(t_info *phil)
{
	message(phil, 2);
	usleep(phil->vars->time_to_sleep * 1000);
	return (0);
}

int	create_thread(t_info *phil)
{
	pthread_t	arb;

	if (!phil->vars->start)
		phil->vars->start = gettime();
	if (pthread_create(&arb, NULL, &check_routine, phil))
		return (error("thread creation failed"));
	while (1)
	{
		message(phil, 3);
		take(phil);
		eat(phil);
		drop(phil);
		sleep_p(phil);
	}
	if (pthread_join(arb, NULL))
		return (error("thread join failed"));
	return (0);
}