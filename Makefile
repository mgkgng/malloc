HOSTTYPE := $(shell uname -m)_$(shell uname -s)

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRCS=src/allocate.c src/manage_block.c src/manage_zone.c src/libft.c src/display.c src/manage_mem.c src/allocate_helper.c src/initialize.c
TEST=tests/test5.c
TEST_OBJ=$(TEST:.c=.o)
MALLOC_TEST=malloc_test
INCLUDE=-I include/
OBJS=$(SRCS:.c=.o)
LIBS=-lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) $(LIBS)

test: $(NAME) $(TEST_OBJ)
	$(CC) $(INCLUDE) -o $(MALLOC_TEST) $(TEST_OBJ) $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(INCLUDE) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(MALLOC_TEST)

re: fclean all

.PHONY: all clean fclean re
