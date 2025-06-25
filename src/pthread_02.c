/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:46:11 by brivera           #+#    #+#             */
/*   Updated: 2025/06/25 12:10:20 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ph_watch_philos(void *arg)
{
	unsigned int	i;
	t_philo			*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos->table->num_philos)
		{
			if (ph_philo_check_deat(&philos[i]) == TRUE) 
				return ((void *)0);
			i++;
			if (ph_all_philos_finished(&philos[i]) == TRUE)
				return ((void *) 0);
		}
	}
	return ((void *)0);
}

int	ph_monitor(t_philo *philos, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, &ph_watch_philos, &philos) != SUCCESS)
		return (ph_clean(philos), FAIL);
	return (SUCCESS);
}

int	ph_run_threads(pthread_t *threads, t_table *table, t_philo *philos)
{
	unsigned int	i;
	pthread_t		monitor;

	i = 0;
	table->start_time = ph_get_time();
	while (i < table->num_philos)
	{
		if (pthread_create(&threads[i], NULL, &ph_thread_loop, &philos[i]) != SUCCESS)
			return (FAIL);
		i++;
	}
	if (ph_monitor(philos, &monitor) != SUCCESS)
		return (FAIL);
	while (--i >= 0)
	{
		if (pthread_join(threads[i], NULL) != SUCCESS)
			return (FAIL);
	}
	pthread_join(monitor, NULL);
	return (SUCCESS);
}

int	ph_simulate(t_table *table, t_philo *philos)
{
	pthread_t	*threads;

	threads = malloc((table->num_philos + 1) * sizeof(pthread_t));
	if (!threads)
		return (FAIL);
	if (ph_run_threads(threads, table, philos) == FAIL)
		return (FAIL);
	free(threads);
	return (SUCCESS);
}
