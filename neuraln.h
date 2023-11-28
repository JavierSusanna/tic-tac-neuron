
#ifndef NEURALN
# define NEURALN
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_matrix
{
	int		cols;
	int		rows;
	float	**val;
}				t_matrix;

typedef struct	s_layer
{
	unsigned int	size;
	unsigned char	*val;
	float			**param;
}				t_layer;

void		prt(t_matrix *t);
t_matrix	*prod(t_matrix *t1, t_matrix *t2);
#endif
