/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_zam_eval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 19:53:08 by wstygg            #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval_expr.h"

char		*return_with_del(char *str)
{
	ft_strdel(&str);
	return (NULL);
}

char		*ft_do_cut(char *tmp, int *error)
{
	int					dopi;
	char				*str;
	char				*dop;
	char				*str_for_rec;
	char				*str_for_del;

	dopi = 0;
	if (tmp[dopi] == '(' && tmp[dopi + 1] == '(')
		if (sc_size(&tmp[dopi], '(') != -1 &&
			sc_size(&tmp[dopi + 1], '(') != -1)
		{
			dopi = sc_size(&tmp[dopi], '(') - 3;
			dop = ft_strsub(tmp, 2, dopi - 2);
			str_for_del = dop;
			str_for_rec = ft_main_calc_rec(dop, error);
			if (*error == 1)
				return (NULL);
			if (str_for_rec != NULL)
				dop = str_for_rec;
			str = ft_itoa(eval_expr(dop, error));
			(str_for_del != dop) ? ft_strdel(&str_for_del) : 0;
			if (*error == 1)
				return (return_with_del(str));
			return (str);
		}
	return (NULL);
}

char		*ft_main_calc_rec(char *mas, int *error)
{
	char	*newstr;
	char	*cut_str;
	int		i;
	int		d;

	i = 0;
	d = 0;
	if (!(newstr = ft_memalloc(ft_strlen(mas) + 1)))
		return (NULL);
	while (i < (int)ft_strlen(mas) && mas[i] != '\0')
	{
		if (mas[i] == '$')
		{
			d++;
			if (!(cut_str = ft_do_cut(mas + 1, error)))
				return (return_with_del(newstr));
			i += sc_size(&mas[i + 1], mas[i + 1]);
		}
		else
		{
			cut_str = ft_strdup(" ");
			cut_str[0] = mas[i];
			i++;
		}
		ft_strcat(newstr, cut_str);
		ft_strdel(&cut_str);
	}
	if (d > 0)
		return (newstr);
	return (return_with_del(newstr));
}

char		*ft_do_zam_eval(char *mas)
{
	char				*newstr;
	int					error;

	error = 0;
	if (mas == NULL)
		return (NULL);
	if (*mas == '\0')
		return (mas);
	if ((newstr = ft_main_calc_rec(mas, &error)) == NULL)
	{
		if (error == 1)
		{
			put_error_to_shell(2);
			ft_dprintf(globals()->fd[2], "parse error in eval near: |%s|\n", mas);
			ft_strdel(&mas);
			return (NULL);
		}
		return (mas);
	}
	ft_strdel(&mas);
	return (newstr);
}
