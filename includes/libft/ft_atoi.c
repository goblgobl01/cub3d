/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:59:37 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/20 21:36:10 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_overflow_atoi(void)
{
	stder("atoi overflow ", 2);
	return ;
}

long long	ft_atoi(char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = sign * -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (9223372036854775807 - (*str - '0')) / 10)
		{
			handle_overflow_atoi();
			return (-922337203685477580);
		}
		result = result * 10 + *str++ - '0';
	}
	return (result * sign);
}
