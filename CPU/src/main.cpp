#include <iostream>
#include <string>

#include "Parser.hpp"
#include "Machine.hpp"

using namespace std;

const string appName("samvirtcpu");

void printUsage() {
    cout << "OVERVIEW: Sam's Virtual CPU" << endl;
    cout << endl;
    cout << "USAGE: " << appName << " COMMAND [options]" << endl;
    cout << endl;
    cout << "COMMANDS:" << endl;
    cout << "\tparse" << endl;
    cout << "\thelp" << endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: no command specified" << endl;
    printUsage();
    exit(1);
  }

  string command (argv[1]);

  if (command == "help" || command == "-h" || command == "--help") {
    printUsage();
    exit(0);
  } else if (command == "parse")  {
    if (argc != 3) {
      cerr << "Error: invalid usage" << endl;
      cout << "Usage: " << appName << " parse <inputfile.asm>" << endl;
      exit(1);
    } else {
      string inputfile = argv[2];
      auto instructions = Parser::parse(inputfile);
      Machine::run(instructions);

      exit(0);
    }
  } else {
    cerr << "Error: unknown command" << endl;
    cout << "See usage with the command help, -h or --help" << endl;
  }

  return -1;
}
