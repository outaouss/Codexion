/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outaouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 06:21:36 by outaouss          #+#    #+#             */
/*   Updated: 2026/08/04 06:21:39 by outaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_number_condition(char *str, int i)
{
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			i++;
			if (str[i] != '0')
				return (-1);
		}
		else
		{
			i++;
			if (str[i] < '0' || str[i] > '9')
				return (-1);
		}
	}
	return (i);
}

int	check_number(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	result = check_number_condition(str, i);
	if (result == -1)
		return (1);
	i = result;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	ft_atoi_condition(char *str, int i)
{
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			i++;
			while (str[i] == '0')
				i++;
		}
		else
			i++;
	}
	return (i);
}

long	ft_atoi(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	i = ft_atoi_condition(str, i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	while (str[i] == ' ')
		i++;
	return (result);
}
