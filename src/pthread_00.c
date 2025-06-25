/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:24:25 by brivera           #+#    #+#             */
/*   Updated: 2025/06/25 12:24:26 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
