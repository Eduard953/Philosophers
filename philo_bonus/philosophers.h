/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:29:36 by ebeiline          #+#    #+#             */
/*   Updated: 2022/04/07 19:54:30 by ebeiline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
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
	sem_t			*routine;
	sem_t			*arb;
	sem_t			*forks;
	sem_t			*access;
}	t_vars;

typedef struct s_info
{
	int			philo_id;
	long long	last_eat;
	int			eaten;
	long long	birth;
	int			pid;
	int			ate;
	t_vars		*vars;
}	t_info;

int			init_philos(t_vars *vars);
int			init_semaphor(t_vars *vars);
void		init_info(t_vars *vars, int argc, char **argv);
long long	gettime(void);
int			ft_atoi(const char *nptr);
int			error(char *message);
void		message(t_info *phil, int m_code);
void		clean(t_vars *vars);
void		take(t_info *phil);
int			check_eat(t_info *phil);
int			create_thread(t_info *phil);
void		drop(t_info *phil);

#endif