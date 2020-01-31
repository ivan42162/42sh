/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:54:50 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/29 15:54:51 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void				hash_init(void)
{
	register int	i;

	i = -1;
	while (++i < MAX_HASH)
		g_hash[i] = NULL;
}

t_hash			*parse_path(char *key)
{
	char			**path;
	int				i;
	char			*cat;

	if (ft_findenv("PATH=", g_env) == -404)
		return (NULL);
	path = ft_strsplit(g_env[ft_findenv("PATH=", g_env)] + 5, ":");
	i = -1;
	if (!access(key, X_OK))
		return (hash_create(ft_strdup(key), ft_strdup(key)));
	else
		while (path[++i])
		{
			cat = slash_cat(path[i], key);
			if (!access(cat, X_OK))
				return (hash_create(ft_strdup(key), cat));
			free(cat);
		}
	return (NULL);
}

char				*hash_parse(char *key)
{
	t_hash			*hash;
	int				id;

	id = str_to_hash(key);
	if (!g_hash[id])
		return ((g_hash[id] = parse_path(key)) ? g_hash[id]->value : NULL);
	else
	{
		hash = g_hash[id];
		while (hash->next)
		{
			if (!ft_strcmp(hash->value, key))
				return (hash->value);
			hash = hash->next;
		}
		if (!ft_strcmp(hash->key, key))
			return (hash->value);
		return ((hash->next = parse_path(key)) ? hash->next->value : NULL);
	}
}

void				hash_clear(void)
{
	t_hash			*hash;
	t_hash			*to_free;
	int				id;

	id = -1;
	while (++id < MAX_HASH)
		if (g_hash[id])
		{
			hash = g_hash[id];
			while (hash)
			{
				to_free = hash;
				hash = hash->next;
				free_hash(&to_free);
			}
			g_hash[id] = NULL;
		}
}

char				*hash_get(char *key)
{
	char			*var;

	var = hash_parse(key);
	if (!var)
	{
		ft_printf("21sh: command not found: %s\n", key);
		return (NULL);
	}
	else
	{
		if (check_file(var, IS_X) == 1 && !check_file(var, IS_D))
			return (var);
		else
		{
			hash_free_by_key(key);
			ft_printf("21sh: permission denied: %s\n", key);
			return (NULL);
	}
	}
}
