/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-24 14:56:51 by brivera           #+#    #+#             */
/*   Updated: 2025-06-24 14:56:51 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Libera y destruye todos los mutex creados
void	ph_destroy_mutexes(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo->table->num_philos)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		pthread_mutex_destroy(&philo->table->private_locks[i]);
		i++;
	}
	pthread_mutex_destroy(philo->table->public_lock);
	pthread_mutex_destroy(philo->table->finished);
}

// Libera toda la memoria dinámica reservada
void	ph_clean(t_philo *philo)
{
	if (philo->table)
	{
		ph_destroy_mutexes(philo);
		if (philo->table->forks)
			free(philo->table->forks);
		if (philo->table->private_locks)
			free(philo->table->private_locks);
        if (philo->table->public_lock)
		    free(philo->table->public_lock);
		if (philo->table->finished)
            free(philo->table->finished);
        if (philo->table)
		    free(philo->table);
	}
	free(philo);
}
