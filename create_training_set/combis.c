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

void	create_sets(t_node *nd)
{
	int	n;
	int	fd_basic;
	int	fd_all;

	fd_basic = open(BASIC_SET_FILE, O_CREAT | O_WRONLY);
	fd_all = open(ALL_SET_FILE, O_CREAT | O_WRONLY);
	if (fd_basic > 0 && fd_all > 0)
	{
		n = -1;
		while (++n < 627)
			show_results(nd + n, fd_basic, fd_all);
		chmod(BASIC_SET_FILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		chmod(ALL_SET_FILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
/*		fchmod(fd_basic, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		fchmod(fd_all, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);*/
		printf("\nTraining sets created\n");
	}
	else
		printf("\nError creating training sets\n");
	close(fd_basic);
	close(fd_all);
}

int	main(void)
{
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
	printf("Wins: %i\nDraws: %i\nLosses: %i\n", ans[2], ans[1], ans[0]);
	printf("####################\n");
	create_sets(all.nd);
	printf("\nYou can now play tic-tac-toe\n");
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
