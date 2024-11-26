# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2024/11/26 02:47:18 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

dyn: $(OBJS)
	$(CC) -shared -fPIC $(CFLAGS) -o my_library.so my_library.c

test:
	$(CC) -DFT_OS_LINUX -fprofile-generate -fprofile-arcs -ftest-coverage -I./ ./test.c -L./ -lft -o test