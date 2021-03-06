/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 19:01:04 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:45 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

t_lextoken					*do_lexer(char *line);
t_exectoken					*all_parse(char *cmd);
t_exectoken					*do_parser(t_lextoken *tmp);
char						*do_zam_str_hist_var(char *str1, t_memory *q);
int							get_op_type(char *operator);
t_dop_str					*cr_dop_str_par(void);
int							isoperator(char c);
int							isword(char c);
int							do_zamena_slash(char *line, t_readline *p);
int							ispar(char c);
t_exectoken					*ft_cr_new_exectoken(t_lextoken *tmp,
							t_exectoken *prev, int op_type, t_dop_str *t);
int							c_size(char *str, char b);
int							word_size(char *str);
t_lextoken					*add_token(t_lextoken *start, char *line);
char						*do_obr_zamena_sp(char *line);
void						dop_cr_new_exec(t_dop_str *t,
							t_exectoken *prev, int op_type, int type);
t_dop_str					*cr_dop_str_par1(t_lextoken *tmp1);
int							ft_error(int error, char *dopline);
int							is_cmd_delim(int i);
char						*do_zam_str_bax(char *str1, t_dop_str *t);
char						*do_zam_str_hist_var(char *str1, t_memory *q);
char						*do_obr_zamena_sp(char *line);
char						*do_zamena_sp(char *line);
char						*do_zam_str_by_str(int start,
							int end, char *str, char *zam_str);
t_lextoken					*ft_cr_new_token(char *line, int op_type);
char						*do_obr_zamena_sp(char *line);
char						*do_obr_zamena_bax(char *line);
int							ispar(char c);
int							isword(char c);
int							isoperator(char c);
int							issc(char c);
t_lextoken					*ft_kill_str_dop_lex(t_dop_str *t, t_lextoken *tmp);
t_exectoken					*ft_kill_str_dop_exec(t_dop_str *t,
							t_exectoken *tmpexec);
t_lextoken					*do_lexer(char *line);
int							dop_lexer2(t_dop_str *tmp, char *line);
int							dop_lexer(t_dop_str *tmp, char *line);
t_dop_str					*cr_dop_str(char **line1);
t_lextoken					*do_zam_bax_and_hist_full(t_lextoken *h, t_lextoken **save_tmp);
char						*get_num_from_hist_cons(t_memory *t, char *name);
char						*get_num_from_hist_begin(t_memory *t, int num);
char						*get_num_from_hist_end(t_memory *t, int num);
char						*get_num_from_hist_starting(t_memory *t,
							char *name);
int							is_cmd_redirect(int i);

#endif
