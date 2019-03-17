buildDir = build
assemblerBuildDir = `pwd`/Assembler/$(buildDir)
cpuBuildDir = `pwd`/CPU/$(buildDir)
editorBuildDir = `pwd`/Editor/$(buildDir)

.DEFAULT_GOAL := help

virtualassembler: build-directories
	pushd $(assemblerBuildDir) && cmake -DCMAKE_BUILD_TYPE=Release .. && make && popd

virtualcpu: build-directories
	pushd $(cpuBuildDir) && cmake -DCMAKE_BUILD_TYPE=Release .. && make && popd

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

test-assembler: virtualassembler
	pushd $(assemblerBuildDir) && make test ARGS="-V" && popd

test-cpu: virtualcpu
	pushd $(cpuBuildDir) && make test ARGS="-V" && popd

run-assembler: virtualassembler
	$(assemblerBuildDir)/virtualassembler

run-cpu: virtualcpu
	$(cpuBuildDir)/virtualcpu

run-editor: virtualeditor
	open $(editorBuildDir)/VirtualEditor.app

build-debug-assembler: build-directories
	pushd $(assemblerBuildDir) && cmake -DCMAKE_BUILD_TYPE=Debug .. && make && popd

build-debug-cpu: build-directories
	pushd $(cpuBuildDir) && cmake -DCMAKE_BUILD_TYPE=Debug .. && make && popd

debug-assembler: build-debug-assembler
	lldb $(assemblerBuildDir)/virtualassembler

debug-cpu: build-debug-cpu
	lldb $(cpuBuildDir)/virtualcpu

format:
	find . -not -path "*/\.*" -not -path "*/build/*" \( -iname '*.cpp' -or -iname '*.hpp' \) -exec clang-format -style=file -i --verbose {} \;

all: clean virtualassembler virtualcpu virtualeditor test-assembler test-cpu

help:
	@echo ".———————————————————————————————————————."
	@echo "| Sam's Virtual Console: build commands |"
	@echo "°———————————————————————————————————————°"
	@echo "Dependencies:"
	@echo " - cmake"
	@echo " - qmake (if building the editor)"
	@echo ""
	@echo "Available tasks (default is marked by *):"
	@echo "*all			clean then build all projects and run tests"
	@echo " clean			remove files and directories generated during compilation"
	@echo " virtualassembler	compile the Virtual Assembler for releases"
	@echo " virtualcpu		compile the Virtual CPU for releases"
	@echo " virtualeditor		compile the Virtual Editor (GUI) for releases"
	@echo " test-assembler		run tests for Virtual Assembler"
	@echo " test-cpu		run tests for Virtual CPU"
	@echo " run-assembler		compile then run the Virtual Assembler"
	@echo " run-cpu 		compile then run the Virtual CPU"
	@echo " run-editor		compile then run the Virtual Editor"
	@echo " debug-assembler 	compile the Virtual Assembler for debug then launch a debugger (lldb)"
	@echo " debug-cpu		compile the Virtual CPU for debug then launch a debugger (lldb)"
	@echo " format			format C++ source files"
	@echo " help			show this help message"
	@echo ""
