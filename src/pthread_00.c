/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:24:25 by brivera           #+#    #+#             */
/*   Updated: 2025/06/24 12:27:01 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
 * ph_pick_up_forks - Simula que el filósofo toma ambos tenedores para comer.
 *
 * El filósofo primero toma (bloquea) el tenedor de su derecha
 * y luego el de su izquierda,
 * imprimiendo un mensaje después de cada acción. Al tomar ambos,
 * imprime que está comiendo.
 *
 * @philo: puntero a la estructura del filósofo que está tomando los tenedores.
 */

void	ph_pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ph_print_msg(philo, "🤚 has taken a fork", 1);
	pthread_mutex_lock(philo->left_fork);
	ph_print_msg(philo, "🤚 has taken a fork", 1);
	ph_print_msg(philo, "🍪 is eating", 0);
}

void	ph_rest_and_think(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ph_print_msg(philo, "😴 is sleeping", 3);
	ph_sleep_precise(philo->table->time_to_sleep);
	ph_print_msg(philo, "🤔 is thinking", 4);
}

int	ph_has_finished_meals(t_philo *philo)
{
	int	finished;

	finished = FALSE;
	pthread_mutex_lock(philo->table->finished);
	if (philo->meals_eaten == philo->table->max_meals
		&& philo->table->max_meals != NO_MAX_MEALS)
	{
		philo->table->done++;
		finished = TRUE;
	}
	pthread_mutex_unlock(philo->table->finished);
	return (finished);
}

void	ph_sleep_precise(unsigned long time)
{
	unsigned long	start;
	unsigned long	end;
	unsigned long	current;

	start = ph_get_time();
	end = start + time;
	while (1)
	{
		current = ph_get_time();
		if (current >= end)
			break ;
		else
			usleep(500);
	}
}

int	ph_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->table->public_lock);
	if (philo->table->status == DEAD)
	{
		pthread_mutex_unlock(philo->table->public_lock);
		return (TRUE);
	}
	else
		pthread_mutex_unlock(philo->table->public_lock);
	return (FALSE);
}
