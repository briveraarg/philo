/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:46:11 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 19:17:42 by brivera          ###   ########.fr       */
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
			if (ph_all_philos_finished(&philos[i]) == TRUE)
				return ((void *) 0);
			i++;
		}
	}
	return ((void *)0);
}

int	ph_run_threads(pthread_t *threads, t_table *table, t_philo *philos)
{
	unsigned int	i;

	i = 0;
	table->start_time = ph_get_time();
	while (i < table->num_philos)
	{
		if (pthread_create(&threads[i], NULL,
				&ph_thread_loop, &philos[i]) != SUCCESS)
			return (FAIL);
		i++;
	}
	if (pthread_create(&threads[table->num_philos],
			NULL, &ph_watch_philos, philos) != SUCCESS)
		return (FAIL);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(threads[i], NULL) != SUCCESS)
			return (FAIL);
		i++;
	}
	pthread_join(threads[table->num_philos], NULL);
	return (SUCCESS);
}

int	ph_simulate(t_table *table, t_philo *philos)
{
	pthread_t	*threads;

	threads = ft_calloc((table->num_philos + 1), sizeof(pthread_t));
	if (!threads)
		return (FAIL);
	if (ph_run_threads(threads, table, philos) == FAIL)
		return (free(threads), FAIL);
	free(threads);
	return (SUCCESS);
}
