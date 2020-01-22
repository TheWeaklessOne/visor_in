NAME = visor_in

SRC  =	Sources/graph.c			\
        Sources/graph_2.c		\
        Sources/graph_3.c		\
        Sources/additional.c	\
		Sources/rendering.c		\
		Sources/setup.c			\
		Sources/texture.c		\
		Sources/transform.c		\
		Sources/main.c			\
		Utils/ft_1.c			\
		Utils/ft_2.c			\
		Utils/ft_strsplit.c		\
		Utils/get_next_line.c	\
		Utils/list.c			\
		Utils/list_2.c			\

OBJ  = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -I ~/Library/Frameworks/SDL2.framework/Headers -I ~/Library/Frameworks/SDL2_ttf.framework/Headers -I ~/Library/Frameworks/SDL2_image.framework/Headers -F ~/Library/Frameworks

RED= \033[1;31m
GREEN= \033[1;32m
YELLOW= \033[1;33m
BLUE= \033[1;34m
VIOLET= \033[1;35m
RESET= \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME) -framework SDL2 -framework SDL2_image -framework SDL2_ttf
	@echo "$(GREEN)Project is successfully compiled$(RESET)"

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	@echo "$(RED)Suspending library files$(VIOLET)"
	rm -rf *.o

fclean: clean
	@echo "$(RED)Suspending project files$(VIOLET)"
	rm -rf $(OBJ)
	rm -rf $(NAME)
	@echo "$(RESET)"

re: fclean all
