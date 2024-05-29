PROG = main
PROG1 = mysql_func

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
WALL =`-Wall`
MYSQL1 =`mysql_config --cflags`
MYSQL2 = `mysql_config --libs`

${PROG}: ${PROG}.c
	${CC} ${WALL} ${CFLAGS} -o ${PROG} ${PROG1}.c ${PROG}.c ${LIBS} ${MYSQL1} ${MYSQL2} 

clean:
	rm ${PROG} ${PROG1}