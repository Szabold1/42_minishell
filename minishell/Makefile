# Makefile for minishell

# Colour codes
RED					=	\033[01;31m
YELLOW				=	\033[01;33m
GREEN				=	\033[01;32m
RESET				=	\033[0m

# Executable name
NAME				=	minishell

# Source directories
SRC_DIR				=	src

# Libft
LIBFT_DIR			=	libft
LIBFT				=	$(LIBFT_DIR)/libft.a

# Other directories
OBJ_DIR				=	obj
INCLUDE_DIR			=	include
INPUT_CHECK_DIR		=	input_check
PARSE_LINE_DIR		=	parse_line
HEADERS				=	$(INCLUDE_DIR)/minishell.h \
						$(LIBFT_DIR)/include/libft.h

# Compiler and flags
CC = cc
CFLAGS				=	-Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
LFLAGS				=	-L$(LIBFT_DIR) -lft -lreadline

# Remove command
RM					=	rm -rf

# Source files
SRC_INPUT_CHECK		=	check_line.c \
						env_variables.c \
						exit_status.c \
						quotes.c \
						redirections_space.c

SRC_PARSE_LINE		=	cmd_data.c \
						handle_commands.c \
						handle_input.c \
						handle_output.c \
						init_2.c \
						parse_line.c

SRC 				=	$(addprefix $(INPUT_CHECK_DIR)/, $(SRC_INPUT_CHECK)) \
						$(addprefix $(PARSE_LINE_DIR)/, $(SRC_PARSE_LINE)) \
						clean_up_loop.c \
						clean_up.c \
						env.c \
						err_msg.c \
						init.c \
						main.c

# Object files
OBJ					=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Compile individual source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
all: $(NAME)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) --quiet clean
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)✔️ clean $(NAME)$(RESET)"

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) --quiet fclean
	@$(RM) $(NAME)
	@echo "$(RED)✔️ fclean $(NAME)$(RESET)"

re: fclean all

# Target rules
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)✔️ $(NAME) created$(RESET)"

# Create directories for object files
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(INPUT_CHECK_DIR)
	@mkdir -p $(OBJ_DIR)/$(PARSE_LINE_DIR)

# Library compilation
$(LIBFT): $(LIBFT_DIR)
	@echo "$(YELLOW)compiling...$(RESET)"
	@cd $(LIBFT_DIR) && $(MAKE) --quiet
	@echo "$(GREEN)✔️ libft created$(RESET)"

.PHONY: all clean fclean re
