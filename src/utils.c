/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:19:42 by brivera           #+#    #+#             */
/*   Updated: 2025/06/26 15:14:05 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

	str = ft_calloc(ft_count_digits(n) + 1, sizeof(char));
	if (!str)
		return (NULL);
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

long	ph_atol(const char *str)
{
	long	num;
	int		sig;
	int		i;

	num = 0;
	sig = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sig);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total_bytes;

	if (size != 0 && count >= SIZE_MAX / size)
		return (NULL);
	total_bytes = count * size;
	ptr = malloc(total_bytes);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, total_bytes);
	return (ptr);
}
