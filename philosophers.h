/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:15:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/03/18 15:53:24 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define YL		"\033[1;33m"
# define GN		"\033[1;32m"
# define BL		"\033[1;34m"
# define PK		"\033[1;35m"
# define GR		"\033[1;30m"
# define CY		"\033[1;36m"
# define RD		"\033[1;31m"
# define CLR	"\x1b[0m"

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
	pthread_mutex_t	death;
	pthread_mutex_t	guard_d;
	pthread_mutex_t	*forks;
} t_vars;

typedef struct s_info
{
	int			philo_id;
	long long   last_eat;
	int			eaten;
	long long   birth;
	int			ate;
	int			left_fork;
	int			right_fork;
	pthread_t		th;
	t_vars		*vars;
	pthread_mutex_t	arb;
} t_info;

// typedef struct s_phil
// {
// 	t_info      *phils;
// } t_phil;

int			init_philos(t_vars *vars);
int			init_mutex(t_vars *vars);
void		init_info(t_vars *vars, int argc, char **argv);
void    	*routine(void *philo);
long long	gettime(void);
int			ft_atoi(const char *nptr);
int			error(char *message);
void		message(t_info *phil, int m_code);
void		death(t_info *phil);
void		clean(t_vars *vars);

#endif