NAME = libft.a
# mandatory
SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strduparr.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_tolower.c ft_toupper.c \
	get_next_line.c get_next_line_utils.c ft_hex.c ft_strcmp.c ft_strutils.c ft_lstget.c \
	ft_atoi_parse.c ft_lstget.c ft_min.c ft_max.c ft_ternary.c ft_split_set.c ft_array.c ft_array2.c \
	ft_strstrip.c ft_strtok.c ft_arrlen.c ft_strncpy.c ft_isinset.c ft_addchar.c ft_isonly.c ft_strsplitset.c
# # ft_printf
# SRC += \
# 	../ft_printf/arg.c			\
# 	../ft_printf/ft_printf.c	\
# 	../ft_printf/ft_vprintf.c	\
# 	../ft_printf/put_int.c		\
# 	../ft_printf/put_misc.c	\
# 	../ft_printf/put_ptr.c		\
# 	../ft_printf/putarg.c		\
# 	../ft_printf/putfuncs.c

# SRC += \
# 	../ft_alloc/ft_malloc.c \
# 	../ft_alloc/ft_free.c

SRC += \
	../ft_destructor/ft_allocs.c \
	../ft_destructor/ft_destructors.c \
	../ft_destructor/ft_init.c \
	../ft_destructor/ft_utils.c

# bonus
SRC_BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c 
OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g -fPIE
# CFLAGS += -DDEBUG_ALLOCS=1
# CFLAGS += -fsanitize=address -fno-omit-frame-pointer
#CFLAGS += -Wno-unused-value -Wno-unused-result

# TODO: Temporary fix for gcc compilation
ifeq ($(CC),gcc)
	CFLAGS += -Wno-unused-value
endif

all: bonus

$(NAME): $(OBJS)
	$(AR) rcs $@ $?

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) rcs $(NAME) $?

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: clean fclean re bonus
