#include "neuraln.h"

int	ft_atoi(const char *str)
{
	unsigned long long	ret;
	unsigned long long	max;
	int					sign;
	int					i;

	max = (1ULL << (8 * sizeof(max) - 1)) - 1ULL;
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

void	say(char *txt)
{
	while (*txt)
		write(1, txt++, 1);
}

void	say_n(int n)
{
	int		sgn;
	char	d;

	sgn = 1;
	if (n < 0)
		sgn = -1;
	if (sgn < 0)
		say("-");
	if ((n / 10) * sgn > 10)
		say_n((n / 10) * sgn);
	d = (n % 10) * sgn + '0';
	write(1, &d, 1);
}

t_matrix	*input_matrix()
{
	t_matrix	*t;
	int			i;
	int			j;
	char 		tmp[5];

	t = malloc(sizeof(t_matrix));
	say("number of rows: ");
	read(0, tmp, 3);
	t->rows = ft_atoi(tmp);
	say("\nnumber of cols: ");
	read(0, tmp, 3);
	t->cols = ft_atoi(tmp);
	t->val = malloc(t->rows * sizeof(*t->val));
	t->val[0] = malloc(t->rows * t->cols * sizeof(**t->val));
	j = -1;
	while (++j < t->rows)
	{
		t->val[j] = t->val[0] + j * t->cols;
		say("\nrow ");
		say_n(j);
		say("\n");
		i = -1;
		while (++i < t->cols)
		{
			read(0, tmp, 3);
			t->val[j][i] = ft_atoi(tmp);
		}
	}
	return (t);
}

int	main(void)
{
	t_matrix	*t1;
	t_matrix	*t2;
	t_matrix	*t3;

	t1 = input_matrix();
	say("\n");
	t2 = input_matrix();
	say("\n");
	prt(t1);
	say("\n");
	prt(t2);
	t3 = prod(t1, t2);
	say("\nproduct: \n");
	prt(t3);
	return (0);
}
