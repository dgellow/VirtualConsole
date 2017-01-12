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
    is(machine.cpu.a, 0x22, "lda #$22");
    is(machine.cpu.x, 33, "lda #$22");
    is(machine.cpu.y, 44, "lda #$22");
    machine.run(1);
    is(machine.cpu.a, 0x22, "ldx #$33");
    is(machine.cpu.x, 0x33, "ldx #$33");
    is(machine.cpu.y, 44, "ldx #$33");
    machine.run(1);
    is(machine.cpu.a, 0x22, "ldy #$44");
    is(machine.cpu.x, 0x33, "ldy #$44");
    is(machine.cpu.y, 0x44, "ldy #$44");


    test("Load instructions: absolute");
    machine.memory.set(0x1020, 55);
    machine.memory.set(0x1030, 66);
    machine.memory.set(0x1040, 77);

    machine.run(1);
    is(machine.cpu.a, 55, "lda $1020");
    machine.run(1);
    is(machine.cpu.x, 66, "ldx $1030");
    machine.run(1);
    is(machine.cpu.y, 77, "ldy $1040");


    test("Load instructions: absolute indexed x");
    machine.memory.set(0x1020, 60);
    machine.memory.set(0x1021, 61);
    machine.memory.set(0x1022, 62);
    machine.memory.set(0x1040, 80);
    machine.memory.set(0x1041, 81);
    machine.memory.set(0x1042, 82);

    machine.run(2);
    is(machine.cpu.a, 60, "lda $1020,x when x=0");
    machine.run(2);
    is(machine.cpu.a, 61, "lda $1020,x when x=1");
    machine.run(2);
    is(machine.cpu.a, 62, "lda $1020,x when x=2");

    machine.run(2);
    is(machine.cpu.y, 80, "ldy $1040,x when x=0");
    machine.run(2);
    is(machine.cpu.y, 81, "ldy $1040,x when x=1");
    machine.run(2);
    is(machine.cpu.y, 82, "ldy $1040,x when x=2");


    test("Load instructions: absolute indexed y");
    machine.memory.set(0x1020, 60);
    machine.memory.set(0x1021, 61);
    machine.memory.set(0x1022, 62);
    machine.memory.set(0x1030, 70);
    machine.memory.set(0x1031, 71);
    machine.memory.set(0x1032, 72);

    machine.run(2);
    is(machine.cpu.a, 60, "lda $1020,y when y=0");
    machine.run(2);
    is(machine.cpu.a, 61, "lda $1020,y when y=1");
    machine.run(2);
    is(machine.cpu.a, 62, "lda $1020,y when y=2");

    machine.run(2);
    is(machine.cpu.x, 70, "ldx $1030,y when y=0");
    machine.run(2);
    is(machine.cpu.x, 71, "ldx $1030,y when y=1");
    machine.run(2);
    is(machine.cpu.x, 72, "ldx $1030,y when y=2");


    test("Load instructions: zeropage");
    machine.memory.set(0x20, 5);
    machine.memory.set(0x30, 6);
    machine.memory.set(0x40, 7);

    machine.run(1);
    is(machine.cpu.a, 5, "lda $20");
    machine.run(1);
    is(machine.cpu.x, 6, "ldx $30");
    machine.run(1);
    is(machine.cpu.y, 7, "ldy $40");


    test("Load instructions: zeropage indexed x");
    machine.memory.set(0x20, 10);
    machine.memory.set(0x21, 11);
    machine.memory.set(0x22, 12);
    machine.memory.set(0x40, 30);
    machine.memory.set(0x41, 31);
    machine.memory.set(0x42, 32);

    machine.run(2);
    is(machine.cpu.a, 10, "lda $20,x when x=0");
    machine.run(2);
    is(machine.cpu.a, 11, "lda $20,x when x=1");
    machine.run(2);
    is(machine.cpu.a, 12, "lda $20,x when x=2");

    machine.run(2);
    is(machine.cpu.y, 30, "ldy $40,x when x=0");
    machine.run(2);
    is(machine.cpu.y, 31, "ldy $40,x when x=1");
    machine.run(2);
    is(machine.cpu.y, 32, "ldy $40,x when x=2");


    test("Load instructions: zeropage indexed y");
    machine.memory.set(0x20, 100);
    machine.memory.set(0x21, 101);
    machine.memory.set(0x22, 102);
    machine.memory.set(0x30, 90);
    machine.memory.set(0x31, 91);
    machine.memory.set(0x32, 92);

    machine.run(2);
    is(machine.cpu.a, 100, "lda $20,y when y=0");
    machine.run(2);
    is(machine.cpu.a, 101, "lda $20,y when y=1");
    machine.run(2);
    is(machine.cpu.a, 102, "lda $20,y when y=2");

    machine.run(2);
    is(machine.cpu.x, 90, "ldx $30,y when y=0");
    machine.run(2);
    is(machine.cpu.x, 91, "ldx $30,y when y=1");
    machine.run(2);
    is(machine.cpu.x, 92, "ldx $30,y when y=2");


    test("Load instructions: zeropage indexed indirect");
    machine.memory.set(0x20, 0x10);
    machine.memory.set(0x21, 0x18);
    machine.memory.set(0x1018, 99);
    machine.memory.set(0x2a, 0x20);
    machine.memory.set(0x2b, 0x19);
    machine.memory.set(0x2019, 79);

    machine.run(2);
    is(machine.cpu.a, 99, "lda ($20,x) when x=0");
    machine.run(2);
    is(machine.cpu.a, 79, "lda ($20,x) when x=10");

    test("Load instructions: zeropage indirect indexed");
    machine.memory.set(0x40, 0x30);
    machine.memory.set(0x41, 0x33);
    machine.memory.set(0x3033, 66);
    machine.memory.set(0x303d, 55);

    machine.run(2);
    is(machine.cpu.a, 66, "lda ($40),y when y=0");
    machine.run(2);
    is(machine.cpu.a, 55, "lda ($40),y when y=10");
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
