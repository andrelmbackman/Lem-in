NAME 		=	lem-in
FLAGS		=	-Wall -Werror -Wextra
# DEBUG		=	-g -fsanitize=address
LIBFT 		=	libft/libft.a
INCL		= 	-Iincludes/

SRC 		= 	main.c parse.c init_structs.c free_structs.c \
				hash_tools.c add_tools.c find_paths.c bfs.c \
				path_tools.c move_ants.c error.c parse_tools.c bonus.c \
				move_ants_tools.c

SRC_DIR = src/
SRCS = $(addprefix $(SRC_DIR), $(SRC))

NODE_SRC = ft_nodeadd_end.c ft_nodeadd_front.c ft_nodedel_front.c ft_nodedel.c \
ft_nodenew.c ft_nodepop.c ft_nodeswap.c ft_nodeprint.c

NODE_DIR = node_struct/
NODE_SRCS = $(addprefix $(NODE_DIR), $(NODE_SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(NODE_SRCS) $(SRCS) Makefile
	@gcc -O3 $(DEBUG) $(FLAGS) $(INCL) -o $(NAME) $(NODE_SRCS) $(SRCS) $(LIBFT)
	@printf "Compilation done."

$(LIBFT):
	@$(MAKE) -C ./libft/ all

clean:
	@$(MAKE) -C ./libft/ clean
	@printf "Removed .o files"

fclean:
	@$(MAKE) -C ./libft/ fclean
	@/bin/rm -f $(NAME)
	@printf "Removed $(NAME) and $(LIBFT)"

re: fclean all

test1: all
	./$(NAME) < ./eval_tests/cases/augment_0.map

test2: all
	./$(NAME) < ./eval_tests/cases/augment_1.map

test3: all
	./$(NAME) < ./eval_tests/cases/augment_2.map

test4: all
	./$(NAME) < ./eval_tests/cases/augment_3.map

.PHONY: all clean fclean re