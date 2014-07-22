all:
	g++ *.h *.cpp -o twisty -lncurses -O3

install:
	cp twisty /usr/local/bin

uninstall:
	rm /usr/local/bin/twisty
