#include "../inc/fshell.h"

int					check_file(char *file, unsigned check)
{
	struct stat		st;
	int				ret;

	if (!file || lstat(file, &st) == -1)
		return (-1);
	ret = 1;
	if (check & IS_L)
		ret &= S_ISLNK(st.st_mode);
	if (check & IS_D)
		ret &= S_ISDIR(st.st_mode);
	if (check & IS_R)
		ret &= ((st.st_mode & S_IRUSR) != 0);
	if (check & IS_W)
		ret &= ((st.st_mode & S_IWUSR) != 0);
	if (check & IS_X)
		ret &= ((st.st_mode & S_IXUSR) != 0);
	return (ret);
}