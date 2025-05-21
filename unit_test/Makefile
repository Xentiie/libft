# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/18 15:45:48 by reclaire          #+#    #+#              #
#    Updated: 2025/05/19 17:41:38 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

CFLAGS+=-masm=intel

$(NAME): packages $(OBJS)
	gcc -o $(NAME) $(OBJS) $(LIBS_PATHS) $(LIBS)
