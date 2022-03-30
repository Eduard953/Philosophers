/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:57:40 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/30 13:59:11 by ebeiline         ###   ########.fr       */
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

int	check_eat(t_info *phil)
{
	if (phil->eaten == phil->vars->max_eat)
		return (1);
	return (0);
}
