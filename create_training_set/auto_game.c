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

	if (mark(all->step[all->moves].board, pos))
	{
		printf("ERROR: possition not empty.\n");
		return (-1);
	}
	all->step[all->moves].move = pos;
	new_board = all->step[all->moves].board;
	put_mark(&new_board, pos, (all->moves % 2) + 1);
	printf("   + mark: %d\n", new_board);
	all->moves++;
	all->step[all->moves].board = new_board;
	show_board(new_board);
	all->step[all->moves].transform = reduce(new_board);
	new_board = rearrange(new_board, all->step[all->moves].transform);
	printf("  reduced: %d\n\n", new_board);
	all->step[all->moves].box = find(new_board, all->st);
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
	t_state	*state;
	int	*ans;

	printf("moves: %i\n", all->moves);
	state = all->step[all->moves].box;
	if (state->paths[0] || state->paths[1] || state->paths[2])
		return (state->paths);
	pos = -1;
	while (++pos < 9)
	{
		if (state->good[pos] != 4)
			continue;
		if (won(do_move(pos, all)))
		{
			state->good[pos] = 3;
			state->paths[2] += state->multiplicity[pos];
		}
		else if (all->step[all->moves].box)
		{
			ans = auto_play(all);
			state->good[pos] = 4 - max(all->step[all->moves].box->good);
			state->paths[0] += ans[2] * state->multiplicity[pos];
			state->paths[1] += ans[1] * state->multiplicity[pos];
			state->paths[2] += ans[0] * state->multiplicity[pos];
		}
		else
		{
			state->good[pos] = 2;
			state->paths[1] += state->multiplicity[pos];
		}
		all->moves--;
	}
	mx = max(state->good);
	pos = -1;
	while (++pos < 9)
	{
		if (state->good[pos] == mx)
			state->chances[pos] = 1;/****** FIRST, SIMPLEST APPROACH ****/
		else
			state->chances[pos] = 0;
	}

	return (state->paths);
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
			printf("\nPlayer %d, select position: ", all->moves % 2 + 1);
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
		brd = all->step[all->moves].board;
/*		brd = rearrange(brd, all->transform[all->moves - 1]);*/
	}
	show_board(brd);
	winner = won(brd);
	if (winner > 0)
		printf("Player %d won!\n", winner); /*((all->moves - 1) % 2) + 1);*/
	else
		printf("The game ended in a draw\n");
	show_board(all->step[all->moves].board);
}
