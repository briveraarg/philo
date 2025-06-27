/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:11:19 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 15:37:30 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str, int fd)
{
	int	len;

	len = ft_strlen(str);
	write(fd, str, len);
}

static void	ft_putstr_pad(char *str, int width)
{
	int	len;

	len = ft_strlen(str);
	ft_putstr(str, 1);
	while (len < width)
	{
		write(1, " ", 1);
		len++;
	}
}

static char	*ph_get_color(int i)
{
	if (i == 1)
		return (COLOR_TECH_BLUE);
	if (i == 2)
		return (COLOR_TECH_RED);
	if (i == 3)
		return (COLOR_TECH_GREEN);
	if (i == 4)
		return (COLOR_TECH_VIOLET);
	return (COLOR_RESET);
}

void	ph_print_msg(t_philo *philo, char *msg, int i)
{
	unsigned long	time;
	char			*time_str;
	char			*id_str;

	time = ph_get_time() - philo->table->start_time;
	pthread_mutex_lock(philo->table->public_lock);
	if (philo->table->status == 0)
	{
		time_str = ft_utoa(time);
		id_str = ft_itoa(philo->id);
		ft_putstr(ph_get_color(i), 1);
		ft_putstr_pad(time_str, 8);
		ft_putstr_pad(id_str, 4);
		ft_putstr(msg, 1);
		ft_putstr(COLOR_RESET, 1);
		ft_putstr("\n", 1);
		free(time_str);
		free(id_str);
	}
	pthread_mutex_unlock(philo->table->public_lock);
}
