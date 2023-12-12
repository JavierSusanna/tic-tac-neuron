#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_state
{
	int	board;
	int	next_move[9];
}		t_state;

typedef struct	s_game
{
	int	box[9];
	char	move[9];
}		t_game;

int	mark(int board, int pos)
{
	while (pos--)
		board /= 3;
	return (board % 3);
}

int	next_player(int board)
{
	int 	ct[3] = {0, 0, 0};
	int	pos;
	char	m;

	pos = -1;
	while(++pos < 9)
		ct[mark(board, pos)]++;
	if (ct[0] && ct[1] == ct[2])
		return (1);
	if (ct[0] && ct[1] - 1 == ct[2])
		return (2);
	return (0);
}

int	won(int board)
{
	int	pos;
	int	pos2;
	int	pos3;
	int	ct_lines = 0;
	int	m;
	int	who;

	who = 0;
	pos = -1;
	while(++pos < 4)
	{
		m = mark(board, pos);
		if (!m)
			continue ;
		pos2 = pos;
		pos3 = 12 - pos - pos2;
		while (--pos3 > ++pos2)
		{
			if (mark(board, pos2) == m && mark(board, pos3) == m)
			{
				who = m;
				ct_lines++;
			}
		}
	}
	if (!ct_lines)
		return (0);
	if (1 == ct_lines)
		return (who);
	return (-1);
}
/*                               XOR(H):         XOR(D):
 * 165  01.20.12 0001.1000.0110  0111.0000.0111  0000.0010.0010
   840  22.11.00 1010.0101.0000  1010.0000.1010  0010.0000.0010
   327  10.02.21 0100.0010.1001  1101.0000.1101  0010.0010.0000
   
   381  10.22.01 0100.1010.0001  0101.0000.0101  0000.1000.1000
   246  02.11.20 0010.0101.1000  1010.0000.1010  1000.0000.1000
   705  21.00.12 1001.0000.0110  1111.0000.1111  1000.1000.0000

   723  21.02.10 1001.0010.0100  1101.0000.1101  0000.0010.0010
   048  00.11.22 0000.0101.1010  1010.0000.1010  0010.0000.0010
   561  12.20.01 0110.1000.0001  0111.0000.0111  0010.0010.0000
   */

int	rearrange(int board, char *order_new)
{
	char	pos_ini[] = "507642183";
	int		pos;
	int		board_new;

	board_new = 0;
	pos = -1;
	while (++pos < 9)
		board_new = board_new * 3 + mark(board, order_new[pos_ini[pos] - '0'] - '0');
	return (board_new);
}

int	reduce(int board)
{
	char	order[8][10] = {"165840327", "381246705", "723048561",
		"507642183", "327840165", "705246381", "561048723", "183642507"};
	int	n;
	int	ret;

	ret = board;
	n = -1;
	while (++n < 8)
	{
		if (rearrange(board, order[n]) < ret)
			ret = rearrange(board, order[n]);
	}
	return (ret);
}

int	possible_line(int board, int i, int j)
{
	int	ct;

	ct = 0;
	ct |= 1 << mark(board, i);
	ct |= 1 << mark(board, j);
	ct |= 1 << mark(board, 12 - i - j);
	return ((ct & 6) != 6);
}

int	forced_draw(int board)
{
	char	order[] = "165840327";
	int		i;
	int		j;
	int		possible;

	possible = 0;
	i = -1;
	while (++i < 4 && !possible)
	{
		j = 3 - i;
		if (j < i)
			j = i;
		while (++j < 6 - i / 2)
			possible += possible_line(board, i, j);
	}
	return (!possible);
}

int	valid_board(int board)
{
	return (next_player(board) && !won(board) && reduce(board) == board
			&& !forced_draw(board));
}
/*
165840327 -> 012345678
012345678    507642183

165840327 -> 012345678
507642183 -> 258147036
723048561 -> 876543210
381246705 -> 630741852
165840327 -> 012345678

165840327 -> 012345678
561048723 -> 210543876
165840327 -> 012345678
*/
void	show_board(int board)
{
	char	order[] = "165840327";
	char	marks[] = ".OX";
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

void	initialize(t_state *st, int board)
{
	st->board = board;
	while (++n < 9)
	{
		if (mark(board, n))
			st->next_move[n] = 0;
		else
			st->next_move[n] = 8;
	}
}

int	find(int board, t_state **st)
{
	int	ret;

	ret = 0;
	while (st[ret]->board != board && st[ret]->board != -1)
		ret++;
	if (st[ret]->board == board)
		return (ret);
	return (-1);
}

int	move(int box, t_state **st)
{
	int	sum;
	int	n;
	int	trit;
	
	sum = 0;
	n = -1;
	while (++n < 9)
		sum += st[box]->next_move[n];
	sum *= rand() / (RAND_MAX >> 8);
	sum = sum >> 8;
	n = -1;
	trit = 1;
	while (sum > 0)
	{
		sum -= st[box]->next_move[++n];
		trit *= 3;
	}
	return (st[box]->board + trit * next_player(board));
}

void	play(t_state **st)
{
	int	n;
	int	board;
	int	box;

	n = 0;
	while (++n < 10000)
	{
		board = 0;
		box = find(board, st);
		while (box > -1)
		{
			board = move(box, st);
			box = find(board, st);
		}
		if (won(board))
			;
		else
			;
	}
}

int	main(void)
{
	int	n;
	int ct_valid;
	t_state	state[600];

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));
	ct_valid = 0;
	n = -1;
	while (++n < 27*27*27)
	{
		if (valid_board(n))
		{
			initialize(*(state[ct_valid]), n);
			ct_valid++;
			show_board(n);
		}
	}
	state[ct_valid].board = -1;
	printf("Valid boards: %i\n", ct_valid);
	play(state);
	return (0);
}
/*
int	main(void)
{
	int	board;

	board = 13932;
	show_board(board);
	board = rearrange(board, "381246705");
	show_board(board);
	return (0);
}*/
