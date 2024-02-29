#include "tictactoe.h"

void	clean_symm(t_state *st)
{
	int		op;
	int		pos;
	int		new_pos;

	/*printf("\nCleaning symmetries from board %i\n", st->board);*/
	pos = -1;
	while (++pos < 9)
		st->multiplicity[pos] = 0;
	op = 8;
	while (--op > 0)
	{
		if (rearrange(st->min_brd, op) == st->min_brd)
		{
	/*		printf("-op %i\n", op);*/
			pos = -1;
			while (++pos < 9)
			{
				new_pos = apply_symm(pos, op);
				if (!st->min_brd)
					printf("board 0, op %i: pos %i => %i\n", op, pos, new_pos);
				if (new_pos == pos)
					st->multiplicity[pos] = 1;
				else if (1 == op || 3 == op)
					st->multiplicity[pos] = 4;
				else
					st->multiplicity[pos] = 2;
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
		st->min_brd = id;
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
	st->min_brd = -1;	
}
