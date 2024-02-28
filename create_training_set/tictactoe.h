#ifndef TICTACTOE_H
# define TICTACTOE_H

# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct	s_state
{
	int	board;
	int	multiplicity;
	int	good[9];
	int	paths[3];
	int	chances[9];
}		t_state;

typedef struct	s_set
{
	t_state	st[628];
	int	moves;
	int	move[9];
	int	board[9];
	int	transform[9];
	int	box[9];
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
int	find(int board, t_state *st);

/* game.c*/
int	rnd_move(t_state *st);
void	put_mark(int *board, int pos, int m);
void	tmp_show(int *good);
int	max(int *good);
int	do_move(int pos, t_set *all);
int	*auto_play(t_set *all);
void	play(t_set *all);

/* show.c*/
void	show_board(int board);
void	show_state(t_state *st);
void	show_row(int board, int row, t_state *st, int transform);
void	show_game(t_set *all);

/* board_init.c*/
void	clean_symm(t_state *st);
int	valid_board(int board);
void	initialize(t_state *st);

/* combis.c*/
int	ft_atoi(char *str);
int	main(void);

#endif
