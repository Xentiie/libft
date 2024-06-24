# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 09:55:54 by reclaire          #+#    #+#              #
#    Updated: 2024/06/20 00:21:11 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.so
include config.mk

#CFLAGS		+=	-Wall -Wextra -Werror -O3 -g
CFLAGS		+=	-g -DDEBUG -Wall -Wextra
INCLUDES  	+=	-I./ -I./srcs

$(NAME):	$(OBJS)
			$(MKLIB)
