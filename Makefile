NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src
INCDIR = inc
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCFILES = handle_errors.c \
			init_a_to_b.c \
			init_b_to_a.c \
			op_push.c \
			op_rev_rotate.c \
			op_rotate.c \
			op_swap.c \
			push_swap.c \
			sort_stack.c \
			sort_three.c \
			stack_init.c \
			stack_utils1.c \
			stack_utils2.c
			
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCDIR) $(LIBFT) -o $(NAME)

%.o: %.c $(INCDIR)/push_swap.h
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re