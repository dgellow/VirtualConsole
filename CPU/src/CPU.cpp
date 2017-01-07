#include "CPU.hpp"

uint8_t* registerRef(CPU& cpu, opsoperand operand) {
  uint8_t* reg;
  switch (operand) {
  case opsoperand::pc:
    reg = &cpu.pc;
    break;
  case opsoperand::stack:
    reg = &cpu.stack;
    break;
  case opsoperand::a:
    reg = &cpu.a;
    break;
  case opsoperand::x:
    reg = &cpu.x;
    break;
  case opsoperand::y:
    reg = &cpu.y;
    break;
  }
  return reg;
}

void load(CPU &cpu, Instruction instruction) {
  uint8_t* to = registerRef(cpu, instruction.operation.operand1);
  to = uint8_t();
}

void store(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::sta:
    break;
  case ops::stx:
    break;
  case ops::sty:
    break;
  }
}

void arithmetic(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::adc:
    break;
  case ops::sbc:
    break;
  }
}

void inc(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::inc:
    break;
  case ops::inx:
    break;
  case ops::iny:
    break;
  }
}

void dec(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::dec:
    break;
  case ops::dex:
    break;
  case ops::dey:
    break;
  }
}

void shift(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::asl:
    break;
  case ops::lsr:
    break;
  }
}

void rotate(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::rol:
    break;
  case ops::ror:
    break;
  }
}

void logic(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::and_:
    break;
  case ops::ora:
    break;
  case ops::eor:
    break;
  }
}

void compare(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::cmp:
    break;
  case ops::cpx:
    break;
  case ops::cpy:
    break;
  case ops::bit:
    break;
  }
}

void branch(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::bcc:
    break;
  case ops::bcs:
    break;
  case ops::beq:
    break;
  case ops::bmi:
    break;
  case ops::bne:
    break;
  case ops::bpl:
    break;
  case ops::bvc:
    break;
  case ops::bvs:
    break;
  }
}

void transfer(CPU &cpu, Instruction instruction) {
  uint8_t* from = registerRef(cpu, instruction.operation.operand1);
  uint8_t* to = registerRef(cpu, instruction.operation.operand2);
  to = from;
}

void tostack(CPU &cpu, Instruction instruction) {
  uint8_t* from = registerRef(cpu, instruction.operation.operand1);
  uint8_t* to = registerRef(cpu, instruction.operation.operand2);
  to = from;
}

void jump(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::jmp:
    break;
  case ops::jsr:
    break;
  }
}

void subroutine(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::rts:
    break;
  case ops::rti:
    break;
  }
}

void set(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::sec:
    cpu.c = true;
    break;
  case ops::sed:
    cpu.d = true;
    break;
  case ops::sei:
    cpu.i = true;
    break;
  }
}

void clear(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::clc:
    cpu.c = false;
    break;
  case ops::cld:
    cpu.d = false;
    break;
  case ops::cli:
    cpu.i = false;
    break;
  case ops::clv:
    cpu.v = false;
    break;
  }
}

void other(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::nop:
    // do nothing
    break;
  case ops::brk:
    cpu.b = true;
    cpu.i = true;
    break;
  }
}

void CPU::compute(Instruction instruction, Memory memory) {
  switch (instruction.operation.group) {
  case opsgroup::load: load(*this, instruction); break;
  case opsgroup::store: store(*this, instruction); break;
  case opsgroup::arithmetic: arithmetic(*this, instruction); break;
  case opsgroup::inc: inc(*this, instruction); break;
  case opsgroup::dec: dec(*this, instruction); break;
  case opsgroup::shift: shift(*this, instruction); break;
  case opsgroup::rotate: rotate(*this, instruction); break;
  case opsgroup::logic: logic(*this, instruction); break;
  case opsgroup::compare: compare(*this, instruction); break;
  case opsgroup::branch: branch(*this, instruction); break;
  case opsgroup::transfer: transfer(*this, instruction); break;
  case opsgroup::stack: tostack(*this, instruction); break;
  case opsgroup::jump: jump(*this, instruction); break;
  case opsgroup::subroutine: subroutine(*this, instruction); break;
  case opsgroup::set: set(*this, instruction); break;
  case opsgroup::clear: clear(*this, instruction); break;
  case opsgroup::other: other(*this, instruction); break;
  }
}
