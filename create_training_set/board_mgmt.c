#include "tictactoe.h"

int	apply_symm(int pos, int  op)
{
	char	order[3][10] = {"012345678", "630741852", "210543876"};
	char	*order_new;

	if (op < 0 || op > 7)
		return (-1);
	if (!op)
		return (pos);
	if (op & 4)
	{
		order_new = order[2];
		op ^= 4;
	}
	else
	{
		order_new = order[1];
		op--;
	}
	return (apply_symm(order_new[pos] - '0', op));
}

int	rearrange(int board, int  op)
{
	int		pos;
	int		board_new;

	if (op < 0 || op > 7)
		return (-1);
	if (!op)
		return (board);
	board_new = 0;
	pos = 9;
	while (--pos >= 0)
		board_new = board_new * 3 + mark(board, apply_symm(pos, op));
	return (board_new);
}

int	opposite(int sym_op)
{
	char	oppo[] = "03214567";

	return (oppo[sym_op] - '0');
}
/*
int	revert(int board, int  n)
{
	char	opposite[] = "03214567";

	return (rearrange(board, opposite[n] - '0'));
}*/

int	reduce(int board)
{
	int	n;
	int	min;
	int	min_n;

	min = board;
	min_n = 0;
	n = -1;
	while (++n < 8)
	{
		if (rearrange(board, n) < min)
		{
			min_n = n;
			min = rearrange(board, n);
		}
	}
	return (min_n);
}

int	find(int board, t_state *st)
{
	int	ret;

	ret = 0;
	while (st[ret].board != board && st[ret].board != -1)
		ret++;
	if (st[ret].board == board)
		return (ret);
	/*printf("Board %i not found\n", board);*/
	return (-1);
}
