/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:24:44 by brivera           #+#    #+#             */
/*   Updated: 2025/06/24 12:16:41 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>    // malloc, free, and exit
# include <unistd.h>    // usleep and write
# include <sys/time.h>  // gettimeofday
# include <pthread.h>   // pthread & mutex
# include <limits.h>	// atol
# include <unistd.h>    // write

# define LIVE 0
# define DEAD 1

# define SUCCESS 0
# define FAIL 1

# define TRUE 0
# define FALSE 1

typedef struct s_table
{
	unsigned long		start_time; // Marca de tiempo del inicio
	unsigned int		num_philos; // Número de filósofos
	int					max_meals; // Número máximo de comidas
	unsigned int		time_to_die; // Tiempo en ms antes de morir sin comer
	unsigned int		time_to_eat; // Tiempo que tarda en comer
	unsigned int		time_to_sleep; // Tiempo que tarda en dormir
	int					status; // Estado global (puede ser DEAD / LIVE)
	int					done; // 1 si todos comieron lo suficiente
	pthread_mutex_t		*forks; // Array de mutex de los tenedores
	pthread_mutex_t		*finished; // Mutex para proteger `done`
	pthread_mutex_t		*public_lock; // Mutex para imprimir o sincro
}	t_table;

typedef struct s_philo
{
	unsigned int		id; // ID del filósofo
	unsigned int		meals_eaten;// Contador de comidas realizadas
	unsigned long		last_meal_time; // Tiempo de la última comida
	pthread_mutex_t		*left_fork; // Puntero al mutex del tenedor izquierdo
	pthread_mutex_t		*right_fork; // Puntero al mutex del tenedor derecho
	pthread_mutex_t		*private_lock; // Mutex exclusivo por filósofo 
	t_table				*table; // Referencia a la mesa
}	t_philo;


int				ph_input_check(int argc, char **argv);
int				ph_init_structs(int arg, char **argv, t_table **t, t_philo **p);
void			*ph_thread_loop(void *arg);
void			ph_print_msg(t_philo *philo, char *msg, int i);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*								utils										 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void			ft_putstr(char *str);
long			ph_atol(const char *str);
int				ft_isdigit(int c);
unsigned long	ph_get_time(void);

#endif
