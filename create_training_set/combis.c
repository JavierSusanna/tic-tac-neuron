#include <stdio.h>
#include <unistd.h>

char	mark(int board, int pos)
{
	char	marks[] = ".ox";

	while (pos--)
		board /= 3;
	return (marks[board % 3]);
}

int	marks_ok(int board)
{
	int 	ct_1 = 0;
	int		ct_2 = 0;
	int		pos;
	char	m;

	pos = -1;
	while(++pos < 9)
	{
		m = mark(board, pos);
		if ('o' == m)
			ct_1++;
		else if ('x' == m)
			ct_2++;
	}
	return (ct_1 + ct_2 < 9 && (ct_1 == ct_2 || ct_1 - 1 == ct_2));
}

int	lines_ok(int board)
{
	int		pos;
	int		pos2;
	int		pos3;
	int 	ct_lines = 0;
	char	m;

	pos = -1;
	while(++pos < 4)
	{
		m = mark(board, pos);
		if ('.' == m)
			continue ;
		pos2 = pos;
		pos3 = 12 - pos - pos2 - 1;
		while (--pos3 > ++pos2)
		{
			if (mark(board, pos2) == m && mark(board, pos3) == m)
				ct_lines++;
		}
	}
	return (!ct_lines);
}

int	valid_board(int board)
{
	return (marks_ok(board) && lines_ok(board));
}

void	show_board(int board)
{
	char	order[] = "165840327";
	int		pos;
	char	m;

	pos = -1;
	while (++pos < 9)
	{
		m = mark(board, order[pos] - '0');
		write(1, &m, 1);
		if (pos % 3 == 2)
			write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

int	main(void)
{
	int	n;
	int ct_valid;

	ct_valid = 0;
	n = -1;
	while (++n < 27*27*27)
	{
		if (valid_board(n))
		{
			ct_valid++;
			show_board(n);
		}
	}
	printf("Valid boards: %i\n", ct_valid);
	return (0);
}
