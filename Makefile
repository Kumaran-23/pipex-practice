NAME		= pipex
INC			= inc
HEADER		= -I inc
LIBFT		= libft
SRC_DIR		= src/
OBJ		= $(SRC:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g 
LEAKS	= -fsanitize=address -g3
RM			= rm -f

GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
WHITE		=	\033[0;97m

MAN_DIR		=	mandatory/
MAN_FILES	=	pipex_utils pipex

SRC_FILES	=	$(addprefix $(MAN_DIR), $(MAN_FILES))

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

start:
			@echo "$(YELLOW)Start Make:$(WHITE)"
			@make all

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@$(CC) $(CFLAGS) $(LEAKS) $(OBJ) $(HEADER) libft.a -o $(NAME)
			@echo "$(GREEN)pipex Done!$(WHITE)"

%.o: %.c
			@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
			@$(RM) $(OBJ)
			@make clean -C $(LIBFT)
			@echo "$(BLUE)pipex: object files have been cleaned!$(WHITE)"

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) libft.a
			@$(RM) $(LIBFT)/libft.a
			@echo "$(BLUE)Libft: files have been cleaned!$(WHITE)"
			@echo "$(BLUE)pipex: files have been cleaned!$(WHITE)"


re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for pipex\n$(WHITE)"


.PHONY:		all clean fclean re norm