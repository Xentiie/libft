# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2023/10/11 19:28:34 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

TEST_NAME	=	run_tests
SRCS_TEST   =   $(shell find ./tests -type f -name '*.c')
OBJS_TEST	=	${SRCS_TEST:.c=.o}

NAME	=	libft.a
SRCS    =   $(shell find . -type f -name '*.c' -not -path "*./tests*" -not -path "*./old*")
OBJS		=	${SRCS:.c=.o}

CC			=	gcc
RM			=	rm -f

INCLUDES  	=	-I./ -I./ft_printf
CFLAGS		:=	-Wall -Wextra -Werror -Wno-unused-variable -Wno-pointer-sign -Wno-discarded-qualifiers -Wno-ignored-qualifiers -O3
ifdef MOREFLAGS
CFLAGS		:=	$(CFLAGS) $(MOREFLAGS)
endif
ifeq ($(filter tests, $(MAKECMDGOALS)), tests) || ($(filter tests_re, $(MAKECMDGOALS)), tests_re)
CFLAGS		:=	$(CFLAGS) -D FT_MEMCHECK
endif



%.o: %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS)
				
all:		$(NAME)

tests_re:	re tests

tests:		$(NAME) $(OBJS_TEST)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_TEST) -L./ -lft -lm -lbacktrace -o $(TEST_NAME)


clean:
			find . -name "*.o" -print -exec $(RM) {} \;

tests_clean:
			$(RM) $(OBJS_TEST)

fclean:		clean
			$(RM) $(NAME)

tests_fclean:	tests_clean
			$(RM) $(TEST_NAME)

re:			fclean all clean

tests_re:	re tests_fclean tests

.PHONY:		all tests  clean tests_clean fclean tests_fclean re tests_re