# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ****** <******@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 12:41:37 by ******            #+#    #+#              #
#    Updated: 2024/05/30 17:18:02 by ******          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
SRC = builtins/_handler.c builtins/_options.c builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c \
builtins/unset.c utils/cwd.c utils/error.c utils/exit_status.c utils/ft_close.c utils/ft_stderr.c utils/history.c \
utils/hostname.c utils/prompt.c utils/signals.c exec/ast.c exec/ast_pipe.c exec/ast_print.c exec/ast_utils.c exec/cmd.c exec/cmd_utils.c \
exec/redirect.c exec/wildcards.c main.c parse/input/cont.c parse/input/get.c parse/input/shortcuts.c parse/input/types.c parse/parse.c \
parse/parse_descent.c parse/symbols.c parse/tokenize/print.c parse/tokenize/rules1.c parse/tokenize/rules2.c parse/tokenize/rules3.c \
parse/tokenize/tokenize.c shell/destroy.c shell/heredoc.c shell/init.c shell/run.c variables/add.c variables/envp.c variables/expand.c \
variables/expand_extra.c variables/expand_utils.c variables/get.c variables/print.c variables/remove.c variables/verify.c wlist/add.c \
wlist/extra.c wlist/remove.c wlist/update.c wlist/utils.c
SRC := $(patsubst %.c, $(SRC_DIR)/%.c, $(SRC))

# Compiler and Flags
CC = cc
CPP = clang++
# INC += -I/goinfre/$(USER)/.brew/opt/readline/include
CPPFLAGS = -Wall -Wextra -Werror
CPPFLAGS += -g -fPIE
CPPFLAGS += -I$(LIBFT_DIR) -Iincludes/
#CPPFLAGS += -DDEBUG=1
# CPPFLAGS += -DFORCE_TTY=0

# MacOS flags
# CPPFLAGS += -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
# CPPFLAGS += -fsanitize=address -fno-omit-frame-pointer

LIBFT_DIR = ./includes/libft/
LIBFT = $(LIBFT_DIR)/libft.a
LDLIBS = -L$(LIBFT_DIR)
# LDLIBS += -L/goinfre/$(USER)/.brew/opt/readline/lib
LDLIBS += -lft -lreadline

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_TEST = $(filter-out $(OBJ_DIR)/main.o,$(OBJ))

all: $(NAME)

run: all
	./$(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LREADLINE) $(OBJ) -o $(NAME) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR) 

fclean: clean
	rm -f $(NAME) 
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean
	$(MAKE) all

# ===== Utils =====
v: $(NAME)
	valgrind --leak-check=full ./$(NAME)

vf: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

# ===== Tests =====
TEST_DIR = tests
TEST_REPO = git@github.com:triedel42/minishell-tests
TEST = $(TEST_DIR)/test
LIBGTEST_DIR = googletest
LIBGTEST = $(LIBGTEST_DIR)/build/lib/libgtest.a
CXX = c++
CXXFLAGS = -std=c++14
CXXFLAGS += -I$(LIBGTEST_DIR)/googletest/include
CXXFLAGS += -Wno-write-strings
LDLIBS += -L$(LIBGTEST_DIR)/build/lib

t: $(TEST)
	./$(TEST)

$(TEST): $(TEST_DIR) $(OBJ_TEST) $(LIBGTEST)
	$(CXX) -o $@ $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(wildcard tests/*.cc) $(OBJ_TEST) $(LDLIBS) -lgtest

$(TEST_DIR):
	git clone $(TEST_REPO) $(TEST_DIR)

$(LIBGTEST_DIR):
	git clone --depth=1 https://github.com/google/googletest $@

$(LIBGTEST): $(LIBGTEST_DIR)
	cd $< && mkdir -p build && cd build && cmake ..
	make -j$(shell nproc) -C$(LIBGTEST_DIR)/build

.PHONY: all clean fclean re run t v vf
