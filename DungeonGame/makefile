#Tristen Miller
all: rpg

rpg: Player.o Game.o main.o
	gcc -Wall Player.c Game.c main.c -o rpg

player_test: player_test.c Player.o
	gcc -Wall player_test.c Player.o -o player_test

Player.o: Player.c UNIXBOARD.h Player.h
	gcc -Wall -c Player.c

Game.o: Game.c UNIXBOARD.h Game.h Player.h
	gcc -Wall -c Game.c

main.o: main.c UNIXBOARD.h Game.h
	gcc -Wall -c main.c


clean:
	rm -f *.o
	rm -f rpg
	rm -f player_test