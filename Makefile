# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 13:22:35 by nadesjar          #+#    #+#              #
#    Updated: 2023/04/19 13:20:22 by nadesjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS_T 		= ./objs/
P_OBJS_O 		= ./objs/others/

P_SRCS_T		= ./srcs/
P_SRCS_O		= ./srcs/others/

INCLUDE_PATH	= ./includes/

FILES_T			= $(P_SRCS_T)main.cpp 

FILES_O			= $(P_SRCS_O)logger.cpp $(P_SRCS_O)trsMemory.cpp

OBJS_T			= $(patsubst $(P_SRCS_T)%.cpp, $(P_OBJS_T)%.o, $(FILES_T))
OBJS_O			= $(patsubst $(P_SRCS_O)%.cpp, $(P_OBJS_O)%.o, $(FILES_O))

CC				= c++

CFLAGS			= -Wno-unused-parameter -Wno-unused-variable -std=c++98

NAME			= Transcendence

# ------------------------------- Compilation -------------------------------- #

all: signat msg_in $(NAME) msg_out

$(NAME): $(OBJS_T) $(OBJS_O)
	@$(CC) $(OBJS_T) $(OBJS_O) $(CFLAGS) -o $(NAME)

# --------------------------- Recompilation Headers --------------------------- #

$(P_OBJS_T)main.o: $(P_SRCS_T)main.cpp 
	@mkdir -p $(P_OBJS_T)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$G■"

$(P_OBJS_O)trsMemory.o: $(P_SRCS_O)trsMemory.cpp
	@mkdir -p $(P_OBJS_O)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$Y■"

$(P_OBJS_O)logger.o: $(P_SRCS_O)logger.cpp
	@mkdir -p $(P_OBJS_O)
	@$(CC) -I $(CFLAGS) -c $< -o $@
	@printf "$Y■"

# ----------------------------------- Git ------------------------------------ #

COMMIT = $(shell date "+%d %B %T")
git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push

# --------------------------------- Messages --------------------------------- #

msg_in:
	@echo $L"COMPILATION DE ft_irc EN COURS..."$W

msg_out:
	@echo $L"\nft_irc READY !!!\n"$W

signat:
	@echo "$G\n\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/"
	@echo " |           -------------------------------------------------             |"
	@echo " |           *--* $LPROJET:  ft_Transcendence PAR: NADESJAR$G *--*             |"
	@echo " |           -------------------------------------------------             |"
	@echo "/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\ \n$W"
	
# ---------------------------------- Colors ---------------------------------- #

R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
Y   = $(shell tput -Txterm setaf 3)
L	= $(shell tput -Txterm setaf 5)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)

# ---------------------------------- Clean ----------------------------------- #

clean:	
	@rm -fr $(P_OBJS_S) $(P_OBJS_C)

fclean: clean
	@echo $G"                                    BYE BYE !!!"$W
	@rm -f $(NAME)
	@rm -fr objs

re: fclean all


.PHONY: all msg_in msg_out clean fclean re signat
