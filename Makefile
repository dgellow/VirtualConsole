CFLAGS = -g -std=c++14
CC = clang++

buildDir = `pwd`/build
sourceDir = `pwd`/src
dependencies =

.DEFAULT_GOAL := samvirtcons

samvirtcons: build-directory
	$(CC) $(CFLAGS) \
	$(dependencies) \
        $(sourceDir)/Lexer.cpp \
        $(sourceDir)/Parser.cpp \
        $(sourceDir)/Compiler.cpp \
        $(sourceDir)/main.cpp \
	-o $(buildDir)/samvirtcons

clean:
	rm -rf $(buildDir)/*

build-directory:
	@mkdir -p $(buildDir)

run: samvirtcons
	$(buildDir)/samvirtcons

debug: samvirtcons
	lldb $(buildDir)/samvirtcons

all: clean samvirtcons

help:
	@echo "Available tasks (default is marked with *):"
	@echo "*all		equivalent to 'clean' then 'samvirtcons'"
	@echo " clean		remove files and directories generated during compilation"
	@echo " samvirtcons	compile samvirtcons"
	@echo " run		compile then run the samvirtcons"
	@echo " debug		compile then launch a debugger (lldb)"
	@echo " help		show this help message"
	@echo ""
	@echo "Usage exemple:"
	@echo "To compile and run samvirtcons, be sure to be at the root of the project and execute the command \`make run\`."
