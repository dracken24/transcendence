# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 13:22:35 by nadesjar          #+#    #+#              #
#    Updated: 2023/04/19 15:56:44 by nadesjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS_T 		= ./objs/

P_SRCS_T		= ./srcs/

INCLUDE_PATH	= ./includes/

FILES_T			= 

OBJS_T			= $(patsubst $(P_SRCS_T)%.cpp, $(P_OBJS_T)%.o, $(FILES_T))

CC				= c++

CFLAGS			= 

NAME			= Transcendence

# ------------------------------- Compilation -------------------------------- #

all: signat msg_in $(NAME) msg_out

$(NAME): $(OBJS_T)
	@$(CC) $(OBJS_T) $(CFLAGS) -o $(NAME)

# --------------------------- Recompilation Headers --------------------------- #



# ----------------------------------- Git ------------------------------------ #

COMMIT = $(shell date "+%d %B %T")
git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push

# --------------------------------- Messages --------------------------------- #

msg_in:
	@echo $L"COMPILATION DE ft_Transcendence EN COURS..."$W

msg_out:
	@echo $L"\nft_Transcendence READY !!!\n"$W

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

re: fclean all


.PHONY: all msg_in msg_out clean fclean re signat
