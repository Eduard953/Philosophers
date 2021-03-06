/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:15:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/10 19:42:02 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_vars
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				dead;
	long long		start;
	struct s_info	*phils;
	pthread_mutex_t	access;
	pthread_mutex_t	guard_d;
	pthread_mutex_t	*forks;
}	t_vars;

typedef struct s_info
{
	int			philo_id;
	long long	last_eat;
	int			eaten;
	int			left_fork;
	int			right_fork;
	pthread_t	th;
	t_vars		*vars;
}	t_info;

int			init_philos(t_vars *vars);
int			init_mutex(t_vars *vars);
void		init_info(t_vars *vars, int argc, char **argv);
void		*routine(void *philo);
long long	gettime(void);
int			ft_atoi(const char *nptr);
int			error(char *message);
void		message(t_info *phil, int m_code);
void		clean(t_vars *vars);
void		take(t_info *phil);
int			check_eat(t_info *phil);
void		drop(t_info *phil);

#endif