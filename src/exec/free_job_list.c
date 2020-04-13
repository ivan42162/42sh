#include "fshell.h"

void	free_process(t_process *tmp)
{
	t_process	*process_for_del;

	while (tmp)
	{
		process_for_del = tmp;
		tmp = tmp->next;
		free(process_for_del);
	}

}

void	free_job(t_job *tmp)
{
	if (tmp)
	{
		free_process(tmp->first_process);
		ft_strdel(&tmp->command);
		free(tmp);
	}
}

int		do_job_del()
{
	t_job	*j;
	t_job	*jlast;
	t_job	*jnext;
	t_job	*jdop;
	int d;

	d = 0;
	update_status();
	jlast = NULL;
	j = f_job;
	while (j)
	{
		d++;
		jnext = j->next;
		jdop = NULL;
		if (job_is_completed(j))
		{
			if (j->first_process->foreground == 0)
				format_job_info(j, "completed", d);
			if (jlast)
				jlast->next = jnext;
			else
				f_job = jnext;
			jdop = j;
		}
		else
			jlast = j;
		j = j->next;
		if (jdop != NULL)
			free_job(jdop);
	}
	return (1);
}