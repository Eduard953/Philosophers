/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:36:28 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/22 18:08:08 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	gettime(void)
{
	long long		time;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
		return (-1);
	time = (current_time.tv_sec * 1000LL) + current_time.tv_usec / 1000;
	return (time);
}
