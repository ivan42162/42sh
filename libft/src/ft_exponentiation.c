/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exponentiation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:39:09 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_exponentiation(int nb, int k)
{
	int numb;
	int count;

	numb = nb;
	count = 1;
	if (numb > 46340)
		return (0);
	while (++count <= k)
		numb *= nb;
	return (numb);
}
