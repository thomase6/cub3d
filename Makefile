# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/16 10:05:37 by texenber          #+#    #+#              #
#    Updated: 2026/06/17 13:18:33 by texenber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

#ingredients

SRC			=	main.c			\
				utils/error_handle.c	\
				init/init_game.c	\
				init/minimap.c          \
				init/movement_player.c  \
				init/raycasting.c       \
				init/make_player.c      \
				init/game_rules.c       \
				init/update_helper.c    \
				init/update_player.c   	\
				parser/parser.c	
SRCS		=	$(addprefix $(PRE), $(SRC))
PRE			=	./src/
HEAD		=	./inc/ ./inc/libft/src/
CC			=	cc
WARN		=	-Wall -Werror -Wextra
DFLAGS		=	-g
LIBS		=	-lmlx -lXext -lm
ifeq ($(NOWARN), 1)
	WARN 	=
endif
CFLAGS		= 	$(WARN)
LIBFT_DIR 	= 	inc/libft
LIBFT 		= 	cd $(LIBFT_DIR)
ODIR		= 	obj/
OBJS		= 	$(SRCS:$(PRE)%.c=$(ODIR)%.o)

#utensils

RM			=	rm -f
MAKEFLAGS	+=	--no-print-directory
DIR_DUP		=	mkdir -p $(@D)

#recipe

all:		$(NAME)

$(ODIR)%.o:	$(PRE)%.c
			@$(DIR_DUP)
			@$(CC) $(CFLAGS) -c $(addprefix -I, $(HEAD)) $< -o $@

$(NAME):	$(OBJS)
			@($(LIBFT) && $(MAKE) all)
			@$(CC) $(CFLAGS) $(addprefix -I, $(HEAD)) $(OBJS) $(LIBS) -o $(NAME) $(LIBFT_DIR)/libft.a

clean:
			@($(LIBFT) && $(MAKE) clean)
			@$(RM) $(OBJS)
			@rm -rf $(ODIR)

fclean:		clean
			@($(LIBFT) && $(MAKE) fclean)
			@$(RM) $(NAME)

debug:		
			@$(MAKE) CFLAGS="$(CFLAGS) $(DFLAGS)" re

re:			fclean all clean

.PHONY:		all clean fclean debug re
