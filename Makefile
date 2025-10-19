CC			= gcc
BUFFER_SIZE	?= 32
CFLAGS		?= -Wall -Wextra -Werror
CFLAGS		+= -Iinclude -D BUFFER_SIZE=$(BUFFER_SIZE)

SRC_DIR		= src
TEST_DIR	= tests

SRCS		= $(SRC_DIR)/get_next_line.c \
			  $(SRC_DIR)/get_next_line_utils.c

TEST_MAIN	= $(TEST_DIR)/test_main.c
TEST_BIN	= gnl

UNIT_TEST_SRC	= $(TEST_DIR)/test_get_next_line.c
UNIT_TEST_BIN	= $(TEST_DIR)/gnl_tests

VALGRIND	?= valgrind
VALGRIND_FLAGS	?= --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1

ifdef DEBUG
CFLAGS += -g
endif

.PHONY: all clean fclean re test valgrind-test

all: $(TEST_BIN)

$(TEST_BIN): $(SRCS) $(TEST_MAIN)
	$(CC) $(CFLAGS) $(SRCS) $(TEST_MAIN) -o $@

$(UNIT_TEST_BIN): $(SRCS) $(UNIT_TEST_SRC)
	$(CC) $(CFLAGS) $(SRCS) $(UNIT_TEST_SRC) -o $@

test: $(UNIT_TEST_BIN)
	./$(UNIT_TEST_BIN)

valgrind-test: $(UNIT_TEST_BIN)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(UNIT_TEST_BIN)

clean:
	rm -f $(UNIT_TEST_BIN)

fclean: clean
	rm -f $(TEST_BIN)

re: fclean all
