# Makefile for minishell

# Executable name
NAME = minishell

# Source directories
SRC_DIR = ./src

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft_full.a

# Headers
INCLUDE = ./include
HEADERS = $(INCLUDE)/minishell.h

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE) -I$(LIBFT_DIR) 
LFLAGS = -L$(LIBFT_DIR) -lft_full -lreadline

# Remove command
RM = rm -f

# Source files
SRC = main.c

# Object files
OBJ = $(SRC:%.c=$(SRC_DIR)/%.o)

# Compile individual source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

# Phony Targets
all: $(NAME)

clean:
	@cd $(LIBFT_DIR) && $(MAKE) --quiet clean
	@$(RM) $(OBJ)
	@echo "✅ clean done"

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) --quiet fclean
	@$(RM) $(NAME)
	@echo "✅ fclean done"

re: fclean all

# Target Rules
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "✅ $(NAME) created"

# Library Compilation
$(LIBFT): $(LIBFT_DIR)
	@cd $(LIBFT_DIR) && $(MAKE) --quiet full
	@echo "✅ libft library built"

.PHONY: all clean fclean re