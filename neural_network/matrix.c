#include "neuraln.h"

void	prt(t_matrix *t)
{
	int	i;
	int	j;

	j = -1;
	while (++j < t->rows)
	{
		i = -1;
		while (++i < t->cols)
			printf("%5i\t", (int)t->val[j][i]);
		printf("\n");
	}
}
t_matrix	*prod(t_matrix *t1, t_matrix *t2)
{
	t_matrix	*ret;
	int			i;
	int			j;
	int			ct;

	ret = NULL;
	if (t1 && t2 && t1->cols == t2->rows)
	{
		ret = malloc(sizeof(t_matrix));
		if (ret)
		{
			ret->rows = t1->rows;
			ret->cols = t2->cols;
			ret->val = malloc(ret->rows * ret->cols * sizeof(**ret->val));

			ret->val = malloc(ret->rows * sizeof(*ret->val));
			ret->val[0] = malloc(ret->rows * ret->cols * sizeof(**ret->val));
			j = -1;
			while (++j < ret->rows)
			{
				ret->val[j] = ret->val[0] + j * ret->cols;
				i = -1;
				while (++i < ret->cols)
				{
					ret->val[j][i] = 0;
					ct = -1;
					while (++ct < t1->cols)
						ret->val[j][i] += t1->val[j][ct] * t2->val[ct][i];
				}
			}
		}
	}
	return (ret);
}
