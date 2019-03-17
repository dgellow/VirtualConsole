buildDir = build
assemblerBuildDir = `pwd`/Assembler/$(buildDir)
cpuBuildDir = `pwd`/CPU/$(buildDir)
editorBuildDir = `pwd`/Editor/$(buildDir)

.DEFAULT_GOAL := help

virtualassembler: build-directories
	pushd $(assemblerBuildDir) && cmake .. && make && popd

virtualcpu: build-directories
	pushd $(cpuBuildDir) && cmake .. && make && make test ARGS="-V" && popd

virtualeditor: build-directories
	pushd $(editorBuildDir) && qmake .. && make && popd

clean:
	rm -rf $(assemblerBuildDir)/*
	rm -rf $(cpuBuildDir)/*
	rm -rf $(editorBuildDir)/*

build-directories:
	@mkdir -p $(assemblerBuildDir)
	@mkdir -p $(cpuBuildDir)
	@mkdir -p $(editorBuildDir)

run-assembler: virtualassembler
	$(assemblerBuildDir)/virtualassembler

run-cpu: virtualcpu
	$(cpuBuildDir)/virtualcpu

run-editor: virtualeditor
	open $(editorBuildDir)/VirtualEditor.app

debug-assembler: virtualassembler
	lldb $(assemblerBuildDir)/virtualassembler

debug-cpu: virtualcpu
	lldb $(cpuBuildDir)/virtualcpu

format:
	find . -not -path "*/\.*" -not -path "*/build/*" \( -iname '*.cpp' -or -iname '*.hpp' \) -exec clang-format -style=file -i --verbose {} \;

all: clean virtualassembler virtualcpu virtualeditor

help:
	@echo ".———————————————————————————————————————."
	@echo "| Sam's Virtual Console: build commands |"
	@echo "°———————————————————————————————————————°"
	@echo "Dependencies:"
	@echo " - cmake"
	@echo " - qmake (if building the editor)"
	@echo ""
	@echo "Available tasks (default is marked by *):"
	@echo "*all			clean then build everything"
	@echo " clean			remove files and directories generated during compilation"
	@echo " virtualassembler	compile the Virtual Assembler"
	@echo " virtualcpu		compile the Virtual CPU"
	@echo " virtualeditor		compile the Virtual Editor (GUI)"
	@echo " run-assembler		compile then run the Virtual Assembler"
	@echo " run-cpu 		compile then run the Virtual CPU"
	@echo " run-editor		compile then run the Virtual Editor"
	@echo " debug-assembler 	compile the Virtual Assembler then launch a debugger (lldb)"
	@echo " debug-cpu		compile the Virtual CPU then launch a debugger (lldb)"
	@echo " format			format C++ source files"
	@echo " help			show this help message"
	@echo ""
