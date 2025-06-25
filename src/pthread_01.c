/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:25:06 by brivera           #+#    #+#             */
/*   Updated: 2025/06/25 12:25:27 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
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

int	ph_philo_check_deat(t_philo *philo)
{
	unsigned long	meal;

	pthread_mutex_lock(philo->private_lock);
	meal = philo->last_meal_time;
	if ((ph_get_time() - meal) >= (unsigned long)philo->table->time_to_die
		&& philo->meals_eaten != philo->table->max_meals)
	{
		pthread_mutex_unlock(philo->private_lock);
		ph_print_msg(philo, "👻 has died", 2);
		pthread_mutex_lock(philo->table->public_lock);
		philo->table->status = DEAD;
		pthread_mutex_unlock(philo->table->public_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(philo->private_lock);
	return (FALSE);
}

int	ph_all_philos_finished(t_philo *philo)
{
	int	goal;
	int	finished;

	pthread_mutex_lock(philo->table->finished);
	finished = philo->table->done;
	goal = philo->table->num_philos;
	pthread_mutex_unlock(philo->table->finished);
	if (finished >= goal)
		return (TRUE);
	return (FALSE);
}

/*
 * Maneja el caso especial en el que solo hay un filósofo en la mesa.
 *
 * En el problema de los filósofos, si solo hay un filósofo, este solo puede
 * tomar un tenedor y nunca podrá comer, por lo que inevitablemente muere.
 * 
 * Esta función:
 * - Registra el tiempo de inicio.
 * - Imprime un mensaje indicando que el filósofo ha tomado un tenedor.
 * - Duerme durante el tiempo que tarda en morir por inanición.
 * - Imprime un mensaje indicando que el filósofo ha muerto.
 * - Limpia la memoria asociada a los filósofos.
 *
 * @param table Puntero a la estructura principal de la mesa.
 * @param philo Puntero al único filósofo presente.
 */


void	ph_handle_single(t_table *table, t_philo *philo)
{
	table->start_time = ph_get_time();
	ph_print_msg(&philo[0], FORK, 1);
	ph_sleep_precise(table->time_to_die);
	ph_print_msg(&philo[0], DIED, 2);
	ph_clean(philo);
}
