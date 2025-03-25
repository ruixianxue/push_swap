# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc

# Library Name
NAME = libft.a

# Source Files
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
       ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
       ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
       ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c \
       ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
       ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_printf/ft_print_char.c \
       ft_printf/ft_print_hex.c \
       ft_printf/ft_print_nbr.c \
       ft_printf/ft_print_percent.c \
       ft_printf/ft_print_ptr.c \
       ft_printf/ft_print_str.c \
       ft_printf/ft_print_unsigned.c \
       ft_printf/ft_printf.c

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
             ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
             ft_lstiter.c ft_lstmap.c

# Object Files
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Rule to create the library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Compilation Rule for .c -> .o (Keeps .o files in the correct subdirectories)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Bonus rule
bonus: $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

# Standard Targets
all: $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus