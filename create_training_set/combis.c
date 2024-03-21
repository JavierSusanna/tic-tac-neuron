#include "tic-tac-toe.h"

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
	int	*ans;

	setvbuf(stdout, NULL, _IONBF, 0);
	srand(time(NULL));
	initialize(&all);
	all.now = &(all.step[0]);
	all.now->board = 0;
	all.now->op_min = 0;
	all.now->box = &(all.nd[0]);
/*	printf("auto_play\n");*/
	ans = auto_play(&all);
/*	printf("Wins: %i\nDraws: %i\nLosses: %i\n", ans[2], ans[1], ans[0]);
	printf("####################\n");*/
	n = -1;
	while (++n < 627)
		show_results(all.nd + n);
<<<<<<< HEAD
	printf("\n");
=======
	printf("play1\n");*/
>>>>>>> fcdbbe746397b90440457d1bfa38af99c2bab625
	play(&all);
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
