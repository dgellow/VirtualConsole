#include "CPU.hpp"

// Return actual data based on address mode of the operation
uint16_t resolveData(CPU &cpu, Memory &memory, addressMode addressMode,
                    uint8_t lsb, uint8_t msb) {
  auto indexedLsb = memory.at(lsb + cpu.x);
  auto indexedMsb = memory.at(lsb + cpu.x + 1);
  auto indirectLsb = memory.at(lsb);
  auto indirectMsb = memory.at(lsb + 1);

  switch (addressMode) {
  case addressMode::implied:
    throw std::runtime_error("CPU error: instruction with addressMode::implied shouldn't call resolveData");
  case addressMode::absolute: return (msb * 16 * 16) + lsb;
  case addressMode::absoluteIndexedX: return (msb * 16 * 16) + lsb + cpu.x;
  case addressMode::absoluteIndexedY: return (msb * 16 * 16) + lsb + cpu.y;
  case addressMode::accumulator: return cpu.a;
  case addressMode::immediate: return msb * 100 + lsb;
  case addressMode::relative: return cpu.pc + lsb;
  case addressMode::zeropage: return lsb;
  case addressMode::zeropageIndexedIndirect: return (indexedMsb * 16 * 16) + indexedLsb;
  case addressMode::zeropageIndexedX: return lsb + cpu.x;
  case addressMode::zeropageIndexedY: return lsb + cpu.y;
  case addressMode::zeropageIndirectIndexed: return (indirectMsb * 16 * 16) + indirectLsb + cpu.y;
  }
}

// Set flag z based on given value
void setZero(CPU &cpu, uint16_t value) {
  cpu.z = value == 0;
}

// Set flag n based on given value
void setNeg(CPU &cpu, uint16_t value) {
  // The most significant bit specifies if the value can be considered
  // negative.
  cpu.n = value >= 0x80;
}

void load(CPU &cpu, Memory &memory, Instruction instruction) {
  uint16_t d = resolveData(cpu, memory, instruction.operation.addressMode,
                         instruction.dataLsb, instruction.dataMsb);
  switch (instruction.operation.ops) {
  case ops::lda:
    if (instruction.operation.addressMode == addressMode::immediate) {
      cpu.a = d;
    } else {
      cpu.a = memory.at(d);
    }
    break;
  case ops::ldx:
    if (instruction.operation.addressMode == addressMode::immediate) {
      cpu.x = d;
    } else {
      cpu.x = memory.at(d);
    }
    break;
  case ops::ldy:
    if (instruction.operation.addressMode == addressMode::immediate) {
      cpu.y = d;
    } else {
      cpu.y = memory.at(d);
    }
    break;
  }

  cpu.pc++;
}

void store(CPU &cpu, Memory &memory, Instruction instruction) {
  auto d = resolveData(cpu, memory, instruction.operation.addressMode,
                        instruction.dataLsb, instruction.dataMsb);
  switch(instruction.operation.ops) {
  case ops::sta:
    memory.set(d, cpu.a);
    break;
  case ops::stx:
    memory.set(d, cpu.x);
    break;
  case ops::sty:
    memory.set(d, cpu.y);
    break;
  }

  cpu.pc++;
}

void impl_adc(CPU &cpu, uint8_t arg) {
    unsigned const sum = cpu.a + arg + cpu.c;

    cpu.c = sum > 0xff;

    // The overflow flag is set when the sign of the addends is the
    // same and differs from the sign of the sum.
    cpu.v = ~(cpu.a ^ arg) & (cpu.a ^ sum) & 0x80;

    cpu.a = sum;
    setZero(cpu, cpu.a);
    setNeg(cpu, cpu.a);
}

void arithmetic(CPU &cpu, Memory &memory, Instruction instruction) {
  auto d = resolveData(cpu, memory, instruction.operation.addressMode,
                    instruction.dataLsb, instruction.dataMsb);

  if (instruction.operation.addressMode == addressMode::absolute) {
    d = memory.at(d);
  }

  switch(instruction.operation.ops) {
  case ops::adc:
    impl_adc(cpu, d);
    break;
  case ops::sbc:
    impl_adc(cpu, ~d);
    break;
  }

  cpu.pc++;
}

void inc(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::inc:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::inx:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::iny:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void dec(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::dec:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::dex:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::dey:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void shift(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::asl:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::lsr:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void rotate(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::rol:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::ror:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void logic(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::and_:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::ora:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::eor:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void compare(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::cmp:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::cpx:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::cpy:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::bit:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void branch(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::bcc:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::bcs:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::beq:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::bmi:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::bne:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::bpl:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::bvc:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::bvs:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void transfer(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::tax:
    cpu.x = cpu.a;
    setNeg(cpu, cpu.x);
    setZero(cpu, cpu.x);
    break;
  case ops::txa:
    cpu.a = cpu.x;
    setNeg(cpu, cpu.a);
    setZero(cpu, cpu.a);
    break;
  case ops::tay:
    cpu.y = cpu.a;
    setNeg(cpu, cpu.y);
    setZero(cpu, cpu.y);
    break;
  case ops::tya:
    cpu.a = cpu.y;
    setNeg(cpu, cpu.a);
    setZero(cpu, cpu.a);
    break;
  case ops::tsx:
    cpu.x = cpu.stack;
    setNeg(cpu, cpu.x);
    setZero(cpu, cpu.x);
    break;
  case ops::txs:
    cpu.stack = cpu.x;
    setNeg(cpu, cpu.stack);
    setZero(cpu, cpu.stack);
    break;
  }
}

void tostack(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::pha:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::pla:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::php:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::plp:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void jump(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::jmp:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::jsr:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }
}

void subroutine(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::rts:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  case ops::rti:
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
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

  cpu.pc++;
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

  cpu.pc++;
}

void other(CPU &cpu, Instruction instruction) {
  switch(instruction.operation.ops) {
  case ops::nop:
    // do nothing
    break;
  case ops::brk:
    // force an interrupt
    cpu.b = true;
    cpu.i = true;
        throw std::runtime_error("CPU error: unimplemented instruction: " +
                             opsnames[int(instruction.operation.ops)]);
    break;
  }

  cpu.pc++;
}

void CPU::compute(Instruction instruction, Memory &memory) {
  switch (instruction.operation.group) {
  case opsgroup::load: load(*this, memory, instruction); break;
  case opsgroup::store: store(*this, memory, instruction); break;
  case opsgroup::arithmetic: arithmetic(*this, memory, instruction); break;
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
