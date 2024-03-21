### FILES AND DIRECTORIES ###
NAME = tic-tac-neuron
GC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c89 #-g -O2 -fsanitize=thread -pthread #-g3 -fsanitize=address 
INCLUDES = include

DIR_TTN = ./
FILES_TTN = train matrix

FILES_SRC += $(addprefix $(DIR_TTN), $(FILES_TTN))

DIR_OBJ = obj/
FILES_OBJ = $(addprefix $(DIR_OBJ), $(addsuffix .o, $(FILES_TTN)))


#####################
### PROGRAM RULES ###
#####################

all: #$(NAME)
	@echo "\nNeural network not implemented."
	@echo "Change directory \033[0;32mcd create_training_set\033[0m to see most interesting stuff.\n"

$(NAME): $(FILES_OBJ)
	$(GC) $(FILES_OBJ) -o $(NAME) $(CFLAGS) #-fsanitize=address
#	@ar rsc $(NAME) $(FILES_OBJ)
	@echo "SUCCESSFULLY COMPILED $(NAME)"

$(DIR_OBJ)%.o: $(DIR_TTN)%.c | DIRECTORIES #LIB
	@$(GC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@
	@echo "COMPILED OBJECT $@"

DIRECTORIES:
	@mkdir -p $(DIR_OBJ)
	

bonus: all

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
