FILES=get_next_line.c get_next_line_utils.c main.c
OBJECTS=$(FILES:.c=.o)
PROGRAM=gnl
FLAGS=-Werror -Wall -Wextra

all:	$(PROGRAM)

$(PROGRAM):	$(FILES)
			gcc $(FLAGS) $(FILES) -D BUFFER_SIZE=32 -o $(PROGRAM)
	
clean:
		rm -rf $(OBJECTS)

fclean: clean
		rm -rf $(PROGRAM)
