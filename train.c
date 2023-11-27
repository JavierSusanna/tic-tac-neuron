#include "neuraln.h"

int	ft_atoi(const char *str)
{
	unsigned long long	ret;
	unsigned long long	max;
	int					sign;
	int					i;

	max = 0x7fffffffffffffff;
	i = 0;
	while (' ' == str[i] || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if ('-' == str[i])
		sign = -1;
	if ('-' == str[i] || '+' == str[i])
		i++;
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i++] - '0');
		if (ret > max + (1 - sign) / 2)
			return (- (sign + 1) / 2);
	}
	return (sign * ret);
}

int	main(void)
{
	t_matrix	t;
	int			i;
	int			j;
	char 		tmp[5];

	read(0, tmp, 3);
	t.cols = ft_atoi(tmp);
	read(0, tmp, 3);
	t.rows = ft_atoi(tmp);
	t.val = malloc(t.cols * sizeof(*t.val));
	t.val[0] = malloc(t.rows * t.cols * sizeof(**t.val));
	j = -1;
	while (++j < t.rows)
	{
		t.val[j] = t.val[0] + j * t.rows;
		printf("row %i\n", j);
		i = -1;
		while (++i < t.cols)
		{
			read(0, tmp, 3);
			t.val[j][i] = ft_atoi(tmp);
		}
	}
	prt(&t);
	return (0);
}
