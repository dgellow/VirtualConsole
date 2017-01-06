#include <iostream>
#include <string>

using namespace std;

const string appName("samvirteditor");

void printUsage() {
    cout << "OVERVIEW: Sam's Virtual Editor" << endl;
    cout << endl;
    cout << "USAGE: " << appName << " COMMAND [options]" << endl;
    cout << endl;
    cout << "COMMANDS:" << endl;
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
  } else {
    cerr << "Error: unknown command" << endl;
    cout << "See usage with the command help, -h or --help" << endl;
  }

  return -1;
}
