#include <iostream>
#include <fstream>
#include "RunFlags.hpp"
#include "Parser.hpp"
#include "Machine.hpp"
#include <string>

int testNumber = 0;
int testFailures = 0;

void test(std::string testName) {
  std::cout << "Test: " << testName << std::endl;
}

bool is(int x, int y, std::string msg = "") {
  testNumber++;
  bool success = x == y;
  if (!success) {
    testFailures ++;
    std::cerr << "Test n°" << testNumber << " failed: "
              << msg
              << ": actual value " << x
              << ", expected value " << y
              << std::endl;
  }
  return success;
}

int main() {

  // Load
  {
    string file = "tests/CPU/tests_load.out";
    auto instructions = Parser::parse(file);
    auto machine = Machine();

    machine.memory.set(22, 5);
    machine.memory.set(33, 6);
    machine.memory.set(44, 7);

    machine.load(instructions);

    test("Load instructions: default");
    is(machine.cpu.a, 0, "default a register");
    is(machine.cpu.x, 0, "default x register");
    is(machine.cpu.y, 0, "default y register");

    machine.run(3);
    is(machine.cpu.a, 0, "lda 0");
    is(machine.cpu.x, 0, "ldx 0");
    is(machine.cpu.x, 0, "ldy 0");

    test("Load instructions: immediate");
    machine.run(1);
    is(machine.cpu.a, 22, "lda #22");
    is(machine.cpu.x, 0, "lda #22");
    is(machine.cpu.y, 0, "lda #22");
    machine.run(1);
    is(machine.cpu.a, 22, "ldx #33");
    is(machine.cpu.x, 33, "ldx #33");
    is(machine.cpu.y, 0, "ldx #33");
    machine.run(1);
    is(machine.cpu.a, 22, "ldy #44");
    is(machine.cpu.x, 33, "ldy #44");
    is(machine.cpu.y, 44, "ldy #44");

    test("Load instructions: immediate hex");
    machine.run(1);
    is(machine.cpu.a, 34, "lda #$22");
    is(machine.cpu.x, 33, "lda #$22");
    is(machine.cpu.y, 44, "lda #$22");
    machine.run(1);
    is(machine.cpu.a, 34, "ldx #$33");
    is(machine.cpu.x, 51, "ldx #$33");
    is(machine.cpu.y, 44, "ldx #$33");
    machine.run(1);
    is(machine.cpu.a, 34, "ldy #$44");
    is(machine.cpu.x, 51, "ldy #$44");
    is(machine.cpu.y, 68, "ldy #$44");

    test("Load instructions: absolute");
    machine.run(1);
    is(machine.cpu.a, 5, "lda $22");
    machine.run(1);
    is(machine.cpu.x, 6, "ldx $33");
    machine.run(1);
    is(machine.cpu.y, 7, "ldy $44");


  }

  // // Store
  // {
  //   string file = "tests/CPU/tests_store.out";
  //   auto instructions = Parser::parse(file);
  //   auto machine = Machine();

  //   machine.memory.set(1, 22);
  //   machine.memory.set(2, 33);
  //   machine.memory.set(3, 44);

  //   machine.load(instructions);
  //   machine.run();
  // }

  if (testFailures != 0) {
    std::cerr << "Some tests failed. Failures: " << testFailures << "/" << testNumber << std::endl;
    exit(1);
  } else {
    std::cout << "All tests passed" << std::endl;
  }

  return 0;
}
