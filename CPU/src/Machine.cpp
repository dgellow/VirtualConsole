#include <iostream>

#include "virtualcpu/Machine.hpp"
#include "virtualcpu/RunFlags.hpp"
#include "virtualcpu/Utils.hpp"

void printHeader() {
	std::cout << "  pc  |"
	          << "  a |"
	          << "  x |"
	          << "  y |"
	          << " c |"
	          << " z |"
	          << " i |"
	          << " d |"
	          << " b |"
	          << " v |"
	          << " n |" << std::endl;
}

std::string boolToStr(bool b) {
	return b ? "✓" : " ";
}

void Machine::printState() {
	std::cout << " " << Utils::sstreamHexByte(cpu.pc, 4).str() << " |"
	          << " " << Utils::sstreamHexByte(cpu.a).str() << " |"
	          << " " << Utils::sstreamHexByte(cpu.x).str() << " |"
	          << " " << Utils::sstreamHexByte(cpu.y).str() << " |"
	          << " " << boolToStr(cpu.c) << " |"
	          << " " << boolToStr(cpu.z) << " |"
	          << " " << boolToStr(cpu.i) << " |"
	          << " " << boolToStr(cpu.d) << " |"
	          << " " << boolToStr(cpu.b) << " |"
	          << " " << boolToStr(cpu.v) << " |"
	          << " " << boolToStr(cpu.n) << " |" << std::endl;
}

void Machine::printExit() {
	std::cout << std::endl
	          << "End of the rom reached" << std::endl
	          << cpu.ostream().str() << memory.ostream().str() << std::endl;
}

void Machine::run(Instruction6502::Instructions instructions) {
	auto machine = Machine();
	machine.rom.load(instructions);
	machine.run();
}

void Machine::run(unsigned int steps) {
	unsigned int nbInstructions = steps;
	RunFlags::testOutput ? printHeader() : (void)0;

	while (cpu.pc < rom.size()) {
		auto instruction = rom.at(cpu.pc);
		cpu.compute(instruction, memory);

		RunFlags::testOutput ? printState() : (void)0;

		if (steps != 0) {
			nbInstructions--;
			if (nbInstructions == 0) {
				break;
			}
		}
	}

	RunFlags::testOutput ? printExit() : (void)0;
}

std::ostringstream Machine::ostream() {
	std::ostringstream os;
	os << "Machine()";
	return os;
}
