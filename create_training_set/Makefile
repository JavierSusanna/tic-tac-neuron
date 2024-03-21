### FILES AND DIRECTORIES ###
NAME = tic-tac-train
GC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c89 #-g -O2 -fsanitize=thread -pthread #-g3 -fsanitize=address 
INCLUDES = include

DIR_TTTR = ./
FILES_TTTR = combis board_init board_ctrl board_mgmt auto_game show

FILES_SRC += $(addprefix $(DIR_TTTR), $(FILES_TTTR))

DIR_OBJ = obj/
FILES_OBJ = $(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILES_TTTR)))


#####################
### PROGRAM RULES ###
#####################

all: $(NAME)

$(NAME): $(FILES_OBJ)
	$(GC) $(FILES_OBJ) -o $(NAME) $(CFLAGS) #-fsanitize=address
#	@ar rsc $(NAME) $(FILES_OBJ)
	@echo "SUCCESSFULLY COMPILED \033[0;31m$(NAME)\033[0m."

$(DIR_OBJ)%.o: $(DIR_TTN)%.c | DIRECTORIES #LIB
	@$(GC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@
	@echo "COMPILED OBJECT $@"

DIRECTORIES:
	@mkdir -p $(DIR_OBJ)

###################
### CLEAN RULES ###
###################

clean:
	@rm -rf $(DIR_OBJ)
	@echo "-TTN- OBJECTS DELETED. CLEAN SUCCESSFUL!"

fclean: clean
	@rm -rf $(NAME)
	@echo "-TTN- EXECUTABLE DELETED. CLEAN SUCCESSFUL!"

re:	fclean all
