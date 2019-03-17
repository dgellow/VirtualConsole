#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "virtualcpu/Parser.hpp"
#include "virtualcpu/RunFlags.hpp"
#include "virtualcpu/Utils.hpp"

void printInstruction(Instruction6502::Instruction instruction) {
	std::cout << Instruction6502::opsnames[int(instruction.operation.ops)] << " "
	          << Instruction6502::addressModeSym[int(instruction.operation.addressMode)] << " ";
	if (instruction.dataLength > 0) {
		std::cout << Utils::sstreamHexByte(instruction.dataMsb).str()
		          << Utils::sstreamHexByte(instruction.dataLsb).str();
	}
	std::cout << std::endl;
}

Instruction6502::Instructions Parser::parseFile(std::ifstream &file) {
	Instruction6502::Instructions instructions;

	// Two first bytes specify the memory location of the program
	char lsbProgramLocation;
	char msbProgramLocation;
	file.get(lsbProgramLocation);
	file.get(msbProgramLocation);

	// instructions.push_back(Instruction(Operation(ops::programLocation, opsgroup::other,
	//                                              addressMode::implied, opsoperand::none),
	//                                    0, lsbProgramLocation, msbProgramLocation));

	if (RunFlags::debugParser) {
		std::cout << "Program location in memory: " << Utils::sstreamHexByte(msbProgramLocation).str()
		          << Utils::sstreamHexByte(lsbProgramLocation).str() << std::endl;
	}

	char c;

	while (file.get(c)) {
		auto ic = Utils::to_uint16(c);

		// Get operation based on opcode
		Instruction6502::Operation operation;
		try {
			operation = Instruction6502::opscodes.at(ic);
		} catch (std::out_of_range e) {
			std::cerr << "Parsing error: the byte " << std::hex << ic << " isn't a supported opcode" << std::endl;
			continue;
		}

		// Read operation data
		int dataLength = 0;
		try {
			dataLength = Instruction6502::dataLength.at(operation.addressMode);
		} catch (std::out_of_range e) {
			std::cerr << "Parsing error: no data length found for addressMode "
			          << Instruction6502::addressModeSym[int(operation.addressMode)] << std::endl;
			continue;
		}

		char lsb = 0;
		char msb = 0;
		if (dataLength == 1) {
			file.get(lsb);
		} else if (dataLength == 2) {
			file.get(lsb);
			file.get(msb);
		}

		// Add instruction to the vector
		auto instruction = Instruction6502::Instruction(operation, dataLength, lsb, msb);
		instructions.push_back(instruction);
		RunFlags::debugParser ? printInstruction(instruction) : (void)0;
	}

	if (RunFlags::debugParser) {
		std::cout << std::endl;
	}
	return instructions;
}

Instruction6502::Instructions Parser::parse(std::string filepath) {
	std::ifstream file;
	file.open(filepath, std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("Parsing error: cannot read input file: " + filepath);
	}

	auto instructions = parseFile(file);
	file.close();

	return instructions;
}
