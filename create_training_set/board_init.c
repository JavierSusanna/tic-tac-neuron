#include "tictactoe.h"

void	clean_symm(t_node *nd)
{
	int		op;
	int		pos;
	int		new_pos;

	/*printf("\nCleaning symmetries from board %i\n", nd->board);*/
	pos = -1;
	while (++pos < 9)
		nd->multiplicity[pos] = 1;
	op = 8;
	while (--op > 0)
	{
		if (rearrange(nd->min_brd, op) == nd->min_brd)
		{
	/*		printf("-op %i\n", op);*/
			pos = -1;
			while (++pos < 9)
			{
				new_pos = apply_symm(pos, op);
				if (!nd->min_brd)
					printf("board 0, op %i: pos %i => %i\n", op, pos, new_pos);
				if (new_pos == pos)
					nd->multiplicity[pos] = 1;
				else if (1 == op || 3 == op)
					nd->multiplicity[pos] = 4;
				else
					nd->multiplicity[pos] = 2;
				if (new_pos > pos)
					nd->good[new_pos] = 0;
			}
		}
	}
}

int	valid_board(int board)
{
	if (!won(board) && !reduce(board)) /* && !forced_draw(board))*/
		return (gaps(board));
	return (0);
}

void	initialize(t_node *nd)
{
	int	pos;
	int	id;

	id = -1;
	while (++id < 27 * 27 * 27)
	{
		if (valid_board(id) <= 0)
			continue ;
		nd->min_brd = id;
		pos = -1;
		while (++pos < 9)
		{
			if (mark(id, pos))
				nd->good[pos] = 0;
			else
				nd->good[pos] = 4;
		}
		clean_symm(nd);
		nd->paths[0] = 0;
		nd->paths[1] = 0;
		nd->paths[2] = 0;
		nd++;
	}
	nd->min_brd = -1;	
}
