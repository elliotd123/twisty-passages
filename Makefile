all:
	g++ *.h *.cpp -o twisty -lncurses

install:
	cp twisty /usr/local/bin

uninstall:
	rm /usr/local/bin/twisty
