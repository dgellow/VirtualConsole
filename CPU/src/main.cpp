#include <iostream>
#include <string>

#include "Machine.hpp"
#include "Parser.hpp"
#include "RunFlags.hpp"

const std::string appName("samvirtcpu");

bool findArgument(int argc, char *argv[], std::string arg) {
  for (auto i = 0; i < argc; i++) {
    if (std::string(argv[i]) == arg) {
      return true;
    }
  }
  return false;
}

void printUsage() {
  std::cout << "OVERVIEW: Sam's Virtual CPU" << std::endl;
  std::cout << std::endl;
  std::cout << "USAGE: " << appName << " COMMAND [options]" << std::endl;
  std::cout << std::endl;
  std::cout << "COMMANDS:" << std::endl;
  std::cout << "\tparse" << std::endl;
  std::cout << "\thelp" << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Error: no command specified" << std::endl;
    printUsage();
    exit(1);
  }

  std::string command(argv[1]);

  if (command == "help" || command == "-h" || command == "--help") {
    printUsage();
    exit(0);
  } else if (command == "parse") {
    if (argc < 3 || argc > 5) {
      std::cerr << "Error: invalid usage" << std::endl;
      std::cout << "Usage: " << appName << " parse [OPTIONS] <inputfile>" << std::endl;
      exit(1);
    } else {
      std::string inputfile = argv[argc - 1];
      RunFlags::testOutput = findArgument(argc, argv, "--test-output");
      RunFlags::debugParser = findArgument(argc, argv, "--debug-parser");

      auto instructions = Parser::parse(inputfile);
      Machine::run(instructions);

      exit(0);
    }
  } else {
    std::cerr << "Error: unknown command" << std::endl;
    std::cout << "See usage with the command help, -h or --help" << std::endl;
  }

  return -1;
}
