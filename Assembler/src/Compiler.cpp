#include <bitset>
#include <iostream>

#include "virtualassembler/Compiler.hpp"
#include "virtualassembler/Grammar.hpp"

std::string condToString(Instruction instruction) {
	std::string cond = "";
	for (auto t : instruction.cond) {
		if (t.value != "") {
			cond += t.value;
		} else {
			try {
				auto keyword = Grammar::legalKeyword.at(t.token);
				cond += keyword;
			} catch (const std::out_of_range e) {
				throw std::invalid_argument(std::string("Compiler error at line ") + std::to_string(t.line) +
				                            ", position " + std::to_string(t.position) +
				                            ": Invalid keyword in condition of C instruction");
			}
		}
	}
	return cond;
}

void Compiler::debug(Instructions instructions) {
	for (auto instruction : instructions) {
		if (instruction.type == AInstruction) {
			std::cout << "@" << instruction.address << std::endl;
		} else if (instruction.type == CInstruction) {
			std::cout << (instruction.dest.value.empty() ? "" : instruction.dest.value + "=")
			          << condToString(instruction)
			          << (instruction.jump.value.empty() ? "" : ";" + instruction.jump.value) << std::endl;
		}
	}
}

std::string Compiler::compile(Instructions instructions) {
	std::string output = "";

	for (auto instruction : instructions) {
		if (instruction.type == AInstruction) {
			output += std::bitset<16>(instruction.address).to_string();
		} else if (instruction.type == CInstruction) {
			// opcode
			output += "111";

			// cond
			auto cond = condToString(instruction);
			try {
				auto bits = Grammar::legalCond.at(cond);
				output += std::bitset<7>(bits).to_string();
			} catch (const std::out_of_range e) {
				throw std::invalid_argument(std::string("Compiler error at line ") + std::to_string(instruction.line) +
				                            ", position " + std::to_string(instruction.position) +
				                            ": Invalid condition in C instruction");
			}

			// dest
			if (instruction.dest.value.find_first_not_of(Grammar::legalDest) == std::string::npos) {
				output += instruction.dest.value.find(Grammar::legalDest[0]) != std::string::npos ? "1" : "0";
				output += instruction.dest.value.find(Grammar::legalDest[1]) != std::string::npos ? "1" : "0";
				output += instruction.dest.value.find(Grammar::legalDest[2]) != std::string::npos ? "1" : "0";
			} else {
				throw std::invalid_argument(std::string("Compiler error at line ") + std::to_string(instruction.line) +
				                            ", position " + std::to_string(instruction.position) +
				                            ": Invalid destination in C instruction");
			}

			// jump
			try {
				auto jump = Grammar::legalJump.at(instruction.jump.value);
				output += std::bitset<3>(jump).to_string();
			} catch (const std::out_of_range e) {
				throw std::invalid_argument(std::string("Compiler error at line ") + std::to_string(instruction.line) +
				                            ", position " + std::to_string(instruction.position) +
				                            ": Invalid jump in C instruction");
			}
		}

		output += '\n';
	}

	return output;
}
