all:
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit main.c -o mlxtest
