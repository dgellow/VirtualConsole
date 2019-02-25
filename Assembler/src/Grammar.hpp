#ifndef __Grammar__
#define __Grammar__

#include <array>
#include <map>
#include <string>

namespace Grammar {
enum Tokens {
  UNASSIGNED,
  AT_SYM,
  EQ_SYM,
  COLON_SYM,
  SEMICOLON_SYM,
  PLUS_SYM,
  MINUS_SYM,
  BANG_SYM,
  AND_SYM,
  OR_SYM,
  PARENTOPEN_SYM,
  PARENTCLOSE_SYM,
  ALPHA,
  DIGIT,
  VARIABLE,
  LABEL,
};

const std::map<Tokens, std::string> legalKeyword = {
    {AT_SYM, "@"},   {EQ_SYM, "="},  {COLON_SYM, ":"}, {SEMICOLON_SYM, ";"},  {PLUS_SYM, "+"},        {MINUS_SYM, "-"},
    {BANG_SYM, "!"}, {AND_SYM, "&"}, {OR_SYM, "|"},    {PARENTOPEN_SYM, "("}, {PARENTCLOSE_SYM, ")"},
};

const std::string legalDest = "ADM";

const std::map<std::string, uint16_t> legalJump = {
    {"", 0b000},    {"JGT", 0b001}, {"JEQ", 0b010}, {"JGE", 0b011},
    {"JLT", 0b100}, {"JNE", 0b101}, {"JLE", 0b110}, {"JMP", 0b111},
};

const std::map<std::string, uint16_t> legalCond = {
    // a=0
    {"0", 0b0101010},
    {"1", 0b0111111},
    {"-1", 0b0111010},
    {"D", 0b0001100},
    {"A", 0b0110000},
    {"!D", 0b0001101},
    {"!A", 0b0110001},
    {"-D", 0b0001111},
    {"-A", 0b0110011},
    {"D+1", 0b0011111},
    {"A+1", 0b0110111},
    {"D-1", 0b0001110},
    {"A-1", 0b0110010},
    {"D+A", 0b0000010},
    {"D-A", 0b0010011},
    {"A-D", 0b0010011},
    {"D&A", 0b0000000},
    {"D|A", 0b0010101},
    // a=1
    {"M", 0b1110000},
    {"!M", 0b1110001},
    {"-M", 0b1110011},
    {"M+1", 0b1110111},
    {"M-1", 0b1110010},
    {"D+M", 0b1000010},
    {"D-M", 0b1010011},
    {"M-D", 0b1000111},
    {"D&M", 0b1000000},
    {"D|M", 0b1010101}};
} // namespace Grammar

#endif /* __Grammar__ */
