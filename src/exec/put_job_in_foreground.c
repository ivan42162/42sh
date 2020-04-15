/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_foreground.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:11:37 by qmartina          #+#    #+#             */
/*   Updated: 2020/04/13 20:04:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

/* Put job j in the foreground.  If cont is nonzero,
   restore the saved terminal modes and send the process group a
   SIGCONT signal to wake it up before we block.  */

void	put_job_in_foreground (t_job *j, int cont)
{
	/* Put the job into the foreground.  */
	tcsetpgrp (g_shell_terminal, j->pgid);

	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		//tcsetattr (g_shell_terminal, TCSADRAIN, &j->tmodes);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}

	//dprintf(2, "\n\n\ndadadadad : |%p|\n", j);
	//dprintf(2, "\n\n\ndadadadad : |%p|\n", j->first_process);
	/* Wait for it to report.  */
	//wait_for_job(g_f_job);
	wait_for_job(j);
	//dprintf(2, "\n\n\ndadadadad : |%p|\n", j);


	/* Put the shell back in the foreground.  */
	tcsetpgrp (g_shell_terminal, g_shell_pgid);

	/* Restore the shell’s terminal modes.  */
	//tcgetattr (g_shell_terminal, &j->tmodes);
	//tcsetattr (g_shell_terminal, TCSADRAIN, &shell_tmodes);
}