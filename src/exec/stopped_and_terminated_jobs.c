/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopped_and_terminated_jobs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:15:58 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/29 20:01:50 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././inc/fshell.h"
#include <errno.h>

static int		check_status(t_pstat *pstat, int status, pid_t pid, t_job *job)
{
	pstat->p->status = status;
	if (WIFSTOPPED(status))
	{
		pstat->p->stopped = 1;
		ft_dprintf(2, "\n");
		if (job != NULL)
			format_job_info(job, "stopped", num_of_the_job(job));
		//pstat->str_for_del = ft_itoa(WEXITSTATUS(status));
		//put_error_to_shell(WEXITSTATUS(status));
		//ft_strdel(&pstat->str_for_del);
	}
	else
	{
		pstat->p->completed = 1;
		pstat->p->status = WEXITSTATUS(status);
		//pstat->str_for_del = ft_itoa(pstat->p->status);
		put_error_to_shell(pstat->p->status);
		//ft_strdel(&pstat->str_for_del);
		pstat->ptmp = pstat->j->first_process;
		while (pstat->ptmp != pstat->p && (pstat->ptmp->completed = 1))
			pstat->ptmp = pstat->ptmp->next;
		if (WIFSIGNALED(status))
			ft_dprintf(globals()->fd[2], "%d: Terminated by signal %d.\n",
					   (int)pid, WTERMSIG(pstat->p->status));
	}
	return (0);
}

int				mark_process_status(pid_t pid, int status, t_job *job)
{
	t_pstat		pstat;

	pstat.job_count = 0;
	if (pid > 0)
	{
		pstat.j = globals()->g_f_job;
		while (pstat.j)
		{
			pstat.job_count++;
			pstat.p = pstat.j->first_process;
			while (pstat.p)
			{
				if (pstat.p->pid == pid)
					return (check_status(&pstat, status, pid, job));
				pstat.p = pstat.p->next;
			}
			pstat.j = pstat.j->next;
		}
		return (!ft_dprintf(globals()->fd[2], "No child process %d.\n", pid) - 1);
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	return (-1);
}

int				process_count(void)
{
	t_job		*job;
	t_process	*p;
	int			res;

	job = globals()->g_f_job;
	res = 0;
	while (job)
	{
		p = job->first_process;
		while (p)
		{
			res++;
			p = p->next;
		}
		job = job->next;
	}
	return (res);
}

void			update_status(void)
{
	int			status;
	pid_t		pid;
	int			counter;
	int			pr_count;
	t_job		*job;
	t_process	*pr;

	pr_count = process_count();
	status = 0;
	counter = 0;
	while (counter < pr_count)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		mark_process_status(pid, status, NULL);
		counter++;
	}
	job = globals()->g_f_job;
	while (job)
	{
		pr = job->first_process;
		while (pr)
		{
			pid = waitpid(pr->pid, &status, WNOHANG);
			//errno = 0;
//			dprintf(2, "\n|%d, %d, %d, %d, %d, %d, %d|\n", errno, pr->pid,
//					pid, status, WEXITSTATUS(status), WIFSIGNALED(status), WTERMSIG(status));
			mark_process_status(pid, status, job);
			pr = pr->next;
		}
		job = job->next;
	}
}

void			wait_for_job(t_job *j)
{
	int			status;
	pid_t		pid;

	status = 0;
	while (1)
	{
		if (job_is_stopped(j))
			break ;
		pid = waitpid(-j->pgid, &status, WUNTRACED);
		mark_process_status(pid, status, j);
	}
}