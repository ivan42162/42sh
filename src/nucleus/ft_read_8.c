/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:15:41 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void			ft_cheak_sum(t_readline *p, t_memory **h)
{
	p->sum_read == 186 || p->sum_read == 185 ? ft_do_leftright(p) : NULL;
	p->sum_read == 183 || p->sum_read == 184 ? ft_putmemory(h, p) : NULL;
	p->sum_read == 341 ? ft_upcursor(p) : NULL;
	p->sum_read == 342 ? ft_downcursor(p) : NULL;
	p->sum_read == 297 || p->sum_read == 298 || p->sum_read == 190 ||
							p->sum_read == 188 ? ft_arrows(p) : NULL;
}

void			ft_add_his(t_readline *p, t_memory *h)
{
	find_history(p, h);
	ft_cleanstr(p->index, p);
	p->len_hint = ft_printf_helper(p->mod);
	ft_putstr_fd(p->buff, 2);
}

static void		norme_help(t_readline *p, char buf[8])
{
	if (p->sum_read == 27 || (p->sum_read == 119 && p->esc == 1))
		ft_do_copy(p);
	else if (ft_signal(p->sum_read, p) == 404)
		ft_do_addch(p, buf[0]);
	do_job_del();
}

void			ft_read_8(t_readline *p, t_memory *head, int mod)
{
	char		buf[8];
	int			rt;
	t_memory	*h;

	p->mod = mod;
	h = head;
	do_job_del();
	while (do_job_del() && (rt = read(0, buf, 8)) && buf[0] != '\n')
	{
		do_job_del();
		p->sum_read = ft_add_sumchar(buf, rt);
		if (rt > 1)
			ft_cheak_sum(p, &h);
		else if (p->sum_read == 9)
			ft_cheak_tab(p);
		else if (p->sum_read == 18)
			ft_add_his(p, h);
		else if (p->sum_read == 25 || p->sum_read == 23 || p->sum_read == 21 ||
				p->sum_read == 127)
			ft_cut_copy(p);
		else if (ft_signal(p->sum_read, p) == 1)
			return ;
		else
			norme_help(p, buf);
	}
	if (globals()->g_memory_head->inp && mod != 0)
	{
		if (globals()->g_memory_head->inp[0] != '\0')
			ft_strcat(globals()->g_memory_head->inp, "\n");
		ft_strcat(globals()->g_memory_head->inp, p->buff);
	}
	p->index = do_zamena_slash(p->buff, p);
}
