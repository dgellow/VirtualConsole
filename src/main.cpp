#include <iostream>
#include <fstream>
#include <array>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"

using namespace std;

void printUsage() {
    cout << "OVERVIEW: Sam's Virtual Console" << endl;
    cout << endl;
    cout << "USAGE: samvirtcons COMMAND [options]" << endl;
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
  } else if (string(argv[1]) == "compile") {
    if (argc != 4) {
      cerr << "Error: invalid usage" << endl;
      cout << "Usage: samvirtcons compile <inputfile.asm> <outputfile.hack> " << endl;
      exit(1);
    } else {
      string inputfile = argv[2];
      string outputfile = argv[3];

      auto instructions = Parser::parse(inputfile);
      auto output = Compiler::compile(instructions);

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

  return 0;
}
