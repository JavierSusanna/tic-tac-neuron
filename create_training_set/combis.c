#include <stdio.h>
#include <unistd.h>

int	mark(int board, int pos)
{
	while (pos--)
		board /= 3;
	return (board % 3);
}

int	marks_ok(int board)
{
	int 	ct[3] = {0, 0, 0};
	int		pos;
	char	m;

	pos = -1;
	while(++pos < 9)
		ct[mark(board, pos)]++;
	return (ct[0] > 1 && (ct[1] == ct[2] || ct[1] - 1 == ct[2]));
}

int	lines_ok(int board)
{
	int	pos;
	int	pos2;
	int	pos3;
	int	ct_lines = 0;
	int	m;

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
				ct_lines++;
		}
	}
	return (!ct_lines);
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

int	reduced_ok(int board)
{
	char	order[8][10] = {"165840327", "381246705", "723048561",
		"507642183", "327840165", "705246381", "561048723", "183642507"};
	int	n;

	n = -1;
	while (++n < 8)
	{
		if (rearrange(board, order[n]) < board)
			return (0);
	}
	return (1);
}

int	valid_board(int board)
{
	return (marks_ok(board) && lines_ok(board) && reduced_ok(board));
}
/*
165840327 -> 012345678
012345678    507642183
*/
void	show_board(int board)
{
	char	order[] = "165840327";
	char	marks[] = ".OX";
	int		pos;
	char	m;

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

int	main(void)
{
	int	n;
	int ct_valid;

	ct_valid = 0;
	n = -1;
	while (++n < 27*27*27)
	{
		if (valid_board(n))
		{
			ct_valid++;
			show_board(n);
		}
	}
	printf("Valid boards: %i\n", ct_valid);
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
