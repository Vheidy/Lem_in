NAME = lem-in
LIBFTA = $(LIB_DIR)libft.a

HEADER = $(HEAD_DIR)lem_in.h
LIB_H = $(LIB_DIR)libft.h

LIB_DIR = libft/
HEAD_DIR = includes/

HEAD = -I $(HEAD_DIR)
LIBFT_H = -I $(LIB_DIR)

COMP = gcc -Wall -Werror -Wextra $(HEAD) $(LIBFT_H)

DIR = src/

OBJ_DIR = obj/

SRCS = main.c ft_parse.c

C_FILE = $(SRCS)

OFILE = $(C_FILE:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OFILE))

all: $(NAME)

lib:
	@make -C $(LIB_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ) $(HEADER) $(LIB_H)
	@make -C $(LIB_DIR)
	@$(COMP) $(LIBFTA) $(OBJ) -o $(NAME)
	@echo -------compile len-in finish----------

$(OBJ_DIR)%.o: $(DIR)%.c $(HEADER)
	@$(COMP) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean
	@echo OBJECTS FILES HAS BEEN DELETED.

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_DIR) fclean
	@echo OBJECT FILES AND EXECUTABLE HAS BEEN DELETED.

re: fclean all