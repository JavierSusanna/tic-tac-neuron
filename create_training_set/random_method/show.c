#include "tictactoe.h"

void	show_board(int board)
{
	char	order[] = "165840327";
	char	marks[] = ".XO";
	int		pos;
	char	m;

	printf("%d\n", board);
	pos = -1;
	while (++pos < 9)
	{
		m = mark(board, order[pos] - '0');
		write(1, marks + m, 1);
		if (pos % 3 == 2)
			write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

void	show_state(t_state *st)
{
	char	order[] = "165840327";
	char	marks[] = ".XO";
	int		pos;
	char	val;
	int		m;

	printf("%d\n", st->board);
	pos = -1;
	while (++pos < 9)
	{
		m = mark(st->board, order[pos] - '0');
		if (!m)
		{
			val = st->good[order[pos] - '0'] + '0';
			write(1, &val, 1);
		}
		else
			write(1, marks + m, 1);
		if (pos % 3 == 2)
			write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

void	show_row(int board, int row, t_state *st, int transform)
{
	char	order[] = "165840327";
	char	marks[] = ".XO";
	int		pos;
	char	val;
	char	m;

	if (row < 0 || row > 2 || board < 0 || board > 27 * 27 * 27)
		return ;
	pos = -1;
	while (++pos < 3)
	{
		m = mark(board, order[row * 3 + pos] - '0');
		if (!m && st)
		{
			val = st->good[apply_symm(order[row * 3 + pos] - '0', opposite(transform))] + '0';
			write(1, &val, 1);
		}
		else
			write(1, marks + m, 1);
	}
}

void	show_game(t_set *all)
{
	int		row;
	int		i;
	t_state	*state;

	i = -1;
	while (++i < all->moves && all->box[i] > -1)
		printf("%i ", all->st[all->box[i]].board);
	write(1, "\n", 1);
	row = -1;
	while (++row < 3)
	{
		i = -1;
		while (++i < all->moves)
		{
			state = NULL;
			if (all->box[i] > -1)
				state = all->st + all->box[i];
			show_row(all->board[i], row, state, all->transform[i]);
			if (i < all->moves - 1)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}
