ventana: buscador.c
	gcc -g -c buscador.c -lpthread
	gcc -g buscador.o -o buscador -lpthread