#ifndef PARSER
#define PARSER

#include "Lexer.hpp"
#include <map>
#include <string>
#include <vector>

using SymMap = std::map<std::string, uint32_t>;

enum InstructionTypes {
	CInstruction,
	AInstruction,
};

struct Instruction {
	Instruction(uint32_t position, uint32_t line) : position(position), line(line){};
	~Instruction(){};

	void make_A(uint32_t address) {
		this->type = AInstruction;
		this->address = address;
	}

	void make_C(Token dest, std::vector<Token> cond, Token jump) {
		this->type = CInstruction;
		this->dest = dest;
		this->cond = cond;
		this->jump = jump;
	}

	InstructionTypes type;

	uint32_t address = 0; // <- A

	Token dest;              // <- C
	std::vector<Token> cond; // <- C
	Token jump;              // <- C
	uint32_t position;
	uint32_t line;
};

using Instructions = std::vector<Instruction>;

class Parser {
public:
	static Instructions parse(std::string filepath);

	SymMap makeSymbolsMap();
	SymMap collectSymbols(TokensList tokens);

	Instructions parseLine(std::string line);
	Instructions generateInstructions(TokensList tokens, SymMap symbols);

private:
	Parser(){};
	~Parser(){};

	uint32_t nextFreeAddress() {
		freeAddress++;
		return freeAddress;
	}

	uint32_t freeAddress = 15;
};

#endif /* PARSER */
