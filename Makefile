# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 04:08:31 by sarazicchie       #+#    #+#              #
#    Updated: 2023/02/22 07:14:14 by aliburdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

HEADER		=	./includes/

LIBFT		=	libft/libft.a

LIBS		=	-lreadline

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) #-fsanitize=address

SRCS		=	minishell.c

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LIBS)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all

# NAME			= minishell

# SRCS			=	minishell.c get_next_line.c get_next_line_utils.c
					

# OBJS			= $(SRCS:.c=.o)

# INCLUDES		= minishell.h

# CC				= gcc
# RM				= rm -f
# CFLAGS			= -Wall -Wextra -Werror -I.


# all:			$(NAME)

# %.o	: %.c
# 		$(CC) $(CFLAGS) -c $(SRCS)

# $(NAME):		$(OBJS) $(INCLUDES)
# 				$(MAKE) -C libft
# 				cp libft/libft.a .
# 				mv libft.a $(NAME)
# 				$(NAME) $(OBJS)

# clean:
# 				make clean -C libft
# 				$(RM) $(OBJS)

# fclean:			clean
# 				make fclean -C libft
# 				$(RM) $(NAME) libft.a

# re:				fclean all

# .PHONY:			all clean fclean re