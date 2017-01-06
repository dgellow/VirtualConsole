#include <iostream>
#include <fstream>
#include <array>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"

using namespace std;

const string appName("samvirtassembler");

void printUsage() {
    cout << "OVERVIEW: Sam's Virtual Assembler" << endl;
    cout << endl;
    cout << "USAGE: " << appName << " COMMAND [options]" << endl;
    cout << endl;
    cout << "COMMANDS:" << endl;
    cout << "\tcompile <inputfile.asm> <outputfile.hack>" << endl;
    cout << "\thelp" << endl;
}

int main (int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: no command specified" << endl;
    printUsage();
    exit(1);
  }

  string command (argv[1]);

  if (command == "help" || command == "-h" || command == "--help") {
    printUsage();
    exit(0);
  } else if (command == "compile") {
    if (argc != 4 && argc != 5) {
      cerr << "Error: invalid usage" << endl;
      cout << "Usage: " << appName << " compile [--debug-parser] <inputfile.asm> <outputfile.hack> " << endl;
      exit(1);
    } else {
      string inputfile;
      string outputfile;
      bool debugParser = false;

      if (argc == 4) {
        inputfile = argv[2];
        outputfile = argv[3];
      } else {
        inputfile = argv[3];
        outputfile = argv[4];
        debugParser = string(argv[2]) == "--debug-parser";
      }

      auto instructions = Parser::parse(inputfile);
      auto output = Compiler::compile(instructions);
      if (debugParser) {
        Compiler::debug(instructions);
      }

      ofstream outfile;
      outfile.open(outputfile);
      outfile << output;
      outfile.close();

      exit(0);
    }
  } else {
    cerr << "Error: unknown command" << endl;
    cout << "See usage with the command help, -h or --help" << endl;
  }

  return -1;
}
