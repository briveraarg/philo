/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:24:44 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 19:57:26 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h> 
# include <sys/time.h>
# include <pthread.h> 
# include <limits.h>	
# include <unistd.h>    
# include <stdint.h>
# include <string.h>
# include <stdio.h>

# define LIVE 0
# define DEAD 1

# define SUCCESS 0
# define FAIL 1

# define TRUE 0
# define FALSE 1

# define NO_MAX_MEALS -1

# define FORK 	"has taken a fork"
# define DIED	"died"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"

# define COLOR_TECH_GREEN	"\033[1;38;5;49m"
# define COLOR_TECH_BLUE	"\033[1;38;5;75m"
# define COLOR_TECH_VIOLET	"\033[1;38;5;135m"
# define COLOR_TECH_RED		"\033[1;38;5;196m"
# define COLOR_RESET		"\033[0m"


typedef struct s_table
{
	unsigned long		start_time;
	unsigned int		num_philos;
	int					max_meals;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					status;
	int					done;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*finished;
	pthread_mutex_t		*public_lock;
	pthread_mutex_t		*private_locks;

}	t_table;

typedef struct s_philo
{
	unsigned int		id;
	int					meals_eaten;
	unsigned long		last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*private_lock;
	t_table				*table;
}	t_philo;

int				ph_input_check(int argc, char **argv);
int				ph_init_structs(int arg, char **argv, t_table **t, t_philo **p);
int				ph_is_dead(t_philo *philo);
int				ph_has_finished_meals(t_philo *philo);
int				ph_philo_check_deat(t_philo *philo);
int				ph_all_philos_finished(t_philo *philo);
int				ph_monitor(t_philo *philos, pthread_t *monitor);
int				ph_simulate(t_table *table, t_philo *philos);
void			*ph_thread_loop(void *arg);
void			ph_clean(t_philo *philo);
void			ph_sleep_precise(unsigned long time);
void			ph_rest_and_think(t_philo *philo);
void			ph_pick_up_forks(t_philo *philo);
void			ph_routine(t_philo *philo);
void			ph_handle_single(t_table *table, t_philo *philo);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*								utils										 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

char			*ft_itoa(int n);
char			*ft_utoa(unsigned long n);
int				ft_isdigit(int c);
long			ph_atol(const char *str);
unsigned long	ph_get_time(void);
void			ft_putstr(char *str, int fd);
void			ph_print_msg(t_philo *philo, char *msg, int i);
void			*ft_calloc(size_t count, size_t size);
#endif
