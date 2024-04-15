# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2024/04/11 18:50:10 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

TEST_NAME	=	run_tests
SRCS_TEST   =   $(shell find ./tests -type f -name '*.c')
OBJS_TEST	=	${SRCS_TEST:.c=.o}

NAME		=	libft.a
SRCS    	=   $(shell find . -type f -name '*.c' -not -path "*./tests*" -not -path "*./old*")
OBJS		=	${SRCS:.c=.o}

CFLAGS		=	-Wall -Wextra -Werror -O3

WSLENV ?= notwsl
ifndef WSLENV
	CFLAGS += -D WIN32
	CC := x86_64-w64-mingw32-gcc
	LINK := ar -rcs $(NAME)

	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
	    CFLAGS += -D AMD64
	else
	    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	        CFLAGS += -D AMD64
	    endif
	    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	        CFLAGS += -D IA32
	    endif
	endif
else
	ifeq ($(OS),Windows_NT)
	    CFLAGS += -D WIN32
		CC := x86_64-w64-mingw32-gcc
		LINK := ar -rcs $(NAME)

	    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
	        CFLAGS += -D AMD64
	    else
	        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	            CFLAGS += -D AMD64
	        endif
	        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	            CFLAGS += -D IA32
	        endif
	    endif
	else
	    UNAME_S := $(shell uname -s)
		CC := gcc
		LINK := ar -rcs $(NAME)

	    ifeq ($(UNAME_S),Linux)
	        CFLAGS += -D LINUX
	    endif
	    ifeq ($(UNAME_S),Darwin)
	        CFLAGS += -D OSX
	    endif
	    UNAME_P := $(shell uname -p)
	    ifeq ($(UNAME_P),x86_64)
	        CFLAGS += -D AMD64
	    endif
	    ifneq ($(filter %86,$(UNAME_P)),)
	        CFLAGS += -D IA32
	    endif
	    ifneq ($(filter arm%,$(UNAME_P)),)
	        CFLAGS += -D ARM
	    endif
	endif
endif

RM			=	rm -f
INCLUDES  	=	-I./ -I./srcs

%.o: %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			$(LINK) $(OBJS)
				
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