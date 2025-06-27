/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:23:48 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 18:39:55 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
 * ph_pick_up_forks - Simula que el filósofo toma ambos tenedores para comer.
 *
 * El filósofo primero toma (bloquea) sus tenedores pero dependiendio 
 * el oden si son pares o impares.
 * Pares => derecha / izquierda.
 * Impares => izquierda / derecha.
 * imprimiendo un mensaje después de cada acción. Al tomar ambos,
 * imprime que está comiendo.
 *
 * @philo: puntero a la estructura del filósofo que está tomando los tenedores.
 */

void	ph_pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		ph_print_msg(philo, FORK, 1);
		pthread_mutex_lock(philo->left_fork);
		ph_print_msg(philo, FORK, 1);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ph_print_msg(philo, FORK, 1);
		pthread_mutex_lock(philo->right_fork);
		ph_print_msg(philo, FORK, 1);
	}
	ph_print_msg(philo, EAT, 0);
}

/*
 * El filósofo suelta los tenedores después de comer,
 * imprime que va a dormir, duerme un tiempo determinado,
 * y luego imprime que está pensando.
 * Esta función representa el paso posterior al acto de comer,
 * ayudando a sincronizar el acceso a los tenedores (forks) mediante mutexes.
 */

void	ph_rest_and_think(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ph_print_msg(philo, SLEEP, 3);
	ph_sleep_precise(philo->table->time_to_sleep);
	ph_print_msg(philo, THINK, 4);
}

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
