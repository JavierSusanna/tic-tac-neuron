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

int	*play(t_set *all)
{
	int	pos;
	t_state	*state;
	int	*ans;
	int	mult;

	printf("moves: %i\n", all->moves);
	if (all->moves)
		state = &(all->st[all->box[all->moves - 1]]);
	else
		state = &(all->st[0]);
	if (state->paths[0] || state->paths[1] || state->paths[2])
		return (state->paths);
	pos = -1;
	while (++pos < 9)
	{
		if (state->good[pos] != 4)
			continue;
/*		mult = multiplicity(pos, all-> */
		if (won(do_move(pos, all)))
		{
			state->good[pos] = 3;
			state->paths[2]++;
		}
		else if (all->box[all->moves - 1] > -1)
		{
			ans = play(all);
			state->good[pos] = 4 - max(all->st[all->box[all->moves - 1]].good);
			state->paths[0] += ans[2];
			state->paths[1] += ans[1];
			state->paths[2] += ans[0];
		}
		else
		{
			state->good[pos] = 2;
			state->paths[1]++;
		}
		all->moves--;
	}
	return (state->paths);
}
