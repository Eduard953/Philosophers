/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:49:45 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/07 19:43:57 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_sign(char c)
{
	if (c == '+')
		return (1);
	else
		return (-1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = 0;
	j = 1;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		j = ft_sign(nptr[i]);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + (nptr[i] - '0');
		i++;
	}
	return (nb * j);
}

int	error(char *message)
{
	printf("%s", message);
	return (1);
}

char	*choose_str(int m_code)
{
	if (m_code == 0)
		return ("has taken a fork");
	if (m_code == 1)
		return ("is eating");
	if (m_code == 2)
		return ("is sleeping");
	if (m_code == 3)
		return ("is thinking");
	if (m_code == 4)
		return ("died");
	return (NULL);
}

void	message(t_info *phil, int m_code)
{
	sem_wait(phil->vars->access);
	printf("%llums Philosopher %d %s\n", gettime() - phil->vars->start,
		phil->philo_id + 1, choose_str(m_code));
	if (m_code == 4)
		return ;
	sem_post(phil->vars->access);
}
