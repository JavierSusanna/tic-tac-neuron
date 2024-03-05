#include "tictactoe.h"

int	rnd_move(t_node *nd)
{
	int		sum;
	int		pos;

	sum = 0;
	pos = -1;
	/*show_node(nd);*/
	while (++pos < 9)
		sum += nd->good[pos];
	/*printf("\nsum: %i\n", sum);*/
	sum *= rand() & 255;
	/*printf("sum*rnd&255: %i\n", sum);*/
	sum = (sum >> 8) + 1;
	/*printf("sum>>8+1: %i\n", sum);*/
	pos = -1;
	while (sum > 0)
	{
		sum -= nd->good[++pos];
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
	int	mk;

	if (mark(all->now->board, pos))
	{
		printf("ERROR: position %i not empty.\n", pos);
		show_board(all->now->board);
		printf("op_min: %d\n", all->now->op_min);
		printf("opposite op_min: %d\n", opposite(all->now->op_min));
		printf("apply opposite op_min to 3: %d\n", apply_symm(3, opposite(all->now->op_min)));
		printf("min_board: %d\n", all->now->box->min_brd);
		exit(1);
		return (-1);
	}
	all->now->move = pos;
	new_board = all->now->board;
	mk = gaps(new_board);
	if (mk > 0)
	{
		mk = (1 + mk) % 2 + 1;
		put_mark(&new_board, pos, mk);
	}
	else
		return (-1);
	printf("   + mark %d at %d: %d\n", mk, pos, new_board);
	all->now++;
	all->now->board = new_board;
	show_board(new_board);
	all->now->op_min = reduce(new_board);
	new_board = rearrange(new_board, all->now->op_min);
	printf("  reduced: %d\n\n", new_board);
	all->now->box = find(new_board, all->nd);
	return (new_board);
}

void	tmp_show(int *good)
{
	int	i;

	write(1, "8654!\n", 6);
	i = -1;
	while (++i < 9)
		printf("%i ", good[i]);
	printf("\n");
}

int	max(int *good)
{
	int	i;
	int	max;

	i = -1;
	max = -1;
	while (++i < 9)
	{
		if (max < good[i])
			max = good[i];
	}
	return (max);
}

int	*auto_play(t_set *all)
{
	int	pos;
	int	mx;
	t_level	*pin;
	int	*ans;

	pin = all->now;
	if (pin->box->paths[0] || pin->box->paths[1] || pin->box->paths[2])
		return (pin->box->paths);
	pos = -1;
	while (++pos < 9)
	{
		if (pin->box->good[pos] != 4)
			continue;
		if (mark(pin->board, apply_symm(pos, pin->op_min)))
		{
			printf("***********************pos %i \n", pos);
			show_board(pin->board);
			printf("***********************\n");
		}
		if (won(do_move(apply_symm(pos, pin->op_min), all))) /*opposite(pin->op_min)*/
		{
			printf("won\n");
			pin->box->good[pos] = 3;
			pin->box->paths[2] += pin->box->multiplicity[pos];
		}
		else if (all->now->box)
		{
			ans = auto_play(all);
			pin->box->good[pos] = 4 - max(all->now->box->good);
			pin->box->paths[0] += ans[2] * pin->box->multiplicity[pos];
			pin->box->paths[1] += ans[1] * pin->box->multiplicity[pos];
			pin->box->paths[2] += ans[0] * pin->box->multiplicity[pos];
		}
		else
		{
			pin->box->good[pos] = 2;
			pin->box->paths[1] += pin->box->multiplicity[pos];
		}
		if (all->now == all->step)
			printf("can't go back.\n");
		else
			all->now--;
	}
	mx = max(pin->box->good);
	pos = -1;
	while (++pos < 9)
	{
		if (pin->box->good[pos] == mx)
			pin->box->chances[pos] = 1;/****** FIRST, SIMPLEST APPROACH ****/
		else
			pin->box->chances[pos] = 0;
	}
	printf("returning\n");
	return (pin->box->paths);
}

void play(t_set *all)
{
	char	magic[] = "165840327";
	int	pos;
	int	brd;
	int	winner;

	brd = 0;
	while (valid_board(brd))
	{
		show_board(brd);
		pos = -1;
		while (pos < 0)
		{
			printf("\nPlayer %d, select position: ", (1 + gaps(brd)) % 2 + 1);
			scanf("%d", &pos);
			printf(" pos %d ", pos);
			if (pos < 0 || pos > 8 || mark(brd, magic[pos] - '0'))
			{
				pos = -1;
				printf("\nWrong position");
			}
		}
		printf("%d\n\n", magic[pos] - '0');
		brd = do_move(magic[pos] - '0', all);
		if (brd < 0)
			return ;
		brd = all->now->board;
/*		brd = rearrange(brd, all->op_min[all->moves - 1]);*/
	}
	show_board(brd);
	winner = won(brd);
	if (winner > 0)
		printf("Player %d won!\n", winner); /*((all->moves - 1) % 2) + 1);*/
	else
		printf("The game ended in a draw\n");
	show_board(all->now->board);
}
