buildDir = build
assemblerBuildDir = `pwd`/Assembler/$(buildDir)
cpuBuildDir = `pwd`/CPU/$(buildDir)
editorBuildDir = `pwd`/Editor/$(buildDir)

.DEFAULT_GOAL := help

samvirtassembler: build-directories
	pushd $(assemblerBuildDir) && cmake .. && make && popd

samvirtcpu: build-directories
	pushd $(cpuBuildDir) && cmake .. && make && make test ARGS="-V" && popd

samvirteditor: build-directories
	pushd $(editorSourceDir) && qmake && make && popd

clean:
	rm -rf $(assemblerBuildDir)/*
	rm -rf $(cpuBuildDir)/*
	rm -rf $(editorBuildDir)/*

build-directories:
	@mkdir -p $(assemblerBuildDir)
	@mkdir -p $(cpuBuildDir)
	@mkdir -p $(editorBuildDir)

run-assembler: samvirtassembler
	$(assemblerBuildDir)/virtualassembler

run-cpu: samvirtcpu
	$(cpuBuildDir)/virtualcpu

run-editor: samvirteditor
	open $(editorBuildDir)/editor.app

debug-assembler: samvirtassembler
	lldb $(assemblerBuildDir)/virtualassembler

debug-cpu: samvirtcpu
	lldb $(cpuBuildDir)/virtualcpu

format:
	find . -not -path "*/\.*" -not -path "*/build/*" \( -iname '*.cpp' -or -iname '*.hpp' \) -exec clang-format -style=file -i --verbose {} \;

all: clean samvirtassembler samvirtcpu samvirteditor

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
	@echo " samvirtassembler	compile samvirtassembler"
	@echo " samvirtcpu		compile samvirtcpu"
	@echo " samvirteditor		compile editor.app"
	@echo " run-assembler		compile then run the samvirtassembler"
	@echo " run-cpu 		compile then run the samvirtcpu"
	@echo " run-editor		compile then run editor.app"
	@echo " debug-assembler 	compile samvirtassembler then launch a debugger (lldb)"
	@echo " debug-cpu		compile samvirtcpu then launch a debugger (lldb)"
	@echo " format			format C++ source files"
	@echo " help			show this help message"
	@echo ""
