
#if ndef NEURALN
# define NEURALN
# include <stdio.c>

typedef struct	s_layer
{
	unsigned int	size;
	unsigned char	*val;
	float			**param;
}				t_layer

#endif
