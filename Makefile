CFLAGS = -g -std=c++14
CC = clang++
dependencies =

buildDir = `pwd`/build
assemblerSourceDir = `pwd`/Assembler/src
CPUSourceDir = `pwd`/CPU/src
editorSourceDir = `pwd`/Editor/src

testDir = `pwd`/tests
assemblerTestDir = $testDir/Assembler
CPUTestDir = $testDir/CPU
editorTestDir = $testDir/Editor

editorAppName = editor.app

.DEFAULT_GOAL := help

samvirtassembler: build-directory
	$(CC) $(CFLAGS) \
	$(dependencies) \
        $(assemblerSourceDir)/Lexer.cpp \
        $(assemblerSourceDir)/Parser.cpp \
        $(assemblerSourceDir)/Compiler.cpp \
        $(assemblerSourceDir)/main.cpp \
	-o $(buildDir)/samvirtassembler

samvirtcpu: build-directory
	$(CC) $(CFLAGS) \
	$(dependencies) \
        $(CPUSourceDir)/RunFlags.cpp \
        $(CPUSourceDir)/Utils.cpp \
        $(CPUSourceDir)/Parser.cpp \
        $(CPUSourceDir)/Machine.cpp \
        $(CPUSourceDir)/CPU.cpp \
        $(CPUSourceDir)/Memory.cpp \
        $(CPUSourceDir)/RAM.cpp \
        $(CPUSourceDir)/main.cpp \
	-o $(buildDir)/samvirtcpu

samvirteditor: build-directory
	pushd $(editorSourceDir) && qmake && make && popd
	rm -rf $(buildDir)/$(editorAppName)
	mv $(editorSourceDir)/$(editorAppName) $(buildDir)/

clean:
	rm -rf $(buildDir)/*

build-directory:
	@mkdir -p $(buildDir)

run-assembler: samvirtassembler
	$(buildDir)/samvirtassembler

run-cpu: samvirtcpu
	$(buildDir)/samvirtcpu

run-editor: samvirteditor
	open $(buildDir)/editor.app

test-cpu: build-directory
	$(CC) $(CFLAGS) \
	$(dependencies) \
        $(CPUSourceDir)/RunFlags.cpp \
        $(CPUSourceDir)/Utils.cpp \
        $(CPUSourceDir)/Parser.cpp \
        $(CPUSourceDir)/Machine.cpp \
        $(CPUSourceDir)/CPU.cpp \
        $(CPUSourceDir)/Memory.cpp \
        $(CPUSourceDir)/RAM.cpp \
        $(CPUSourceDir)/tests.cpp \
	-o $(buildDir)/testcpu

debug-assembler: samvirtassembler
	lldb $(buildDir)/samvirtassembler

debug-cpu: samvirtcpu
	lldb $(buildDir)/samvirtcpu

format:
	find . \( -iname '*.cpp' -or -iname '*.hpp' \) -exec clang-format -style=file -i --verbose {} \;

all: clean samvirtassembler samvirtcpu samvirteditor

help:
	@echo ".—————————————————————————————————————."
	@echo "| Sam's Virtual Console: build system |"
	@echo "°—————————————————————————————————————°"
	@echo "Available tasks (default is marked with *):"
	@echo "*all			clean then build everything"
	@echo " clean			remove files and directories generated during compilation"
	@echo " samvirtassembler	compile samvirtassembler"
	@echo " samvirtcpu		compile samvirtcpu"
	@echo " samvirteditor		compile editor.app"
	@echo " run-assembler		compile then run the samvirtassembler"
	@echo " run-cpu 		compile then run the samvirtcpu"
	@echo " run-editor		compile then run editor.app"
	@echo " debug-assembler 	compile samvirtassembler then launch a debugger (lldb)"
	@echo " debug-cpu		compile samvirtcpu then launch a debugger (lldb)"
	@echo " format		format C++ source files"
	@echo " help			show this help message"
	@echo ""
