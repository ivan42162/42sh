#include "../../inc/fshell.h"

int				get_op_type(char *operator)
{
	int			i;
	static char	operators[9][5] = {";;", ";", "|",\
		"<<", "<", ">>", ">", ">&", "<&"};

	i = 0;
	if (ft_strstr(operator, operators[i]) != NULL)
		return (-1);
	else if (ft_strstr(operator, "<>") != NULL)
		return (-1);
	else if (ft_strstr(operator, "<<-") != NULL)
		return (-1);
	else if (ft_strstr(operator, "||") != NULL)
		return (-1);
	else if (ft_strstr(operator, ">|") != NULL)
		return (-1);
	else if (ft_strstr(operator, ">>>") != NULL)
		return (-1);
	i++;
	while (i < 10)
	{
		if (ft_strcmp(operator, operators[i]) == 0)
			return (i);
		i++;
	}
	return (-2);
}