/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:23:27 by brivera           #+#    #+#             */
/*   Updated: 2025/06/25 11:42:34 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table		*table;
	t_philo		*philos;

	if (ph_input_check(argc, argv) == FALSE)
		return (ft_putstr("❌ invalid input\n"), FAIL);
	if (ph_init_structs(argc, argv, &table, &philos) == FAIL)
		return (ph_clean(philos), FAIL);
	if (table->num_philos == 1)
		return (ph_handle_single(table, philos), SUCCESS);
	if (ph_simulate(table, philos) == FAIL)
		return (ph_clean(philos), FAIL);
	ph_clean(philos);
	return (SUCCESS);
}
