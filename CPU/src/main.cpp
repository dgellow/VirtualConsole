#include <iostream>
#include <string>

#include "Machine.hpp"
#include "Parser.hpp"
#include "RunFlags.hpp"

using namespace std;

const string appName("samvirtcpu");

bool findArgument(int argc, char *argv[], string arg) {
  for (auto i = 0; i < argc; i++) {
    if (string(argv[i]) == arg) {
      return true;
    }
  }
  return false;
}

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

  string command(argv[1]);

  if (command == "help" || command == "-h" || command == "--help") {
    printUsage();
    exit(0);
  } else if (command == "parse") {
    if (argc < 3 || argc > 5) {
      cerr << "Error: invalid usage" << endl;
      cout << "Usage: " << appName << " parse [OPTIONS] <inputfile>" << endl;
      exit(1);
    } else {
      string inputfile = argv[argc - 1];
      RunFlags::testOutput = findArgument(argc, argv, "--test-output");
      RunFlags::debugParser = findArgument(argc, argv, "--debug-parser");

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
