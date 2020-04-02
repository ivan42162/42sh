/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoimy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:45:26 by mbrella           #+#    #+#             */
/*   Updated: 2019/08/18 17:09:29 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

int		ft_atoi_with(char *str, int *marker)
{
	int res;
	int en;

	en = 0;
	dprintf(2, "\nstratoi: |%s|", str);
	while ((*str < 33 || *str == '-' || *str == '+' || *str > 126) &&
			en == 0)
	{
		if (*str == '+')
			en++;
		else
		{
			if (*str == '-')
				en = -1;
		}
		(str)++;
		(*marker)++;
	}
	dprintf(2, "\nnum: |%d|", *str);
	if (en == 0)
		en++;
	res = 0;
	while (*str <= '9' && *str >= '0')
	{
		res = res * 10 + (*str - '0');
		str++;
		(*marker)++;
	}
	dprintf(2, "\nnum: |%d|", res * en);
	return (res * en);
}