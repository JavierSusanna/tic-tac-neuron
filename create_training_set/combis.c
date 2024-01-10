#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
/*
typedef struct	s_game
{
	int	moves;
	int	box[9];
	char	move[9];
}		t_game;*/

typedef struct	s_state
{
	int	board;
	int	good[9];
}		t_state;

typedef struct	s_set
{
	t_state	st[628];
	int	moves;
	int	box[9];
	int	transform[9];
	int	move[9];
}		t_set;

int	mark(int board, int pos)
{
	while (pos--)
		board /= 3;
	return (board % 3);
}

int	gaps(int board)
{
	int 	ct[3] = {0, 0, 0};
	int	pos;
	char	m;

	pos = -1;
	while(++pos < 9)
		ct[mark(board, pos)]++;
	if (ct[1] == ct[2] || ct[1] - 1 == ct[2])
		return (ct[0]);
	return (-1);
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

int	rearrange(int board, int  op)
{
	char	order[8][10] = {"165840327", "381246705", "723048561",
		"507642183", "327840165", "705246381", "561048723", "183642507"};
	char	pos_ini[] = "507642183";
	char	*order_new;
	int		pos;
	int		board_new;

	order_new = order[op];
	board_new = 0;
	pos = 9;
	while (--pos >= 0)
		board_new = board_new * 3 + mark(board, order_new[pos_ini[pos] - '0'] - '0');
	return (board_new);
}

int	revert(int board, int  n)
{
	char	opposite[] = "03214567";

	return (rearrange(board, opposite[n] - '0'));
}

int	apply_symm(int pos, int  op)
{
	char	order[8][10] = {"165840327", "381246705", "723048561",
		"507642183", "327840165", "705246381", "561048723", "183642507"};
	char	pos_ini[] = "507642183";
	char	*order_new;

	order_new = order[op];
	return (order_new[pos_ini[pos] - '0']);
}

int	reduce(int board)
{
	int	n;
	int	min;
	int	min_n;

	min = board;
	min_n = 0;
	n = -1;
	while (++n < 8)
	{
		if (rearrange(board, n) < min)
		{
			min_n = n;
			min = rearrange(board, n);
		}
	}
	return (min_n);
}

void	clean_symm(t_state *st)
{
	int		op;
	int		pos;
	int		new_pos;

	op = 0;
	while (++op < 8)
	{
		if (rearrange(st->board, op) == st->board)
		{
			pos = -1;
			while (++pos < 4)
			{
				new_pos = apply_symm(pos, op);
				if (st->good[pos] && new_pos != pos)
					st->good[new_pos] = 0;
			}
		}
	}
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
	if (!won(board) && !reduce(board)) // && !forced_draw(board))
		return (gaps(board));
	return (0);
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
	int	m;

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

int	find(int board, t_state *st)
{
	int	ret;

	ret = 0;
	while (st[ret].board != board && st[ret].board != -1)
		ret++;
	if (st[ret].board == board)
		return (ret);
	return (-1);
}

int	rnd_move(t_state *st)
{
	int		sum;
	int		n;

	sum = 0;
	n = -1;
	while (++n < 9)
		sum += st->good[n];
	sum *= rand() & 255;
	sum = (sum >> 8) + 1;
	n = -1;
	while (sum > 0)
		sum -= st->good[++n];
	return (n);
}

int	do_move(int m, t_set *all)
{
	int	trit;
	int	new_board;

	all->move[all->moves] = m;
	trit = 1;
	while (m-- > 0)
		trit *= 3;
	new_board = 0;
	if (all->moves)
		new_board = all->st[all->box[all->moves - 1]].board;
	new_board += trit * (all->moves % 2 + 1);
	all->transform[all->moves] = reduce(new_board);
	new_board = rearrange(new_board, all->transform[all->moves]);
	all->box[all->moves] = find(new_board, all->st);
	all->moves++;
	return (new_board);
}

void	play(t_set *all)
{
	int	n;
	int	box;
	int	square;
	int	board;

	n = 0;
	while (++n < 4) //10000)
	{
		printf("*****************\n");
		all->moves = 0;
		all->box[all->moves] = 0;
		while (all->box[all->moves] > -1)
		{
			square = rnd_move(all->st +  all->box[all->moves]);
			board = do_move(square, all);
			printf("move %i: square %i\n", all->moves, square);
			show_board(board);
			printf("board %i, box %i\n", board, all->box[all->moves]);
		}
		if (won(board))
		{
			all->st[all->box[all->moves - 1]].good[all->move[all->moves - 1]] = 16;
			all->st[all->box[all->moves - 2]].good[all->move[all->moves - 2]] = 1;
		}
	}
}

void	initialize(t_state *st, int board)
{
	int	n;

	st->board = board;
	n = -1;
	while (++n < 9)
	{
		if (mark(board, n))
			st->good[n] = 0;
		else
			st->good[n] = 8;
	}
	clean_symm(st);
}

int	main(void)
{
	int	n;
	int	ct_valid;
	int	ct_valid1;
	int	val;
	t_set	all;

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));
	ct_valid = 0;
	ct_valid1 = 0;
	n = -1;
	while (++n < 27*27*27)
	{
		val = valid_board(n);
		if (val > 0)
		{
			initialize(&(all.st[ct_valid]), n);
			ct_valid++;
			/*show_board(n);*/
		}
		if (1 == val)
			ct_valid1++;
	}
	all.st[ct_valid].board = -1;
	printf("Valid boards: %i\n", ct_valid);
	printf("of which boards1: %i\n", ct_valid1);
	play(&all);
/*	n = -1;
	while (++n < 628)
		show_state(all.st + n);*/
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
