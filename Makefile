SRCS			=	init.c\
					main.c\
					utils.c\
					execute.c\

SRCSBONUS		=	init_bonus.c \
					utils_bonus.c \
					main_bonus.c\
					execute_bonus.c\

OBJS			=	$(SRCS:.c=.o)

OBJSBONUS		=	${SRCSBONUS:.c=.o}

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g3

NAME			=	pipex
NAME_BONUS		=	pipex_bonus

LIBRARIES		=	-L libftprintfgnl -lftprintfgnl
INCLUDES		=	-Ilibftprintfgnl

all:			$(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(INCLUDES) -g3 -I/usr/include -O3 -c $< -o $@

$(NAME):		$(OBJS)
				make -C libftprintfgnl
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARIES)

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(OBJSBONUS)
				make -C libftprintfgnl
				$(CC) $(CFLAGS) $(OBJSBONUS) -o $(NAME_BONUS) $(LIBRARIES)
clean:
				make -C libftprintfgnl clean
				$(RM) $(OBJS) $(OBJSBONUS) outfile


fclean:			clean
				make -C libftprintfgnl fclean
				$(RM) $(NAME) $(NAME_BONUS)


re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus norme
