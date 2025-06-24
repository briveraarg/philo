/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:44:20 by brivera           #+#    #+#             */
/*   Updated: 2025/06/24 12:16:12 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	ph_get_time(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

static size_t	ft_count_digits(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	size_t			i;

	str = (char *)malloc(ft_count_digits(n) + 1);
	if (!str)
		return (NULL);
	str[ft_count_digits(n)] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = (unsigned int)(-n);
	}
	else
		num = (unsigned int)n;
	i = ft_count_digits(n) - 1;
	while (num > 0)
	{
		str[i] = (char)((num % 10) + '0');
		num /= 10;
		i--;
	}
	if (n == 0)
		str[0] = '0';
	return (str);
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
		tmp = tmp / 10;
		len++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void	ph_print_msg(t_philo *philo, char *msg, int i)
{
	unsigned long	time;
	char			*time_str;
	char			*id_str;

	time = get_time() - philo->table->start_time;
	pthread_mutex_lock(philo->table->public_lock);
	if (philo->table->status == 0)
	{
		time_str = ft_utoa(time);
		id_str = ft_itoa(philo->id);
		ft_putstr(time_str);
		ft_putstr(" ");
		ft_putstr(id_str);
		ft_putstr(" ");
		ft_putstr(msg);
		ft_putstr("\n");
		free(time_str);
		free(id_str);
	}
	pthread_mutex_unlock(philo->table->public_lock);
}

