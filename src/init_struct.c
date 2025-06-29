/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:00:34 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 15:50:33 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_init_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->forks = ft_calloc(table->num_philos, sizeof(pthread_mutex_t));
	if (!table->forks)
		return (FAIL);
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != SUCCESS)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	ph_init_data(int argc, char **argv, t_table *table)
{
	table->num_philos = (unsigned int)ph_atol(argv[1]);
	table->time_to_die = (unsigned int)ph_atol(argv[2]);
	table->time_to_eat = (unsigned int)ph_atol(argv[3]);
	table->time_to_sleep = (unsigned int)ph_atol(argv[4]);
	if (argc == 6)
		table->max_meals = (unsigned int)ph_atol(argv[5]);
	else
		table->max_meals = NO_MAX_MEALS;
	table->done = 0;
	table->status = LIVE;
	if (ph_init_forks(table) == FAIL)
		return (FAIL);
	table->finished = ft_calloc(1, sizeof(pthread_mutex_t));
	table->public_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!table->finished || !table->public_lock)
		return (FAIL);
	if (pthread_mutex_init(table->finished, NULL) != SUCCESS)
		return (FAIL);
	if (pthread_mutex_init(table->public_lock, NULL) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

int	ph_init_philos(t_table *table, t_philo *philos)
{
	unsigned int	i;
	pthread_mutex_t	*private;

	private = ft_calloc(table->num_philos, sizeof(pthread_mutex_t));
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
		if (pthread_mutex_init(&private[i], NULL) != SUCCESS)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	ph_init_structs(int argc, char **argv, t_table **table, t_philo **philos)
{
	*table = ft_calloc(1, sizeof(t_table));
	if (!*table)
		return (FAIL);
	if (ph_init_data(argc, argv, *table) == FAIL)
		return (FAIL);
	*philos = ft_calloc((*table)->num_philos, sizeof(t_philo));
	if (!*philos)
		return (FAIL);
	if (ph_init_philos(*table, *philos) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
