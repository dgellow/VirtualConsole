CFLAGS = `sdl2-config --cflags` -g -std=c++14
CC = clang++

buildDir = `pwd`/build
sourceDir = `pwd`/src
dependencies = `sdl2-config --libs`

.DEFAULT_GOAL := game

game: build-directory
	$(CC) $(CFLAGS) \
	$(dependencies) \
        $(sourceDir)/Lexer.cpp \
        $(sourceDir)/Parser.cpp \
        $(sourceDir)/main.cpp \
	-o $(buildDir)/game

clean:
	rm -rf $(buildDir)/*

build-directory:
	@mkdir -p $(buildDir)

run: game
	$(buildDir)/game

debug: game
	lldb $(buildDir)/game

all: clean game

help:
	@echo "Available tasks (default is marked with *):"
	@echo "*all	equivalent to 'clean' then 'game'"
	@echo " clean	remove files and directories generated during compilation"
	@echo " game	compile the game"
	@echo " run	compile then run the game"
	@echo " debug	compile then launch a debugger (lldb)"
	@echo " help	show this help message"
	@echo ""
	@echo "Usage exemple:"
	@echo "To compile and run the game, be sure to be at the root of the project and execute the command \`make run\`."
