HOSTTYPE := $(shell uname -m)_$(shell uname -s)

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
SYMLINK=libft_malloc.so
CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRCS=src/malloc.c src/free.c src/realloc.c src/manager.c
INCLUDE=-I include/
OBJS=$(SRCS:.c=.o)
LIBS=-lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(LIBS)
	ln -sf $(NAME) $(SYMLINK)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(SYMLINK)

re: fclean all

.PHONY: all clean fclean re
