# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 14:22:44 by llaakson          #+#    #+#              #
#    Updated: 2024/08/09 16:47:12 by llaakson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES =	ft_strlen.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_strlcpy.c \
			ft_strdup.c \
			ft_bzero.c \
			ft_memset.c \
			ft_calloc.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_memcpy.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strtrim.c \
			ft_memmove.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_split.c get_next_line.c get_next_line_utils.c ft_print_address.c ft_printf.c ft_printf_helper.c \

BONUS	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		  
HEADF	=	libft.h

OBJECTS = $(SOURCES:%.c=%.o)

OBJECTSBONUS = $(BONUS:%.c=%.o)

CC	=	cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o:	%.c	$(HEADF)
	$(CC)	$(CFLAGS)	-c	$<	-o	$@

$(NAME): $(OBJECTS)
	ar	-rcs	$(NAME) $(OBJECTS)

bonus: .bonus

.bonus: $(OBJECTS) $(OBJECTSBONUS)
	ar	-rcs $(NAME) $(OBJECTS)	$(OBJECTSBONUS)
	@touch .bonus

clean:
	rm -f $(OBJECTS) $(OBJECTSBONUS)

fclean: clean
	rm -f $(NAME)	.bonus

re: fclean all

.PHONY: all clean fclean re bonus
