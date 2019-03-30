gol: gifenc.o lodepng.o game_configuration.o game_functions.o game_space_display.o game_space_management.o main.o
	./mdif.sh out
	gcc -o gol make-o/gifenc.o make-o/lodepng.o make-o/game_configuration.o make-o/game_functions.o make-o/game_space_display.o make-o/game_space_management.o make-o/main.o

gifenc.o: libs/gifenc/gifenc.c libs/gifenc/gifenc.h
	./mdif.sh make-o
	./mdif.sh out
	gcc -c libs/gifenc/gifenc.c -o make-o/gifenc.o

lodepng.o: libs/lodepng/lodepng.c libs/lodepng/lodepng.h
	./mdif.sh make-o
	./mdif.sh out
	gcc -c libs/lodepng/lodepng.c -o make-o/lodepng.o

game_configuration.o: src/game_configuration.c src/game_configuration.h
	./mdif.sh make-o
	./mdif.sh out
	gcc -c src/game_configuration.c -o make-o/game_configuration.o

game_functions.o: src/game_functions.c src/game_functions.h
	./mdif.sh make-o
	./mdif.sh out
	gcc -c src/game_functions.c -o make-o/game_functions.o

game_space_display.o: src/game_space_display.c src/game_space_display.h
	./mdif.sh make-o
	./mdif.sh out
	gcc -c src/game_space_display.c -o make-o/game_space_display.o

game_space_management.o: src/game_space_management.c src/game_space_management.h
	./mdif.sh make-o
	./mdif.sh out
	gcc -c src/game_space_management.c -o make-o/game_space_management.o

main.o: src/main.c
	./mdif.sh make-o
	./mdif.sh out
	gcc -c src/main.c -o make-o/main.o