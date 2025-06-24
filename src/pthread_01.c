/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:25:06 by brivera           #+#    #+#             */
/*   Updated: 2025/06/24 12:32:34 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
 * ph_routine - Ejecuta una vuelta completa del ciclo de vida del filósofo.
 *
 * Este ciclo incluye:
 * 1. Tomar los tenedores para poder comer
 *    (bloqueando los mutex correspondientes).
 * 2. Registrar el tiempo de la última comida
 *    y aumentar el contador de comidas.
 *    Esto se hace bajo un mutex privado para evitar condiciones de carrera.
 * 3. Dormir el tiempo correspondiente a "comer"
 *    (simula la duración de la comida).
 * 4. Liberar los tenedores y pasar a dormir y luego pensar
 *    (ph_rest_and_think).
 *
  */

void	ph_routine(t_philo *philo)
{
	ph_pick_up_forks(philo);
	pthread_mutex_lock(philo->private_lock);
	philo->last_meal_time = ph_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->private_lock);
	ph_sleep_precise(philo->table->time_to_eat);
	ph_rest_and_think(philo);
}

/**
 * ph_thread_loop - Función que representa el ciclo de vida de cada filósofo.
 * 
 * Esta función es el punto de entrada de cada hilo (pthread)
 * que simula un filósofo.
 * - Recibe como argumento un puntero a una estructura `t_philo`,
 * que contiene la información individual del filósofo.
 * 
 * Comportamiento:
 * 1. Si el ID del filósofo es par, duerme un pequeño tiempo antes de comenzar.
 * Esto sirve para desfasar ligeramente a los filósofos
 * y evitar condiciones de carrera (ejemplo, todos intentan tomar los tenedores
 * al mismo tiempo).
 * 2. Entra en un bucle infinito que representa la rutina del filósofo.
 *    - En cada iteración:
 *      a.	Verifica si el filósofo ha muerto (`ph_is_dead`).
 * 			Si es así, sale del hilo.
 *      b. 	Verifica si el filósofo ya comió todas sus comidas requeridas 
 * 			(`ph_has_finished_meals`). Si es así, sale del hilo.
 *      c. 	Ejecuta la rutina del filósofo (`ph_routine`),
 * 			incluye pensar, tomar tenedores, comer y dormir.
 *
 * Retorna:
 * - Siempre devuelve `NULL` (cast a `(void *)0`) al terminar el hilo.
 */

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
