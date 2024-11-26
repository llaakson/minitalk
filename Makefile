CLIENT = client

SERVER = server

NAME = $(CLIENT) $(SERVER) 

SOURCES =	client.c\

SERVERS =	server.c server_tools.c\

OBJECTS = $(SOURCES:%.c=%.o)

SOBJECTS = $(SERVERS:%.c=%.o)

LIBFT	=	libft/libft.a
CC	=	cc
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./libft

LIBFT_FLAGS = -L ./libft -lft

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(CLIENT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)

$(SERVER): $(SOBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)


clean:
	make clean -C libft
	rm -f $(OBJECTS) $(SOBJECTS)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re LIBFT
