NAME = lem-in
LIBFTA = $(LIB_DIR)libft.a

HEADER = $(HEAD_DIR)lem_in.h
LIB_H = $(LIB_DIR)libft.h

LIB_DIR = libft/
HEAD_DIR = includes/

HEAD = -I $(HEAD_DIR)
LIBFT_H = -I $(LIB_DIR)

COMP = gcc -Wall -Werror -Wextra

DIR = src/

OBJ_DIR = obj/

SRCS = ft_bfs.c ft_parse.c ft_parse_room.c ft_parse_link.c debug/ft_print_all.c main.c

C_FILE = $(SRCS)

OFILE = $(C_FILE:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OFILE))
SRC_DIR = $(addprefix $(DIR), $(SRCS))

all: $(NAME)

lib:
	@make -C $(LIB_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(HEADER) $(LIB_H) # $(OBJ)
	@make -C $(LIB_DIR)
	$(COMP) $(SRC_DIR) $(LIBFTA) $(HEAD) $(LIBFT_H) -o $(NAME)
	@echo -------compile lem-in finish----------

# $(OBJ_DIR)%.o: $(DIR)%.c $(HEADER)
# 	@$(COMP) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean
	@echo OBJECTS FILES HAS BEEN DELETED.

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_DIR) fclean
	@echo OBJECT FILES AND EXECUTABLE HAS BEEN DELETED.

re: fclean all