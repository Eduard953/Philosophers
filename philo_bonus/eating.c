/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:10:08 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/10 19:45:01 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take(t_info *phil)
{
	sem_wait(phil->vars->forks);
	message(phil, 0);
	sem_wait(phil->vars->forks);
	message(phil, 0);
}

void	drop(t_info *phil)
{
	sem_post(phil->vars->forks);
	sem_post(phil->vars->forks);
}
