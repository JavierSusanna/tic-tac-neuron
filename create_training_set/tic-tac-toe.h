#ifndef TICTACTOE_H
# define TICTACTOE_H

# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
# include <fcntl.h>

# define BASIC_SET_FILE "basic_set.txt"
# define ALL_SET_FILE "extended_set.txt"
# define BASIC_SET 1
# define ALL_SYMMETRIES 8

typedef struct	s_node
{
	int	min_brd;
	int	multiplicity[9];
	int	good[9];
	int	paths[3];
	int	chances[9];
}		t_node;

typedef struct	s_level
{
	int	board;
	int	op_min;
	t_node	*box;
	int	move;
}		t_level;

typedef struct	s_set
{
	int		ct_holes[10];
	int		won[10];
	int		draw;
	t_node	nd[628];
	t_level	step[10];
	t_level	*now;
}		t_set;

/* board_ctrl.c*/
int	mark(int board, int pos);
int	gaps(int board);
int	won(int board);
int	possible_line(int board, int i, int j);
int	forced_draw(int board);

/* board_mgmt.c*/
int	apply_symm(int pos, int  op);
int	rearrange(int board, int  op);
int	opposite(int sym_op);
int	reduce(int board);
t_node	*find(int board, t_node *nd);

/* game.c*/
int	rnd_move(t_node *nd);
void	put_mark(int *board, int pos, int m);
void	tmp_show(int *good);
int	max(int *good);
int	do_move(int pos, t_set *all);
int	*auto_play(t_set *all);
void	play(t_set *all);

/* show.c*/
void	show_board(int board);
void	show_results(t_node *nd, int fd_basic, int fd_all);
void	show_node(t_node *nd);
void	show_row(int board, int row, t_node *nd, int op_min);
void	show_game(t_set *all);

/* board_init.c*/
void	clean_symm(t_node *nd);
int	valid_board(int board);
void	initialize(t_set *all);

/* combis.c*/
int	ft_atoi(char *str);
int	main(void);

#endif
