#include "tic-tac-toe.h"

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
	int	op;
	int	min;
	int	min_op;

	min = board;
	min_op = 0;
	op = -1;
	while (++op < 8)
	{
		if (rearrange(board, op) < min)
		{
			min_op = op;
			min = rearrange(board, op);
		}
	}
	return (min_op);
}

t_node	*find(int board, t_node *nd)
{
	t_node	*ret;

	ret = nd;
	while (ret->min_brd != board && ret->min_brd != -1)
		ret++;
	if (ret->min_brd == board)
		return (ret);
	return (NULL);
}
