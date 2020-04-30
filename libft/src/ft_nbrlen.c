/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:02:04 by mbrella           #+#    #+#             */
/*   Updated: 2020/04/29 23:10:20 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int n)
{
	if (n == 0)
		return (1);
	else if (n / 10 > 0)
		return (1 + ft_nbrlen(n / 10));
	else
		return (1);
}