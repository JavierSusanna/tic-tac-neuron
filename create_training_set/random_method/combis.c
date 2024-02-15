#include "tictactoe.h"

int	ft_atoi(char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9' || ret > 999999)
			return (-1);
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret);
}

int	main(void)
{
	int	n;
	t_set	all;

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));
	printf("init\n");
	initialize(all.st);
	printf("play\n");
	play(&all);
	n = -1;
	printf("####################\n");
	while (++n < 628)
		show_state(all.st + n);
	return (0);
}
/*
int	main(int narg, char **args)
{
	int	board;

	if (narg < 3)
		return (0);
	board = ft_atoi(args[1]);
	show_board(board);
	board = rearrange(board, ft_atoi(args[2]));
	show_board(board);
	return (0);
}
*/