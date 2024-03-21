#include "tic-tac-toe.h"

int	mark(int board, int pos)
{
	while (pos--)
		board /= 3;
	return (board % 3);
}

int	gaps(int board)
{
	int 	ct[3] = {0, 0, 0};
	int	pos;

	pos = -1;
	while(++pos < 9)
		ct[mark(board, pos)]++;
	if (ct[1] == ct[2] || ct[1] - 1 == ct[2])
		return (ct[0]);
	return (-1);
}

int	won(int board)
{
	int	pos;
	int	pos2;
	int	pos3;
	int	ct_lines = 0;
	int	m;
	int	who;

	who = 0;
	pos = -1;
	while(++pos < 4)
	{
		m = mark(board, pos);
		if (!m)
			continue ;
		pos2 = pos;
		pos3 = 12 - pos - pos2;
		while (--pos3 > ++pos2)
		{
			if (mark(board, pos2) == m && mark(board, pos3) == m)
			{
				if (!who)
				{
					who = m;
					ct_lines++;
				}
				else if (who == m)
					return (who);
				else
					return (-1);
			}
		}
	}
	if (!ct_lines)
		return (0);
	if (1 == ct_lines)
		return (who);
	return (-1);
}

int	possible_line(int board, int i, int j)
{
	int	ct;

	if (i + j < 4 || i + j > 12
		|| i + 2 * j == 12 || 2 * i + j == 12)
		return (0); 
	ct = 0;
	ct |= 1 << mark(board, i);
	ct |= 1 << mark(board, j);
	ct |= 1 << mark(board, 12 - i - j);
	return ((ct & 6) != 6);
}

int	forced_draw(int board)
{
	int		i;
	int		j;
	int		possible;

	possible = 0;
	i = -1;
	while (++i < 4 && !possible)
	{
		j = 3 - i;
		if (j < i)
			j = i;
		while (++j < 6 - i / 2)
			possible += possible_line(board, i, j);
	}
	return (!possible);
}