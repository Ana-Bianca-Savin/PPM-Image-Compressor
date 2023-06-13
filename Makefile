build:
	gcc -std=c99 -Wall -o quadtree main.c functiiImgArbori.c functiiCerinte.c
run:
	./quadtree
clean:
	rm quadtree
