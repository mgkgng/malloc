HOSTTYPE := $(shell uname -m)_$(shell uname -s)

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

BUILD_DIR := build
NAME := $(BUILD_DIR)/libft_malloc_$(HOSTTYPE).so
CC := gcc
CFLAGS := -Wall -Wextra -Werror
SRCS := src/allocate.c src/manage_block.c src/manage_zone.c src/libft.c src/display.c src/manage_mem.c src/allocate_helper.c src/initialize.c
TEST_FILES := $(wildcard tests/test*.c)
TEST_EXEC_NAMES := $(patsubst tests/test%.c, $(BUILD_DIR)/test%, $(TEST_FILES))

INCLUDE := -I include/
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
LIBS := -L$(BUILD_DIR) -lft_malloc_$(HOSTTYPE) -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) $(LIBS)

test: $(TEST_EXEC_NAMES)

$(BUILD_DIR)/test%: tests/test%.c $(NAME)
	$(CC) $(INCLUDE) -o $@ $< $(LIBS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
