/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:00:34 by brivera           #+#    #+#             */
/*   Updated: 2025/06/24 14:14:55 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Inicializa los mutex de los tenedores
int	ph_init_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->forks = malloc(table->num_philos * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (FAIL);
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

// Inicializa la estructura t_table con los valores pasados por argumento
int	ph_init_data(int argc, char **argv, t_table *table)
{
	table->num_philos = (unsigned int)ph_atol(argv[1]);
	table->time_to_die = (unsigned int)ph_atol(argv[2]);
	table->time_to_eat = (unsigned int)ph_atol(argv[3]);
	table->time_to_sleep = (unsigned int)ph_atol(argv[4]);
	if (argc == 6)
		table->max_meals = (unsigned int)ph_atol(argv[5]);
	else
		table->max_meals = -1;
	table->done = 0;
	table->status = LIVE;
	if (ph_init_forks(table) == FAIL)
		return (FAIL);
	table->finished = malloc(sizeof(pthread_mutex_t));
	table->public_lock = malloc(sizeof(pthread_mutex_t));
	if (!table->finished || !table->public_lock)
		return (FAIL);
	if (pthread_mutex_init(table->finished, NULL) != 0)
		return (FAIL);
	if (pthread_mutex_init(table->public_lock, NULL) != 0)
		return (FAIL);
	return (SUCCESS);
}


// Inicializa los filósofos, sus locks privados y referencias a tenedores
int	ph_init_philos(t_table *table, t_philo *philos)
{
	unsigned int	i;
	pthread_mutex_t	*private;

	private = malloc(table->num_philos * sizeof(pthread_mutex_t));
	if (!private)
		return (FAIL);
	table->private_locks = private;
	i = 0;
	while (i < table->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].last_meal_time = ph_get_time();
		philos[i].meals_eaten = 0;
		philos[i].right_fork = &table->forks[i];
		philos[i].left_fork = &table->forks[(i + 1) % table->num_philos];
		philos[i].private_lock = &private[i];
		philos[i].table = table;
		if (pthread_mutex_init(&private[i], NULL) != 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

// Reserva memoria e inicializa estructuras principales
int	ph_init_structs(int argc, char **argv, t_table **table, t_philo **philos)
{
	*table = malloc(sizeof(t_table));
	if (!*table)
		return (FAIL);
	if (ph_init_data(argc, argv, *table) == FAIL)
		return (FAIL);
	*philos = malloc(sizeof(t_philo) * (*table)->num_philos);
	if (!*philos)
		return (FAIL);
	if (ph_init_philos(*table, *philos) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

