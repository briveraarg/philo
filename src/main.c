/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:27 by brivera           #+#    #+#             */
/*   Updated: 2025/06/24 14:27:28 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Libera y destruye todos los mutex creados
void	ph_destroy_mutexes(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->table->num_philos)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		pthread_mutex_destroy(&philo->table->private_locks[i]);
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
		free(philo->table->forks);
		free(philo->table->private_locks);
		free(philo->table->public_lock);
		free(philo->table->finished);
		free(philo->table);
	}
	free(philo);
}

/**
 * ph_handle_single - Maneja el caso en que solo hay un filósofo.
 *
 * En este caso, el filósofo no puede tomar ambos tenedores,
 * por lo que no puede comer.
 * Se crea un hilo para ejecutar su rutina y un monitor que detectará su muerte.
 * Luego se espera un poco más que 'time_to_die' para asegurarse de que muera.
 * Finalmente, se limpian los recursos asociados.
 *
 * @table: estructura con los parámetros globales de la simulación.
 * @philo: puntero al único filósofo creado.
 */


void	ph_handle_single(t_table *table, t_philo *philo)
{
	pthread_t	thread;
	pthread_t	monitor;

	table->start_time = ph_get_time();
	if (pthread_create(&thread, NULL, &ph_thread_loop, &philo[0]) != 0)
	{
		ph_clean(philo);
		return ;
	}
	//monitor
	//sleep
	//pthread_detach x 2
	//phclean
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
