NAME = so_long

CC = cc

CFLAGS = -Wall -Werror -Wextra

OS		= $(shell uname)

FILE_SRC = check_map2.c  check_map.c  graphic.c  init.c  parsing.c  so_long.c  touche.c  utils.c
FILE_OBJ = $(FILE_SRC:.c=.o)
MLX             = ./minilibx-linux/
MLX_LNK = -L $(MLX) -l mlx -lXext -lX11
MLX_INC	= -I $(MLX)
MLX_LIB	= $(addprefix $(MLX),mlx.a)

LIBFT		= libft/*c
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
GREEN = \033[32m
RESET = \033[0m

define PRINT_LOADING
	@printf "$(GREEN)Compiling... ["
	@for i in $(shell seq 0 10 100); do \
		printf "▓"; \
		sleep 0.1; \
	done
	@printf "] 100%%$(RESET)\n"
endef

.SILENT:
all : $(NAME)

$(NAME): $(FILE_OBJ)
	$(CC) $(CFLAGS) $(FILE_OBJ) $(LIBFT) $(MLX_LNK) $(MLX_INC) -o$(NAME)  libft/ft_printf/*c
	@echo -n "$(GREEN)Creating library...$(RESET)"
	@echo "$(GREEN)Library created successfully!$(RESET)"
	@$(PRINT_LOADING)
	@echo "$(GREEN) Compilation complete!$(RESET)"

clean :
	rm -rf *.o
	@echo "$(GREEN)Cleaning up...$(RESET)"
	@echo "$(GREEN)Cleanup complete!$(RESET)"

fclean : clean
	rm -rf $(NAME)
	@echo "$(GREEN)Removing library...$(RESET)"
	@echo "$(GREEN)Library removed!$(RESET)"

re :fclean all

.PHONY : all clean fclean re