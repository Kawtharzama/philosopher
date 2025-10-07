# Only include each .c file once
SRCS = \
	srcs/main.c \
	srcs/init.c	\
	srcs/check_args.c \
	srcs/free.c  \
	srcs/philo.c  \
	srcs/utils.c  \
	srcs/utils2.c  \
	srcs/monitor_philo.c \

# Convert srcs/ to objs/
OBJS = $(SRCS:srcs/%.c=objs/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Wuninitialized -g
INCLUDES = -I./includes 

NAME = philo

all: $(NAME)



$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

# Make sure to create obj dirs as needed
objs/%.o: srcs/%.c includes/philo.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf objs
	

fclean: clean
	rm -f $(NAME)
	

re: fclean all

.PHONY: all clean fclean re
