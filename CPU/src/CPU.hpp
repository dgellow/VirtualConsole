#ifndef __CPU__
#define __CPU__

#include <cstdint>
#include "RAM16k.hpp"

// 16-bit processor
//
// Registers:
// A - address pointer
// M - register RAM[A]
// D - data
//
// Operations:
// inc - increment
// add - addition
class CPU {
public:
  CPU() {}
  ~CPU() {}

  void load_addr(uint16_t address) {
    reg_writeA(address);
  }

  // Program control

  uint16_t pc_read() {
    return pc;
  }

  void pc_write(uint16_t v) {
    pc = v;
  }

  void pc_inc() {
    pc++;
  }

  // Registers

  uint16_t& reg_refA() {
    return a;
  }

  uint16_t reg_readA() {
    return a;
  }

  void reg_writeA(uint16_t v) {
    a = v;
  }

  uint16_t reg_readM(RAM16k &memory) {
    return memory.read(a);
  }

  void reg_writeM(RAM16k &memory, uint16_t v) {
    memory.write(a, v);
  }

  uint16_t& reg_refD() {
    return d;
  }

  uint16_t reg_readD() {
    return d;
  }

  void reg_writeD(uint16_t v) {
    d = v;
  }

  uint16_t op_inc(uint16_t &reg_ref) {
    reg_ref++;
    return reg_ref;
  }

  uint16_t op_inc_M(RAM16k &memory) {
    reg_writeM(memory, reg_readM(memory) + 1);
    return reg_readM(memory);
  }

  // Addition
  uint16_t op_add(uint16_t& reg_ref, uint16_t val) {
    return reg_ref + val;
  }

  uint16_t op_add(uint16_t& reg_ref1, uint16_t &reg_ref2) {
    return reg_ref1 + reg_ref2;
  }

  void op_add_into(uint16_t &target_reg_ref, uint16_t &reg_ref, uint16_t val) {
    target_reg_ref = reg_ref + val;
  }

  void op_add_into(uint16_t &target_reg_ref, uint16_t &reg_ref1, uint16_t &reg_ref2) {
    target_reg_ref = reg_ref1 + reg_ref2;
  }

  void op_add_into(uint16_t &target_reg_ref1, uint16_t &target_reg_ref2,
                   uint16_t &reg_ref1, uint16_t val) {
    target_reg_ref1 = target_reg_ref2 = reg_ref1 + val;
  }

  void op_add_into(uint16_t &target_reg_ref1, uint16_t &target_reg_ref2,
                   uint16_t &reg_ref1, uint16_t &reg_ref2) {
    target_reg_ref1 = target_reg_ref2 = reg_ref1 + reg_ref2;
  }

  void op_add_into_M(RAM16k &memory, uint16_t &reg_ref1) {
    reg_writeM(memory, op_add_DA());
  }

  uint16_t op_add_AM(RAM16k &memory) {
    return a + reg_readM(memory);
  }

  uint16_t op_add_DM(RAM16k &memory) {
    return d + reg_readM(memory);
  }

  void op_add_DM_to_A(RAM16k &memory) {
    op_add_DM(memory, a);
  }

  void op_add_DM_to_D(RAM16k &memory) {
    op_add_DM(memory, d);
  }

  void op_add_DM_to_M(RAM16k &memory) {
    reg_writeM(memory, op_add_DM(memory));
  }

private:
  void op_add_DA(uint16_t &reg) {
    reg = op_add_DA();
  }

  void op_add_DM(RAM16k &memory, uint16_t &reg) {
    reg = op_add_DM(memory);
  }

  uint16_t pc;
  uint16_t a;
  uint16_t d;
};

#endif /* __CPU__ */
