/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continuing_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:19:34 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/20 14:49:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void			mark_job_as_running(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

void			continue_job(t_job *j, int foreground)
{
	if (j == NULL)
	{
		return ;
	}
	mark_job_as_running(j);
	if (foreground)
	{
		put_job_in_foreground(j, 1);
	}
	else
	{
		put_job_in_background(j, 1);
	}
}
