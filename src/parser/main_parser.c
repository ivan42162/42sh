/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:19:45 by mbrella           #+#    #+#             */
/*   Updated: 2019/12/11 19:19:46 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

t_exectoken		*do_parser_dop(t_dop_str *t, t_lextoken *tmp)
{
	if (tmp == NULL)
		return (NULL);
	if (tmp->operator_type == -2)
		t->prev_c = ft_cr_new_exectoken(tmp, NULL, -2, t);
	else
	{
		if (!(t->prev_c = ft_memalloc(sizeof(t_exectoken))))
			return (NULL);
		t->prev_c->file_args = NULL;
		t->prev_c->file_opt = NULL;
		t->prev_c->left = NULL;
		t->prev_c->right = NULL;
	}
	if (t->prev_c == NULL)
		return (NULL);
	t->start_c = t->prev_c;
	t->prevdot_c = t->prev_c;
	while (tmp != NULL && !is_cmd_delim(tmp->operator_type))
		tmp = tmp->next;
	if (tmp == NULL)
		return (t->start_c);
	return (t->prev_c);
}

t_exectoken		*do_parser(t_lextoken *tmp)
{
	t_dop_str	*t;

	if (!(t = cr_dop_str_par()) || !(do_parser_dop(t, tmp)))
		return (NULL);
	while (tmp != NULL)
	{
		if (is_cmd_delim(tmp->operator_type))
			t->i_c = tmp->operator_type;
		else if (t->i_c != -1)
		{
			if (t->i_c == 2)
				if (!(t->prev_c = ft_cr_new_exectoken(tmp, t->prev_c, t->i_c, t)))
					return (NULL);
			if (t->i_c == 1)
			{
				if (!(t->prevdot_c = ft_cr_new_exectoken(tmp, t->prevdot_c, t->i_c, t)))
					return (NULL);
				t->prev_c = t->prevdot_c;
			}
			t->i_c = -1;
		}
		tmp = tmp->next;
	}
	return (t->start_c);
}

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_dop_str	*t;

	t = NULL;

	if (!(tmp = do_lexer(cmd)))
		return (NULL);
	//ft_printf("\n%s\n", tmp->line);
	//ft_printf("\n%s\n", tmp->next->line);
	free(t);

	extmp = do_parser(tmp);

	ft_distr_lex(tmp);
	return (extmp);
}