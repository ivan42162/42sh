/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 18:29:17 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fshell.h"

int		ft_ck_addline(t_readline *p)
{
	int				f;

	f = 4242;
	while (f != 1)
	{
		p->buff[0] != '\0' ? globals()->g_memory_head = ft_memory(globals()->g_memory_head,
			&(p->buff)) : globals()->g_memory_head;
		p->index = ft_do_zam_alias(p->buff, p);
		while (ft_cheak_quote(p->buff) != 1)
			ft_add_intput_que(p, globals()->g_memory_head, 1);
		if ((f = ck_br(p->buff)) == 0)
			ft_add_intput_que(p, globals()->g_memory_head, 20);
		else if (f == -1 || f == -2)
		{
			ft_putstr_fd("Error \"()\"\n", globals()->all_opened_fds[2]);
			free(p->buff);
			return (0);
		}
	}
	return (1);
}

char	*ck_br_faf(char *s)
{
	int		i;
	char	c;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i];
			s[i] = 'F';
			while (s[++i] != c)
				s[i] = 'a';
			s[i] = 'F';
		}
	}
	return (s);
}

char	*ck_br_cycle(char *s, int k, int i)
{
	while (1)
	{
		i = -1;
		while (s[++i])
			if (s[i] == '(')
				k = i;
		if (s[k] && s[k] == '(')
		{
			i = k;
			while (s[++i] && s[i] != ')')
				;
		}
		else
			break ;
		if (s[i] && s[i] == ')')
		{
			s[k] = 'A';
			s[i] = 'A';
		}
		else if (strdelr(&s))
			return (NULL);
	}
	return (s);
}

int		ck_br(const char *str)
{
	char	*s;
	int		i;
	int		k;

	k = 0;
	s = ft_strdup(str);
	s = ck_br_faf(s);
	if ((i = check_bracket(s)) && i != 1 && strdelr(&s))
		return (i);
	if ((s = ck_br_cycle(s, k, i)) == NULL)
		return (0);
	i = -1;
	while (s[++i])
		if (s[i] == ')')
		{
			ft_strdel(&s);
			return (-2);
		}
	ft_strdel(&s);
	return (1);
}