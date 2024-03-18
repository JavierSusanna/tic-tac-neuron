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

void	show_results(t_node *nd)
{
	int	i;
	int	j;
	int	op;
	int	done[8];
	int	brd;

	op = 0;
	while (op < 8)
		done[op++] = -1;
	op = -1;
	while (++op < 1)
	{
		brd = rearrange(nd->min_brd, op);
		j = -1;
		while (++j < 8)
		{
			if (done[j] == brd || -1 == done[j])
				break ;
		}
		if (-1 == done[j])
		{
			done[j] = brd;
			printf("%i ", brd);
			i = -1;
			while (++i < 9)
				printf("%i", nd->chances[apply_symm(i, op)]);
			printf("\n");
		}
	}
}

void	show_node(t_node *nd)
{
	char	order[] = "165840327";
	char	marks[] = ".XO";
	int		pos;
	char	val;
	int		m;

	printf("%d\n", nd->min_brd);
	pos = -1;
	while (++pos < 9)
	{
		m = mark(nd->min_brd, order[pos] - '0');
		if (!m)
		{
			val = nd->good[order[pos] - '0'] + '0';
			write(1, &val, 1);
		}
		else
			write(1, marks + m, 1);
		if (pos % 3 == 2)
			write(1, "\n", 1);
	}
	printf("%i loses, %i draws, %i wins\n", nd->paths[0], nd->paths[1], nd->paths[2]);
	write(1, "\n", 1);
}

void	show_row(int board, int row, t_node *nd, int op_min)
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
		if (!m && nd)
		{
			val = nd->good[apply_symm(order[row * 3 + pos] - '0', opposite(op_min))] + '0';
			write(1, &val, 1);
		}
		else
			write(1, marks + m, 1);
	}
}

void	show_game(t_set *all)
{
	int		row;
	t_level	*i;

	write(1, " ", 1);
	i = all->step;
	while (i->move > -1)
	{
		printf("%5i ", i->box->min_brd);
		i++;
	}
		printf("%5i \n", i->board);
	row = -1;
	while (++row < 3)
	{
		i = all->step;
		while (1)
		{
			write(1, "   ", 3);
			show_row(i->board, row, i->box, i->op_min);
			if (i->move < 0)
				break;
			i++;
		}
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}
