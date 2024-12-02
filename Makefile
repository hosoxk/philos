NAME = philo
CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra
MAKEFLAGS += -s

SRC_DIR = ./sources

SRC_FILES = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/safe_functions.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/dinner.c \
		$(SRC_DIR)/write.c \
		$(SRC_DIR)/getters_setters.c \
		$(SRC_DIR)/synchro_utils.c \
		$(SRC_DIR)/monitor.c

OBJ_FILES = $(SRC_FILES:.c=.o)


MAGENTA = \033[1;35m
YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "$(MAGENTA)Using compiler: $(CC)$(RESET)"
	@echo "$(MAGENTA)Using flags: $(CFLAGS) $(RESET)"
	@echo "$(YELLOW)Linking $(NAME) to $(OBJ_FILES)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)Compilation $(NAME) successfull!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $(notdir $<)...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	rm -fr $(OBJ_FILES)
	@echo "$(GREEN)Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing $(NAME) executable...$(RESET)"
	rm -fr $(NAME)
	@echo "$(GREEN)Executable $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
