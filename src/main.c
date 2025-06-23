/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:27 by brivera           #+#    #+#             */
/*   Updated: 2025/06/23 20:38:52 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_has_finished_meals(t_philo *philo)
{
	int	finished;

	finished = FALSE;
	pthread_mutex_lock(philo->table->finished);
	if (philo->meals_eaten == philo->table->max_meals
		&& philo->table->max_meals != -1)
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

	start = get_time();
	end = start + time;
	while (1)
	{
		current = get_time();
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

void	ph_routine(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(philo->private_lock);
	philo->last_meal_time = ph_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->private_lock);
	ph_sleep_precise(philo->table->time_to_eat);
	drop_forks(philo);
}

void	*ph_thread_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ph_sleep_precise(philo->table->time_to_eat / 10);
	while (1)
	{
		if (ph_is_dead(philo) == TRUE)
			return ((void *) 0);
		if (ph_has_finished_meals(philo) == TRUE)
			return ((void *) 0);
		ph_routine(philo);
	}
	return ((void *) 0);
}

void	ph_handle_single(t_table *table, t_philo *philo)
{
	pthread_t	thread;
	pthread_t	monitor;

	table->start_time = ph_get_time();
	if (pthread_create(&thread, NULL, &ph_thread_loop, &philo[0]) != 0)
		return ;
}

int	main(int argc, char **argv)
{
	t_table		*table;
	t_philo		*philos;

	if (ph_input_check(argc, argv) == FALSE)
		return (ft_putstr("❌ invalid input\n"), FAIL);
	if (ph_init_structs(argc, argv, &table, &philos) == FAIL)
		return (FAIL);
	if (table->num_philos == 1)
		return (ph_one_philo(table, philos), SUCCESS);
	return (SUCCESS);
}
