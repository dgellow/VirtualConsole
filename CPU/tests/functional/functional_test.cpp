#include <fstream>
#include <iostream>
#include <string>

#include "virtualcpu/Machine.hpp"
#include "virtualcpu/Parser.hpp"
#include "virtualcpu/RunFlags.hpp"

bool globalWasSuccess = true;

struct Tests {
  Tests(std::string testsName) {
    std::cout << std::endl;
    std::cout << testsName << ":" << std::endl;
  }

  ~Tests() { printResults(); }

  void printResults() {
    if (testFailures != 0) {
      std::cerr << "Some tests failed. Failures: " << testFailures << "/" << testNumber << std::endl;
      globalWasSuccess = false;
    } else {
      std::cout << "All tests passed" << std::endl;
    }
  }

  bool is(int x, int y, std::string msg = "") {
    testNumber++;
    assertNumber++;
    bool success = x == y;
    if (!success) {
      testFailures++;
      std::cerr << "  assertion " << assertNumber << " failed: " << msg << ": actual value " << std::dec << x << " (0x"
                << std::hex << x << ")"
                << ", expected value " << std::dec << y << " (0x" << std::hex << y << ")" << std::dec << std::endl;
    }
    return success;
  }

  void test(std::string testName) {
    assertNumber = 0;
    std::cout << "• " << testName << std::endl;
  }

  int assertNumber = 0;
  int testNumber = 0;
  int testFailures = 0;
};

int main() {

  // Load
  {
    auto t = Tests("Load");

    std::string file = "../tests/functional/testdata/tests_load.out";
    auto instructions = Parser::parse(file);
    auto machine = Machine();

    machine.rom.load(instructions);

    t.test("Load instructions: default");
    t.is(machine.cpu.a, 0, "default a register");
    t.is(machine.cpu.x, 0, "default x register");
    t.is(machine.cpu.y, 0, "default y register");

    machine.run(3);
    t.is(machine.cpu.a, 0, "lda 0");
    t.is(machine.cpu.x, 0, "ldx 0");
    t.is(machine.cpu.x, 0, "ldy 0");

    t.test("Load instructions: immediate");
    machine.run(1);
    t.is(machine.cpu.a, 22, "lda #22");
    t.is(machine.cpu.x, 0, "lda #22");
    t.is(machine.cpu.y, 0, "lda #22");
    machine.run(1);
    t.is(machine.cpu.a, 22, "ldx #33");
    t.is(machine.cpu.x, 33, "ldx #33");
    t.is(machine.cpu.y, 0, "ldx #33");
    machine.run(1);
    t.is(machine.cpu.a, 22, "ldy #44");
    t.is(machine.cpu.x, 33, "ldy #44");
    t.is(machine.cpu.y, 44, "ldy #44");

    t.test("Load instructions: immediate hex");
    machine.run(1);
    t.is(machine.cpu.a, 0x22, "lda #$22");
    t.is(machine.cpu.x, 33, "lda #$22");
    t.is(machine.cpu.y, 44, "lda #$22");
    machine.run(1);
    t.is(machine.cpu.a, 0x22, "ldx #$33");
    t.is(machine.cpu.x, 0x33, "ldx #$33");
    t.is(machine.cpu.y, 44, "ldx #$33");
    machine.run(1);
    t.is(machine.cpu.a, 0x22, "ldy #$44");
    t.is(machine.cpu.x, 0x33, "ldy #$44");
    t.is(machine.cpu.y, 0x44, "ldy #$44");

    t.test("Load instructions: absolute");
    machine.memory.set(0x1020, 55);
    machine.memory.set(0x1030, 66);
    machine.memory.set(0x1040, 77);

    machine.run(1);
    t.is(machine.cpu.a, 55, "lda $1020");
    machine.run(1);
    t.is(machine.cpu.x, 66, "ldx $1030");
    machine.run(1);
    t.is(machine.cpu.y, 77, "ldy $1040");

    t.test("Load instructions: absolute indexed x");
    machine.memory.set(0x1020, 60);
    machine.memory.set(0x1021, 61);
    machine.memory.set(0x1022, 62);
    machine.memory.set(0x1040, 80);
    machine.memory.set(0x1041, 81);
    machine.memory.set(0x1042, 82);

    machine.run(2);
    t.is(machine.cpu.a, 60, "lda $1020,x when x=0");
    machine.run(2);
    t.is(machine.cpu.a, 61, "lda $1020,x when x=1");
    machine.run(2);
    t.is(machine.cpu.a, 62, "lda $1020,x when x=2");

    machine.run(2);
    t.is(machine.cpu.y, 80, "ldy $1040,x when x=0");
    machine.run(2);
    t.is(machine.cpu.y, 81, "ldy $1040,x when x=1");
    machine.run(2);
    t.is(machine.cpu.y, 82, "ldy $1040,x when x=2");

    t.test("Load instructions: absolute indexed y");
    machine.memory.set(0x1020, 60);
    machine.memory.set(0x1021, 61);
    machine.memory.set(0x1022, 62);
    machine.memory.set(0x1030, 70);
    machine.memory.set(0x1031, 71);
    machine.memory.set(0x1032, 72);

    machine.run(2);
    t.is(machine.cpu.a, 60, "lda $1020,y when y=0");
    machine.run(2);
    t.is(machine.cpu.a, 61, "lda $1020,y when y=1");
    machine.run(2);
    t.is(machine.cpu.a, 62, "lda $1020,y when y=2");

    machine.run(2);
    t.is(machine.cpu.x, 70, "ldx $1030,y when y=0");
    machine.run(2);
    t.is(machine.cpu.x, 71, "ldx $1030,y when y=1");
    machine.run(2);
    t.is(machine.cpu.x, 72, "ldx $1030,y when y=2");

    t.test("Load instructions: zeropage");
    machine.memory.set(0x20, 5);
    machine.memory.set(0x30, 6);
    machine.memory.set(0x40, 7);

    machine.run(1);
    t.is(machine.cpu.a, 5, "lda $20");
    machine.run(1);
    t.is(machine.cpu.x, 6, "ldx $30");
    machine.run(1);
    t.is(machine.cpu.y, 7, "ldy $40");

    t.test("Load instructions: zeropage indexed x");
    machine.memory.set(0x20, 10);
    machine.memory.set(0x21, 11);
    machine.memory.set(0x22, 12);
    machine.memory.set(0x40, 30);
    machine.memory.set(0x41, 31);
    machine.memory.set(0x42, 32);

    machine.run(2);
    t.is(machine.cpu.a, 10, "lda $20,x when x=0");
    machine.run(2);
    t.is(machine.cpu.a, 11, "lda $20,x when x=1");
    machine.run(2);
    t.is(machine.cpu.a, 12, "lda $20,x when x=2");

    machine.run(2);
    t.is(machine.cpu.y, 30, "ldy $40,x when x=0");
    machine.run(2);
    t.is(machine.cpu.y, 31, "ldy $40,x when x=1");
    machine.run(2);
    t.is(machine.cpu.y, 32, "ldy $40,x when x=2");

    t.test("Load instructions: zeropage indexed y");
    machine.memory.set(0x20, 100);
    machine.memory.set(0x21, 101);
    machine.memory.set(0x22, 102);
    machine.memory.set(0x30, 90);
    machine.memory.set(0x31, 91);
    machine.memory.set(0x32, 92);

    machine.run(2);
    t.is(machine.cpu.x, 90, "ldx $30,y when y=0");
    machine.run(2);
    t.is(machine.cpu.x, 91, "ldx $30,y when y=1");
    machine.run(2);
    t.is(machine.cpu.x, 92, "ldx $30,y when y=2");

    t.test("Load instructions: zeropage indexed indirect");
    machine.memory.set(0x20, 0x10);
    machine.memory.set(0x21, 0x18);
    machine.memory.set(0x1810, 99);
    machine.memory.set(0x2a, 0x20);
    machine.memory.set(0x2b, 0x19);
    machine.memory.set(0x1920, 79);

    machine.run(2);
    t.is(machine.cpu.a, 99, "lda ($20,x) when x=0");
    machine.run(2);
    t.is(machine.cpu.a, 79, "lda ($20,x) when x=10");

    t.test("Load instructions: zeropage indirect indexed");
    machine.memory.set(0x40, 0x30);
    machine.memory.set(0x41, 0x33);
    machine.memory.set(0x3330, 66);
    machine.memory.set(0x333a, 55);

    machine.run(2);
    t.is(machine.cpu.a, 66, "lda ($40),y when y=0");
    machine.run(2);
    t.is(machine.cpu.a, 55, "lda ($40),y when y=10");
  }

  // Store
  {
    auto t = Tests("Store");

    std::string file = "../tests/functional/testdata/tests_store.out";
    auto instructions = Parser::parse(file);
    auto machine = Machine();

    machine.rom.load(instructions);

    t.test("Store instructions: absolute");
    machine.memory.set(0x1020, 0);
    machine.memory.set(0x1021, 0);
    machine.memory.set(0x1022, 0);

    machine.run(3); // lda, ldx, ldy
    machine.run(1);
    t.is(machine.memory.at(0x1020), 1, "sta $1020");
    t.is(machine.memory.at(0x1021), 0, "sta $1020");
    t.is(machine.memory.at(0x1022), 0, "sta $1020");

    machine.run(1);
    t.is(machine.memory.at(0x1020), 1, "stx $1021");
    t.is(machine.memory.at(0x1021), 2, "stx $1021");
    t.is(machine.memory.at(0x1022), 0, "stx $1021");

    machine.run(1);
    t.is(machine.memory.at(0x1020), 1, "sty $1022");
    t.is(machine.memory.at(0x1021), 2, "sty $1022");
    t.is(machine.memory.at(0x1022), 3, "sty $1022");

    t.test("Store instructions: absolute indexed x");
    machine.memory.set(0x1030, 0);
    machine.memory.set(0x1031, 0);
    machine.memory.set(0x1032, 0);

    machine.run(7);
    t.is(machine.memory.at(0x1030), 99, "sta $1030,x when x=0");
    t.is(machine.memory.at(0x1031), 99, "sta $1030,x when x=1");
    t.is(machine.memory.at(0x1032), 99, "sta $1030,x when x=2");

    t.test("Store instructions: absolute indexed y");
    machine.memory.set(0x1040, 0);
    machine.memory.set(0x1041, 0);
    machine.memory.set(0x1042, 0);

    machine.run(7);
    t.is(machine.memory.at(0x1040), 88, "sta $1040,x when x=0");
    t.is(machine.memory.at(0x1041), 88, "sta $1040,x when x=1");
    t.is(machine.memory.at(0x1042), 88, "sta $1040,x when x=2");

    t.test("Store instructions: zeropage");
    machine.memory.set(0x20, 0);
    machine.memory.set(0x21, 0);
    machine.memory.set(0x22, 0);

    machine.run(3); // lda, ldx, ldy
    machine.run(1);
    t.is(machine.memory.at(0x20), 1, "sta $20");
    t.is(machine.memory.at(0x21), 0, "sta $20");
    t.is(machine.memory.at(0x22), 0, "sta $20");

    machine.run(1);
    t.is(machine.memory.at(0x20), 1, "stx $20");
    t.is(machine.memory.at(0x21), 2, "stx $21");
    t.is(machine.memory.at(0x22), 0, "stx $22");

    machine.run(1);
    t.is(machine.memory.at(0x20), 1, "sty $20");
    t.is(machine.memory.at(0x21), 2, "sty $21");
    t.is(machine.memory.at(0x22), 3, "sty $22");

    t.test("Store instructions: zeropage indexed x");
    machine.memory.set(0x30, 0);
    machine.memory.set(0x31, 0);
    machine.memory.set(0x32, 0);

    machine.run(1); // lda
    machine.run(6);
    t.is(machine.memory.at(0x30), 77, "sta $30,x when x=0");
    t.is(machine.memory.at(0x31), 77, "sta $30,x when x=1");
    t.is(machine.memory.at(0x32), 77, "sta $30,x when x=2");

    machine.memory.set(0x40, 0);
    machine.memory.set(0x41, 0);
    machine.memory.set(0x42, 0);

    machine.run(1); // ldy
    machine.run(6);
    t.is(machine.memory.at(0x40), 66, "sty $40,x when x=0");
    t.is(machine.memory.at(0x41), 66, "sty $40,x when x=1");
    t.is(machine.memory.at(0x42), 66, "sty $40,x when x=2");

    t.test("Store instructions: zeropage indexed y");
    machine.memory.set(0x50, 0);
    machine.memory.set(0x51, 0);
    machine.memory.set(0x52, 0);

    machine.run(1); // ldx
    machine.run(6);
    t.is(machine.memory.at(0x50), 55, "stx $50,y when y=0");
    t.is(machine.memory.at(0x51), 55, "stx $50,y when y=1");
    t.is(machine.memory.at(0x52), 55, "stx $50,y when y=2");

    t.test("Store instructions: zeropage indexed indirect");
    machine.memory.set(0x60, 0xab);
    machine.memory.set(0x61, 0x15);
    machine.memory.set(0x15ab, 0);
    machine.memory.set(0x6a, 0xc7);
    machine.memory.set(0x6b, 0x28);
    machine.memory.set(0x28c7, 0);

    machine.run(1); // lda
    machine.run(2);
    t.is(machine.memory.at(0x15ab), 44, "sta ($60,x) when x=0");

    machine.run(2);
    t.is(machine.memory.at(0x28c7), 44, "sta ($60,x) when x=10");

    t.test("Store instructions: zeropage indirect indexed");
    machine.memory.set(0x70, 0x20);
    machine.memory.set(0x71, 0x36);
    machine.memory.set(0x3620, 0);
    machine.memory.set(0x362a, 0);

    machine.run(1); // lda
    machine.run(2);
    t.is(machine.memory.at(0x3620), 33, "sta ($70),y when y=0");

    machine.run(2);
    t.is(machine.memory.at(0x362a), 33, "sta ($70),y when y=10");
  }

  // Arithmetic
  {
    auto t = Tests("Arithmetic");

    std::string file = "../tests/functional/testdata/tests_arithmetic.out";
    auto instructions = Parser::parse(file);
    auto machine = Machine();

    machine.rom.load(instructions);

    t.test("Arithmetic instructions: adc, immediate mode");
    machine.run(2);
    t.is(machine.cpu.a, 0, "adc #0 when a=0 and c=0");
    t.is(machine.cpu.c, 0, "adc #0 when a=0 and c=0");
    t.is(machine.cpu.n, 0, "adc #0 when a=0 and c=0");
    t.is(machine.cpu.z, 1, "adc #0 when a=0 and c=0");

    machine.run(6);
    t.is(machine.cpu.a, 5, "adc #1, 5 times, when a=0 and c=0");
    t.is(machine.cpu.c, 0, "adc #1, 5 times, when a=0 and c=0");
    t.is(machine.cpu.n, 0, "adc #1, 5 times, when a=0 and c=0");
    t.is(machine.cpu.z, 0, "adc #1, 5 times, when a=0 and c=0");

    machine.run(2);
    t.is(machine.cpu.a, 0x10, "adc #$01 when a=0x0f and c=0");
    t.is(machine.cpu.c, 0, "adc #$01 when a=0x0f and c=0");
    t.is(machine.cpu.n, 0, "adc #$01 when a=0x0f and c=0");
    t.is(machine.cpu.z, 0, "adc #$01 when a=0x0f and c=0");

    machine.run(2);
    t.is(machine.cpu.a, 0x00, "adc #$ff when a=0x01 and c=0");
    t.is(machine.cpu.c, 1, "adc #$01 when a=0x0f and c=0");
    t.is(machine.cpu.n, 0, "adc #$01 when a=0x0f and c=0");
    t.is(machine.cpu.z, 1, "adc #$01 when a=0x0f and c=0");

    machine.run(3);
    t.is(machine.cpu.a, 0x82, "adc #$01 when a=0x81");
    t.is(machine.cpu.c, 0, "adc #$01 when a=0x81");
    t.is(machine.cpu.n, 1, "adc #$01 when a=0x81");
    t.is(machine.cpu.z, 0, "adc #$01 when a=0x81");

    t.test("Arithmetic instructions: sbc, immediate mode");
    machine.run(2);
    t.is(machine.cpu.a, 0xff, "sbc #0 when a=0 and c=0");
    t.is(machine.cpu.c, 0, "sbc #0 when a=0 and c=0");
    t.is(machine.cpu.n, 1, "sbc #0 when a=0 and c=0");
    t.is(machine.cpu.z, 0, "sbc #0 when a=0 and c=0");

    machine.run(6);
    t.is(machine.cpu.a, 0, "sbc #1, 4 times, when a=5 and c=0");
    t.is(machine.cpu.c, 1, "sbc #1, 4 times, when a=5 and c=0");
    t.is(machine.cpu.n, 0, "sbc #1, 4 times, when a=5 and c=0");
    t.is(machine.cpu.z, 1, "sbc #1, 4 times, when a=5 and c=0");

    machine.run(3);
    t.is(machine.cpu.a, 0xf0, "sbc #$10 when a=0x01 and c=0");
    t.is(machine.cpu.c, 0, "sbc #$10 when a=0x01 and c=0");
    t.is(machine.cpu.n, 1, "sbc #$10 when a=0x01 and c=0");
    t.is(machine.cpu.z, 0, "sbc #$10 when a=0x01 and c=0");

    machine.run(3);
    t.is(machine.cpu.a, 0xfd, "sbc #$01 when a=0xff and c=0");
    t.is(machine.cpu.c, 1, "sbc #$01 when a=0xff and c=0");
    t.is(machine.cpu.n, 1, "sbc #$01 when a=0xff and c=0");
    t.is(machine.cpu.z, 0, "sbc #$01 when a=0xff and c=0");

    t.test("Arithmetic instructions: adc, absolute mode");
    machine.run(5);
    t.is(machine.cpu.a, 0, "adc $1020 when a=0 and $1020=0");
    t.is(machine.cpu.c, 0, "adc $1020 when a=0 and $1020=0");
    t.is(machine.cpu.n, 0, "adc $1020 when a=0 and $1020=0");
    t.is(machine.cpu.z, 1, "adc $1020 when a=0 and $1020=0");

    machine.run(8);
    t.is(machine.cpu.a, 25, "adc $1020, 5 times, when a=0 and $1020=5");
    t.is(machine.cpu.c, 0, "adc $1020, 5 times, when a=0 and $1020=5");
    t.is(machine.cpu.n, 0, "adc $1020, 5 times, when a=0 and $1020=5");
    t.is(machine.cpu.z, 0, "adc $1020, 5 times, when a=0 and $1020=5");

    machine.run(4);
    t.is(machine.cpu.a, 0xf3, "adc $1020 when a=0xf0, $1020=3 and c=0");
    t.is(machine.cpu.c, 0, "adc $1020 when a=0xf0, $1020=3 and c=0");
    t.is(machine.cpu.n, 1, "adc $1020 when a=0xf0, $1020=3 and c=0");
    t.is(machine.cpu.z, 0, "adc $1020 when a=0xf0, $1020=3 and c=0");

    machine.run(4);
    t.is(machine.cpu.a, 0x00, "adc $1020 when a=0xf0, $1020=0x10 and c=0");
    t.is(machine.cpu.c, 1, "adc $1020 when a=0xf0, $1020=3 and c=0");
    t.is(machine.cpu.n, 0, "adc $1020 when a=0xf0, $1020=3 and c=0");
    t.is(machine.cpu.z, 1, "adc $1020 when a=0xf0, $1020=3 and c=0");

    machine.run(5);
    t.is(machine.cpu.a, 0x82, "adc $1020 when a=1 and $1020=$81");
    t.is(machine.cpu.c, 0, "adc $1020 when a=1 and $1020=0x81");
    t.is(machine.cpu.n, 1, "adc $1020 when a=1 and $1020=0x81");
    t.is(machine.cpu.z, 0, "adc $1020 when a=1 and $1020=0x81");
    t.is(machine.cpu.v, 0, "adc $1020 when a=1 and $1020=0x81");

    t.test("Arithmetic instructions: sbc, absolute mode");
    machine.run(5);
    t.is(machine.cpu.a, 0xff, "sbc $1020 when a=0 and $1020=0");
    t.is(machine.cpu.c, 0, "sbc $1020 when a=0 and $1020=0");
    t.is(machine.cpu.n, 1, "sbc $1020 when a=0 and $1020=0");
    t.is(machine.cpu.z, 0, "sbc $1020 when a=0 and $1020=0");

    machine.run(6);
    t.is(machine.cpu.a, 0xff, "sbc $1020 when a=0 and $1020=0, after a clc");
    t.is(machine.cpu.c, 0, "sbc $1020 when a=0 and $1020=0, after a clc");
    t.is(machine.cpu.n, 1, "sbc $1020 when a=0 and $1020=0, after a clc");
    t.is(machine.cpu.z, 0, "sbc $1020 when a=0 and $1020=0, after a clc");

    machine.run(6);
    t.is(machine.cpu.a, 0x00, "sbc $1020 when a=0 and $1020=0, after a sec");
    t.is(machine.cpu.c, 1, "sbc $1020 when a=0 and $1020=0, after a sec");
    t.is(machine.cpu.n, 0, "sbc $1020 when a=0 and $1020=0, after a sec");
    t.is(machine.cpu.z, 1, "sbc $1020 when a=0 and $1020=0, after a sec");

    machine.run(14);
    t.is(machine.cpu.a, 0xe2, "sbc $1020, 5 times, when a=0 and $1020=5, with clc");
    t.is(machine.cpu.c, 1, "sbc $1020, 5 times, when a=0 and $1020=5, with clc");
    t.is(machine.cpu.n, 1, "sbc $1020, 5 times, when a=0 and $1020=5, with clc");
    t.is(machine.cpu.z, 0, "sbc $1020, 5 times, when a=0 and $1020=5, with clc");
    t.is(machine.cpu.v, 0, "sbc $1020, 5 times, when a=0 and $1020=5, with clc");

    machine.run(14);
    t.is(machine.cpu.a, 0xe7, "sbc $1020, 5 times, when a=0 and $1020=5, with sec");
    t.is(machine.cpu.c, 1, "sbc $1020, 5 times, when a=0 and $1020=5, with sec");
    t.is(machine.cpu.n, 1, "sbc $1020, 5 times, when a=0 and $1020=5, with sec");
    t.is(machine.cpu.z, 0, "sbc $1020, 5 times, when a=0 and $1020=5, with sec");
    t.is(machine.cpu.v, 0, "sbc $1020, 5 times, when a=0 and $1020=5, with sec");

    machine.run(5);
    t.is(machine.cpu.a, 0xfe, "sbc $1020 when a=0x01 and $1020=0x00");
    t.is(machine.cpu.c, 0, "sbc $1020 when a=0x01 and $1020=0x00");
    t.is(machine.cpu.n, 1, "sbc $1020 when a=0x01 and $1020=0x00");
    t.is(machine.cpu.z, 0, "sbc $1020 when a=0x01 and $1020=0x00");
    t.is(machine.cpu.v, 0, "sbc $1020 when a=0x01 and $1020=0x00");

    machine.run(5);
    t.is(machine.cpu.a, 0x80, "sbc $1020 when a=0x81 and $1020=0x00");
    t.is(machine.cpu.c, 1, "sbc $1020 when a=0x81 and $1020=0x00");
    t.is(machine.cpu.n, 1, "sbc $1020 when a=0x81 and $1020=0x00");
    t.is(machine.cpu.z, 0, "sbc $1020 when a=0x81 and $1020=0x00");
    t.is(machine.cpu.v, 0, "sbc $1020 when a=0x81 and $1020=0x00");

    machine.run(5);
    t.is(machine.cpu.a, 0x7f, "sbc $1020 when a=0x80 and $1020=0x00");
    t.is(machine.cpu.c, 1, "sbc $1020 when a=0x80 and $1020=0x00");
    t.is(machine.cpu.n, 0, "sbc $1020 when a=0x80 and $1020=0x00");
    t.is(machine.cpu.z, 0, "sbc $1020 when a=0x80 and $1020=0x00");
    t.is(machine.cpu.v, 1, "sbc $1020 when a=0x80 and $1020=0x00");

    machine.run(5);
    t.is(machine.cpu.a, 0x7d, "sbc $1020 when a=0x7f and $1020=0x01");
    t.is(machine.cpu.c, 1, "sbc $1020 when a=0x7f and $1020=0x01");
    t.is(machine.cpu.n, 0, "sbc $1020 when a=0x7f and $1020=0x01");
    t.is(machine.cpu.z, 0, "sbc $1020 when a=0x7f and $1020=0x01");
    t.is(machine.cpu.v, 0, "sbc $1020 when a=0x7f and $1020=0x01");

    t.test("Arithmetic instructions: adc, absolute indexed x");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: sbc, absolute indexed x");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: adc, absolute indexed y");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: sbc, absolute indexed y");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: adc, zeropage mode");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: sbc, zeropage mode");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: adc, zeropage indexed x");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: sbc, zeropage indexed x");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: adc, zeropage indexed y");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: sbc, zeropage indexed y");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: adc, zeropage indexed indirect");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: sbc, zeropage indexed indirect");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: adc, zeropage indirect indexed");
    t.is(0, 999, "unimplemented test");

    t.test("Arithmetic instructions: sbc, zeropage indirect indexed");
    t.is(0, 999, "unimplemented test");
  }

  // Jumps, Subroutines
  {
    auto t = Tests("Jumps and subroutines");

    std::string file = "../tests/functional/testdata/tests_jumps_subroutines.out";
    auto instructions = Parser::parse(file);
    auto machine = Machine();

    machine.rom.load(instructions);

    t.test("Jump to subroutine");
    machine.run(9);
    t.is(machine.cpu.a, 0x01, "jsr");
    t.is(machine.cpu.x, 0x02, "jsr");
    t.is(machine.cpu.y, 0x03, "jsr");

    t.test("Jump to memory");
    machine.run(8);
    t.is(machine.cpu.a, 0xff, "jmp");
    t.is(machine.cpu.x, 0xfe, "jmp");
    t.is(machine.cpu.y, 0xfd, "jmp");
  }

  // Set and clear
  {
    auto t = Tests("Set and clear");

    std::string file = "../tests/functional/testdata/tests_set_clear.out";
    auto instructions = Parser::parse(file);
    auto machine = Machine();

    machine.rom.load(instructions);

    t.test("Carry flag");
    machine.run(1);
    t.is(machine.cpu.c, 1, "sec");
    machine.run(1);
    t.is(machine.cpu.c, 0, "clc");

    t.test("Decimal mode");
    machine.run(1);
    t.is(machine.cpu.d, 1, "sed");
    machine.run(1);
    t.is(machine.cpu.d, 0, "cld");

    t.test("Interrupt disable status");
    machine.run(1);
    t.is(machine.cpu.i, 1, "sei");
    machine.run(1);
    t.is(machine.cpu.i, 0, "cli");

    t.test("Overflow flag");
    machine.run(3);
    t.is(machine.cpu.v, 1, "set overflow flag");
    machine.run(1);
    t.is(machine.cpu.v, 0, "clv");
  }

  // Other
  {
    auto t = Tests("Other");

    std::string file = "../tests/functional/testdata/tests_other.out";
    auto instructions = Parser::parse(file);
    auto machine = Machine();

    machine.rom.load(instructions);

    t.test("No operation (nop)");
    machine.run(5);
    t.is(machine.cpu.a, 0, "nop, 5 times");
    t.is(machine.cpu.c, 0, "nop, 5 times");
    t.is(machine.cpu.n, 0, "nop, 5 times");
    t.is(machine.cpu.z, 0, "nop, 5 times");
    t.is(machine.cpu.v, 0, "nop, 5 times");

    machine.run(5);
    t.is(machine.cpu.a, 0x12, "nop in between other instructions");
    t.is(machine.cpu.c, 1, "nop in between other instructions");
    t.is(machine.cpu.n, 0, "nop in between other instructions");
    t.is(machine.cpu.z, 0, "nop in between other instructions");
    t.is(machine.cpu.v, 0, "nop in between other instructions");

    t.test("Break");
    t.is(0, 999, "unimplemented test");
  }

  globalWasSuccess ? exit(0) : exit(1);
}
