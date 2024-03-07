#include "tictactoe.h"

int	rnd_move(t_node *nd)
{
	int		sum;
	int		pos;

	sum = 0;
	pos = -1;
	/*show_node(nd);*/
	while (++pos < 9)
		sum += nd->chances[pos];
	/*printf("\nsum: %i\n", sum);*/
	sum *= rand() & 255;
	/*printf("sum*rnd&255: %i\n", sum);*/
	sum = (sum >> 8) + 1;
	/*printf("sum>>8+1: %i\n", sum);*/
	pos = -1;
	while (sum > 0)
	{
		sum -= nd->chances[++pos];
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
	all->now++;
	all->now->board = new_board;
	all->now->op_min = reduce(new_board);
	new_board = rearrange(new_board, all->now->op_min);
	all->now->box = find(new_board, all->nd);
	all->now->move = -1;
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
	return (pin->box->paths);
}

void play(t_set *all)
{
	char	magic[] = "165840327";
	int	pos;
	int	brd;
	int	winner;
	int	n_players;
	int	machine;
	int	turn;

	while (1)
	{
		n_players = -1;
		while (n_players < 0 || n_players > 2)
		{
			printf("\nNumber of human players? (0, 1 or 2) ");
			scanf("%d", &n_players);
			if (n_players < 0 || n_players > 2)
				printf("\nERROR\n");
		}
		if (1 == n_players)
			machine = 0;
		else
			machine = 1;
		while (machine < 1 || machine > 2)
		{
			printf("\nWho plays first? (1 beast, 2 poor human) ");
			scanf("%d", &machine);
			if (machine < 1 || machine > 2)
				printf("\nERROR\n");
		}
		brd = 0;
		while (!won(brd) && gaps(brd))
		{
			if (n_players)
				show_board(brd);
			turn = (1 + gaps(brd)) % 2 + 1;
			pos = -1;
			if ((1 == n_players && machine == turn) || !n_players)
				pos = apply_symm(rnd_move(all->now->box), all->now->op_min);
			while (pos < 0)
			{
				printf("\nPlayer %d, select position: ", turn);
				scanf("%d", &pos);
				if (pos < 0 || pos > 8 || mark(brd, magic[pos] - '0'))
				{
					pos = -1;
					printf("\nWrong position");
				}
			}
			if (2 == n_players || (machine != turn && 1 == n_players))
				pos = magic[pos] - '0';
			if (n_players)
				printf("%d\n\n", pos);
			brd = do_move(pos, all);
			if (brd < 0)
				return ;
			brd = all->now->board;
	/*		brd = rearrange(brd, all->op_min[all->moves - 1]);*/
		}
		show_game(all);
		winner = won(brd);
		if (winner > 0)
			printf("Player %d won!\n", winner); /*((all->moves - 1) % 2) + 1);*/
		else
			printf("The game ended in a draw\n");
		printf("\n\n**************************\nPlay again? (1 yes) ");
		scanf("%d", &pos);
		if (pos != 1)
			break;
		else
			all->now = all->step;
	}	
}
