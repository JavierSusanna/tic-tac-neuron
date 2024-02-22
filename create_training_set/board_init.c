#include "tictactoe.h"

void	clean_symm(t_state *st)
{
	int		op;
	int		pos;
	int		new_pos;

	op = 0;
	st->multiplicity = 1;
	/*printf("\nCleaning symmetries from board %i\n", st->board);*/
	while (++op < 8)
	{
		if (rearrange(st->board, op) == st->board)
		{
	/*		printf("-op %i\n", op);*/
			if (1 == op || 3 == op)
				st->multiplicity = 4;
			else if (1 == st->multiplicity)
				st->multiplicity = 2;
			pos = -1;
			while (++pos < 9)
			{
				new_pos = apply_symm(pos, op);
	/*			printf(" >pos %i => %i\n", pos, new_pos);*/
				if (new_pos > pos)
					st->good[new_pos] = 0;
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

void	initialize(t_state *st)
{
	int	pos;
	int	id;

	id = -1;
	while (++id < 27 * 27 * 27)
	{
		if (valid_board(id) <= 0)
			continue ;
		st->board = id;
		pos = -1;
		while (++pos < 9)
		{
			if (mark(id, pos))
				st->good[pos] = 0;
			else
				st->good[pos] = 4;
		}
		clean_symm(st);
		st->paths[0] = 0;
		st->paths[1] = 0;
		st->paths[2] = 0;
		st++;
	}
	st->board = -1;	
}
