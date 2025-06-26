/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:44:20 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 16:01:39 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	ph_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

char	*ft_utoa(unsigned long n)
{
	char			*str;
	int				len;
	unsigned long	tmp;

	tmp = n;
	len = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		len++;
	}
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}

void	print_forks(t_philo *philos, unsigned int num_philos)
{
	unsigned int	i;

	printf("Asignación de tenedores:\n");
	i = 0;
	while (i < num_philos)
	{
		printf("Filósofo %u:\n", philos[i].id);
		printf("  Tenedor derecho (fork %u): %p\n",
			i, (void *)philos[i].right_fork);
		printf("  Tenedor izquierdo (fork %u): %p\n",
			(i + 1) % num_philos, (void *)philos[i].left_fork);
		i++;
	}
}
