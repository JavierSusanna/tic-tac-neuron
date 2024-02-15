#include "tictactoe.h"

int	rnd_move(t_state *st)
{
	int		sum;
	int		pos;

	sum = 0;
	pos = -1;
	/*show_state(st);*/
	while (++pos < 9)
		sum += st->good[pos];
	/*printf("\nsum: %i\n", sum);*/
	sum *= rand() & 255;
	/*printf("sum*rnd&255: %i\n", sum);*/
	sum = (sum >> 8) + 1;
	/*printf("sum>>8+1: %i\n", sum);*/
	pos = -1;
	while (sum > 0)
	{
		sum -= st->good[++pos];
	/*	printf("after pos: %i, sum: %i\n", pos - 1, sum);*/
	}
	/*printf("pos: %i\n", pos);*/
	return (pos);
}

void	put_mark(int *board, int pos, int m)
{
	int	trit;

	trit = 1;
	while (pos-- > 0)
		trit *= 3;
	*board += trit * m;
}

int	do_move(int pos, t_set *all)
{
	int	new_board;

	all->move[all->moves] = pos;
	new_board = 0;
	if (all->moves)
		new_board = all->st[all->box[all->moves - 1]].board;
	put_mark(&new_board, pos, all->moves % 2 + 1);
	if (all->moves)
		new_board = rearrange(new_board, opposite(all->transform[all->moves - 1]));
	all->board[all->moves] = new_board;
	all->transform[all->moves] = reduce(new_board);
	new_board = rearrange(new_board, all->transform[all->moves]);
	all->box[all->moves] = find(new_board, all->st);
	all->moves++;
	return (new_board);
}

void	play(t_set *all)
{
	int	n;
	int	pos;
	int	board;

	n = 0;
	while (++n < 10000)
	{
		/*printf("\n*****************\ngame %i/9999\n", n);*/
		all->moves = 0;
		all->box[all->moves] = 0;
		while (!all->moves || all->box[all->moves - 1] > -1)
		{
			if (!all->moves)
				pos = rnd_move(all->st);
			else
				pos = rnd_move(all->st +  all->box[all->moves - 1]);
			/*printf("move %i: pos %i\n", all->moves, pos);*/
			board = do_move(pos, all);
/*			show_board(all->board[all->moves - 1]);
			printf("board %i, box %i\n\n", board, all->box[all->moves - 1]);*/
		}
		show_game(all);
		if (gaps(board) < 0)
			show_state(all->st + all->box[all->moves - 1]);
		if (won(board))
		{
/*			printf("_______________\nmoves %i\nboard %i won at %i\n_______________\n\n"
			, all->moves, all->st[all->box[all->moves - 2]].board, all->move[all->moves - 2]);*/
			all->st[all->box[all->moves - 2]].good[all->move[all->moves - 1]] = 9;
			all->st[all->box[all->moves - 3]].good[all->move[all->moves - 2]] = 1;
		}
		else
			all->st[all->box[all->moves - 2]].good[all->move[all->moves - 1]] = 2;
	}
	printf("end$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}