SRC_FILES = mlvm.c
CC_FLAGS = -Wall -Wextra -g -std=c11
CC = clang

all: compile run

compile:
	${CC} ${SRC_FILES} ${CC_FLAGS} -o mlvm.out

run:
	./mlvm.out

.PHONY: compile run all
