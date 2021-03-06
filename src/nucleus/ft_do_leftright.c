/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_leftright.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:22:19 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	do_left(t_readline *p)
{
	int		k;

	k = 0;
	if (p->index > 0 && p->buff[p->index - 1] == '\n')
	{
		k = p->index - 2;
		tputs(tgetstr("up", NULL), 1, ft_c);
		while (k > 0 && p->buff[k] != '\n')
		{
			tputs(tgetstr("nd", NULL), 1, ft_c);
			k--;
		}
		tputs(tgetstr("nd", NULL), 1, ft_c);
		if (k == 0)
		{
			while (k < p->len_hint)
			{
				tputs(tgetstr("nd", NULL), 1, ft_c);
				k++;
			}
		}
//		p->index--;
	}
	if (p->index > 0)
	{
		p->index--;
		write(2, "\b", 1);
	}
}

void 	do_right(t_readline *p)
{
	int 	k;

	k = 0;
	if (p->buff[p->index] && p->buff[p->index] == '\n')
	{
		k = p->index - 1;
		tputs(tgetstr("do", NULL), 1, ft_c);
		while (k > 0 && p->buff[k] != '\n')
		{
			write(2, "\b", 1);
			k--;
		}
		write(2, "\b", 1);
//		p->index++;
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_c);
//	if (ft_put_n(p->len_hint, p->index + 1, p->len) == -1)
//	tputs(tgetstr("nd", NULL), 1, ft_c);
	p->index++;
}

void	ft_do_leftright(t_readline *p)
{
	if (p->sum_read == 186 && p->index > 0)
		do_left(p);
	else if (p->sum_read == 185 && p->index < p->len)
		do_right(p);
}
