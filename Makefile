NAME = client

MAMES = server

SOURCES =	client.c\

SERVERS =	server.c\

OBJECTS = $(SOURCES:%.c=%.o)

SOBJECTS = $(SERVERS:%.c=%.o)

LIBFT	=	libft/libft.a
CC	=	cc
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./libft

LIBFT_FLAGS = -L ./libft -lft

all: LIBFT $(NAME)

LIBFT:
	make -C libft

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
NAME: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)

server: $(NAMES)

$(NAMES): $(SOBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)

clean:
	make clean -C libft
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re LIBFT
