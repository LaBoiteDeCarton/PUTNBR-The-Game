NAME = game42
H_DIR = includes
S_DIR = srcs
SRCS =  ${S_DIR}/ft_str.c ${S_DIR}/color_set.c ${S_DIR}/file.c ${S_DIR}/map.c ${S_DIR}/key_scan.c ${S_DIR}/wait.c ${S_DIR}/anim.c ${S_DIR}/menu.c ${S_DIR}/play.c ${S_DIR}/main.c
CC = gcc
FLAGS = -Wall -Wextra -Werror
HFLAGS = -I${H_DIR}
LIBFLAG = -lncurses
OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${FLAGS} ${HFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	${CC} ${FLAGS} ${HFLAGS} ${LIBFLAG} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

run: ${NAME}
	./${NAME}

re: fclean ${NAME}

.PHONY: clean fclean
