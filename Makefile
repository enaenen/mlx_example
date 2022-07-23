all:
	gcc -g -Lmlx -lmlx -framework OpenGL -framework AppKit main.c
	./a.out
