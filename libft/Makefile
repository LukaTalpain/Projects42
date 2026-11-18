# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/18 10:33:58 by ltalpain          #+#    #+#              #
#    Updated: 2026/11/18 10:34:04 by ltalpain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD

SOURCES = ft_atoi.c ft_lstadd_back.c ft_memchr.c ft_split.c ft_strncmp.c\
		ft_bzero.c ft_lstadd_front.c ft_memcmp.c ft_strchr.c ft_strnstr.c\
		ft_calloc.c   ft_lstclear.c ft_memcpy.c ft_strdup.c ft_strrchr.c\
		ft_isalnum.c ft_lstdelone.c ft_memmove.c ft_striteri.c ft_strtrim.c\
		ft_isalpha.c ft_lstiter.c ft_memset.c ft_strjoin.c ft_substr.c\
		ft_isascii.c ft_lstlast.c ft_putchar_fd.c  ft_strlcat.c ft_tolower.c\
		ft_isdigit.c ft_lstmap.c ft_putendl_fd.c ft_strlcpy.c ft_toupper.c\
		ft_isprint.c ft_lstnew.c ft_putnbr_fd.c ft_strlen.c ft_itoa.c\
		ft_lstsize.c ft_putstr_fd.c ft_strmapi.c

OBJECTS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

NAME = libft.a

HEADER = -I .

all: $(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rcs $@ $^

.PHONY: all clean fclean re

clean :
	rm -f $(OBJECTS) $(DEPS)

fclean : clean
	rm -f $(NAME)

-include $(DEPS)

re : fclean all
