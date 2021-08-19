#ifndef MINITALK_H
# define MINITALK_H
# define BUFFERSIZE 1024
# include "libft.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_data
{
	char	string[BUFFERSIZE];
	int		data_bit;
	int		data_byte;
	int		finished;
	int		overflow;
}	t_data;

t_data	g_print = {{0}, 1 << 7, 0, 0, 0};

void	error(char *error_str);

#endif