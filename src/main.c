/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:27 by brivera           #+#    #+#             */
/*   Updated: 2025/06/24 11:23:29 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		return (ph_handle_single(table, philos), SUCCESS);
	return (SUCCESS);
}
