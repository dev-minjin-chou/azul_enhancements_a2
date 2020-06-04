default: all

all: azul

clean:
	rm -f azul log.txt *.o *.dSYM

azul: main.o Controller.o Menu.o UserPrompt.o GameCommand.o Game.o Mosaic.o BoxLid.o TileBag.o Player.o TileFactory.o Tile.o TileLinkedList.o GameLoader.o GameSaver.o 
	g++ -Wall -Werror -Werror=sign-compare -std=c++14 -g -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -Werror=sign-compare -std=c++14 -g -c $^
