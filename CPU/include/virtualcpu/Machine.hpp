#pragma once

#include <sstream>

#include "CPU.hpp"
#include "Instruction.hpp"
#include "Memory.hpp"
#include "ROM.hpp"

struct Machine {
	Machine() {
		cpu = CPU();
		memory = Memory();
	}
	~Machine() {}

	static void run(Instruction6502::Instructions instructions);
	void run(unsigned int steps = 0);
	std::ostringstream ostream();

	CPU cpu;
	ROM rom;
	Memory memory;

private:
	void printState();
	void printExit();
};
