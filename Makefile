# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguinea <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 10:28:53 by aguinea           #+#    #+#              #
#    Updated: 2025/02/23 23:57:14 by aguinea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                 COLOR CODE                                   #
################################################################################

BOLD			= \033[1m

END         	= \e[0m

DEF_COLOR   	= \033[0;39m

ORANGE    		= \033[38;5;214m

PINK      		= \033[38;5;213m

BLUE      		= \033[0;94m

YELLOW    		= \033[0;93m

BOLD_YELLOW 	= \033[1;33m

WHITE 			= \033[0;97m

ITALIC 			= \033[3m

GREEN 			= \033[0;92m

################################################################################
#                             COMPILATION & MORE                               #
################################################################################

NAME 			= philo

CC 				= cc
CFLAGS 			= -Wall -Werror -Wextra #-g -pthread -fsanitize=address

MAKE_LIB 		= ar -rcs

RM 				= rm -f


################################################################################
#                                 PATH/TO/SRCS                                 #
################################################################################

SRC_DIR 		= ./mandatory/src

OBJ_DIR 		= ./mandatory/obj

HEADER_DIR 		= ./mandatory/header


################################################################################
#                               SRCS && OBJS                                   #
################################################################################

HEADER			= $(HEADER_DIR)/philo.h

SRCS 			= $(SRC_DIR)/main.c						\
				  $(SRC_DIR)/parsing.c					\
				  $(SRC_DIR)/prints.c					\
				  $(SRC_DIR)/utils.c					\
				  $(SRC_DIR)/exit.c						\
				  $(SRC_DIR)/monitor.c					\
				  $(SRC_DIR)/simulation.c 


OBJS 			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))


################################################################################
#                                 MAKEFILE                                     #
################################################################################

all					: $(NAME)


$(NAME)				: $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
					@echo "\n$(PINK)[ＯＫ✔]		➤➤		$(GREEN)executable created$(DEF_COLOR)\n"

$(OBJ_DIR)			:
					@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o		: $(SRC_DIR)/%.c $(HEADER) Makefile | $(OBJ_DIR)
					@$(CC) $(CFLAGS) -c $< -o $@
					@echo "\n$(PINK)[ＯＫ✔]		➤➤		$(GREEN)Compiled $< into $@$(DEF_COLOR)\n"

clean				:
					@rm -rf $(OBJ_DIR)
					@echo "\n$(PINK)[ＯＫ✔]		➤➤		$(GREEN)Cleaned up object$(DEF_COLOR)\n"

fclean				: clean
					@rm -f $(NAME)
					@echo "\n$(PINK)[ＯＫ✔]		➤➤		$(GREEN)All executables and objects removed$(DEF_COLOR)\n"

re					: fclean all

.PHONY: all clean fclean re
