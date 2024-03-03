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

	printf("%d\n", st->min_brd);
	pos = -1;
	while (++pos < 9)
	{
		m = mark(st->min_brd, order[pos] - '0');
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
	printf("%i loses, %i draws, %i wins\n", st->paths[0], st->paths[1], st->paths[2]);
	write(1, "\n", 1);
}

void	show_row(int board, int row, t_state *st, int op_min)
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
		if (!m)
		{
			val = st->good[apply_symm(order[row * 3 + pos] - '0', opposite(op_min))] + '0';
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
	while (++i < all->moves && all->step[i].box)
		printf("%i ", all->step[i].box->min_brd);
	write(1, "\n", 1);
	row = -1;
	while (++row < 3)
	{
		i = -1;
		while (++i < all->moves)
		{
			state = all->step[i].box;
			show_row(all->step[i].board, row, state, all->step[i].op_min);
			if (i < all->moves - 1)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}
