/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:03:49 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 15:48:59 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_check_size(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ph_atol(argv[i]) <= 0 || ph_atol(argv[i]) >= INT_MAX)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ph_check_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) != TRUE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	ph_input_check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (FALSE);
	if (ph_atol(argv[1]) > 200 || ph_atol(argv[1]) < 1)
		return (FALSE);
	if (ph_check_size(argc, argv) == FALSE)
		return (FALSE);
	if (ph_check_digit(argc, argv) == FALSE)
		return (FALSE);
	return (SUCCESS);
}
