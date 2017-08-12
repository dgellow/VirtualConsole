#ifndef __Instruction__
#define __Instruction__

#include "Utils.hpp"

#include <map>
#include <string>
#include <vector>
#include <sstream>

namespace Instruction6502 {
  enum class ops {
    programLocation,
    ldx,
    ldy,
    lda,
    sta,
    stx,
    sty,
    adc,
    sbc,
    inc,
    inx,
    iny,
    dec,
    dex,
    dey,
    asl,
    lsr,
    rol,
    ror,
    and_, // 'and' is a reserved identifier
    ora,
    eor,
    cmp,
    cpx,
    cpy,
    bit,
    bcc,
    bcs,
    beq,
    bmi,
    bne,
    bpl,
    bvc,
    bvs,
    tax,
    txa,
    tay,
    tya,
    tsx,
    txs,
    pha,
    pla,
    php,
    plp,
    jmp,
    jsr,
    rts,
    rti,
    sec,
    sed,
    sei,
    clc,
    cld,
    cli,
    clv,
    nop,
    brk,
  };

  const std::string opsnames[] = {
    "org",
    "ldx",
    "ldy",
    "lda",
    "sta",
    "stx",
    "sty",
    "adc",
    "sbc",
    "inc",
    "inx",
    "iny",
    "dec",
    "dex",
    "dey",
    "asl",
    "lsr",
    "rol",
    "ror",
    "and",
    "ora",
    "eor",
    "cmp",
    "cpx",
    "cpy",
    "bit",
    "bcc",
    "bcs",
    "beq",
    "bmi",
    "bne",
    "bpl",
    "bvc",
    "bvs",
    "tax",
    "txa",
    "tay",
    "tya",
    "tsx",
    "txs",
    "pha",
    "pla",
    "php",
    "plp",
    "jmp",
    "jsr",
    "rts",
    "rti",
    "sec",
    "sed",
    "sei",
    "clc",
    "cld",
    "cli",
    "clv",
    "nop",
    "brk",
  };

  enum class opsgroup {
    load,
    store,
    arithmetic,
    inc,
    dec,
    shift,
    rotate,
    logic,
    compare,
    branch,
    transfer,
    stack,
    subroutine,
    jump,
    set,
    clear,
    other,
  };

  enum class addressMode {
    accumulator,
    immediate,
    implied,
    relative,
    absolute,
    zeropage,
    absoluteIndexedX,
    absoluteIndexedY,
    zeropageIndexedX,
    zeropageIndexedY,
    zeropageIndexedIndirect,
    zeropageIndirectIndexed,
  };

  const std::string addressModeSym[] = {
    "A",
    "#",
    "i",
    "r",
    "a",
    "zp",
    "a,x",
    "a,y",
    "zp,x",
    "zp,y",
    "(zp,x)",
    "(zp),y",
  };

  // The length is the number of bytes following the opcode to use as data
  const std::map<addressMode, unsigned int> dataLength = {
    {addressMode::accumulator, 0},
    {addressMode::immediate, 1},
    {addressMode::implied, 0},
    {addressMode::relative, 1},
    {addressMode::absolute, 2},
    {addressMode::zeropage, 1},
    {addressMode::absoluteIndexedX, 2},
    {addressMode::absoluteIndexedY, 2},
    {addressMode::zeropageIndexedX, 1},
    {addressMode::zeropageIndexedY, 1},
    {addressMode::zeropageIndexedIndirect, 1},
    {addressMode::zeropageIndirectIndexed, 1},
  };

  enum class opsoperand {
    none,
    memory,
    status,
    pc,
    stack,
    a,
    x,
    y,
  };

  const std::string opsoperandSym[] = {
    "none",
    "memory",
    "status",
    "pc",
    "stack",
    "a",
    "x",
    "y",
  };

  struct Operation {
    Operation() {}

    Operation(ops ops, opsgroup group, addressMode addressMode,
              opsoperand operand1, opsoperand operand2 = opsoperand::none)
      : ops(ops), group(group), addressMode(addressMode),
        operand1(operand1), operand2(operand2) {};

    std::ostringstream ostream() {
      std::ostringstream os;
      os << "Operation("
         << "ops=" << opsnames[int(ops)] << ", "
         << "addressMode=" << addressModeSym[int(addressMode)] << ", "
         << "operand1=" << opsoperandSym[int(operand1)] << ", "
         << "operand2=" << opsoperandSym[int(operand2)]
         << ")";
      return os;
    }

    ops ops;
    opsgroup group;
    addressMode addressMode;
    opsoperand operand1;
    opsoperand operand2;
  };

  const std::map<uint8_t, Operation> opscodes = {
    {0xad, Operation(ops::lda, opsgroup::load, addressMode::absolute, opsoperand::a)},
    {0xbd, Operation(ops::lda, opsgroup::load, addressMode::absoluteIndexedX, opsoperand::a)},
    {0xb9, Operation(ops::lda, opsgroup::load, addressMode::absoluteIndexedY, opsoperand::a)},
    {0xa9, Operation(ops::lda, opsgroup::load, addressMode::immediate, opsoperand::a)},
    {0xa5, Operation(ops::lda, opsgroup::load, addressMode::zeropage, opsoperand::a)},
    {0xa1, Operation(ops::lda, opsgroup::load, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0xb5, Operation(ops::lda, opsgroup::load, addressMode::zeropageIndexedX, opsoperand::a)},
    {0xb1, Operation(ops::lda, opsgroup::load, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0xae, Operation(ops::ldx, opsgroup::load, addressMode::absolute, opsoperand::x)},
    {0xbe, Operation(ops::ldx, opsgroup::load, addressMode::absoluteIndexedY, opsoperand::x)},
    {0xa2, Operation(ops::ldx, opsgroup::load, addressMode::immediate, opsoperand::x)},
    {0xa6, Operation(ops::ldx, opsgroup::load, addressMode::zeropage, opsoperand::x)},
    {0xb6, Operation(ops::ldx, opsgroup::load, addressMode::zeropageIndexedY, opsoperand::x)},

    {0xac, Operation(ops::ldy, opsgroup::load, addressMode::absolute, opsoperand::y)},
    {0xbc, Operation(ops::ldy, opsgroup::load, addressMode::absoluteIndexedX, opsoperand::y)},
    {0xa0, Operation(ops::ldy, opsgroup::load, addressMode::immediate, opsoperand::y)},
    {0xa4, Operation(ops::ldy, opsgroup::load, addressMode::zeropage, opsoperand::y)},
    {0xb4, Operation(ops::ldy, opsgroup::load, addressMode::zeropageIndexedX, opsoperand::y)},

    {0x8d, Operation(ops::sta, opsgroup::store, addressMode::absolute, opsoperand::a)},
    {0x9d, Operation(ops::sta, opsgroup::store, addressMode::absoluteIndexedX, opsoperand::a)},
    {0x99, Operation(ops::sta, opsgroup::store, addressMode::absoluteIndexedY, opsoperand::a)},
    {0x85, Operation(ops::sta, opsgroup::store, addressMode::zeropage, opsoperand::a)},
    {0x81, Operation(ops::sta, opsgroup::store, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0x95, Operation(ops::sta, opsgroup::store, addressMode::zeropageIndexedX, opsoperand::a)},
    {0x91, Operation(ops::sta, opsgroup::store, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0x8e, Operation(ops::stx, opsgroup::store, addressMode::absolute, opsoperand::x)},
    {0x86, Operation(ops::stx, opsgroup::store, addressMode::zeropage, opsoperand::x)},
    {0x96, Operation(ops::stx, opsgroup::store, addressMode::zeropageIndexedY, opsoperand::x)},

    {0x8c, Operation(ops::sty, opsgroup::store, addressMode::absolute, opsoperand::y)},
    {0x84, Operation(ops::sty, opsgroup::store, addressMode::zeropage, opsoperand::y)},
    {0x94, Operation(ops::sty, opsgroup::store, addressMode::zeropageIndexedX, opsoperand::y)},

    {0x6d, Operation(ops::adc, opsgroup::arithmetic, addressMode::absolute, opsoperand::a)},
    {0x7d, Operation(ops::adc, opsgroup::arithmetic, addressMode::absoluteIndexedX, opsoperand::a)},
    {0x79, Operation(ops::adc, opsgroup::arithmetic, addressMode::absoluteIndexedY, opsoperand::a)},
    {0x69, Operation(ops::adc, opsgroup::arithmetic, addressMode::immediate, opsoperand::a)},
    {0x65, Operation(ops::adc, opsgroup::arithmetic, addressMode::zeropage, opsoperand::a)},
    {0x61, Operation(ops::adc, opsgroup::arithmetic, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0x75, Operation(ops::adc, opsgroup::arithmetic, addressMode::zeropageIndexedX, opsoperand::a)},
    {0x71, Operation(ops::adc, opsgroup::arithmetic, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0xed, Operation(ops::sbc, opsgroup::arithmetic, addressMode::absolute, opsoperand::a)},
    {0xfd, Operation(ops::sbc, opsgroup::arithmetic, addressMode::absoluteIndexedX, opsoperand::a)},
    {0xf9, Operation(ops::sbc, opsgroup::arithmetic, addressMode::absoluteIndexedY, opsoperand::a)},
    {0xe9, Operation(ops::sbc, opsgroup::arithmetic, addressMode::immediate, opsoperand::a)},
    {0xe5, Operation(ops::sbc, opsgroup::arithmetic, addressMode::zeropage, opsoperand::a)},
    {0xe1, Operation(ops::sbc, opsgroup::arithmetic, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0xf5, Operation(ops::sbc, opsgroup::arithmetic, addressMode::zeropageIndexedX, opsoperand::a)},
    {0xf1, Operation(ops::sbc, opsgroup::arithmetic, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0xee, Operation(ops::inc, opsgroup::inc, addressMode::absolute, opsoperand::memory)},
    {0xfe, Operation(ops::inc, opsgroup::inc, addressMode::absoluteIndexedX, opsoperand::memory)},
    {0xe6, Operation(ops::inc, opsgroup::inc, addressMode::zeropage, opsoperand::memory)},
    {0xf6, Operation(ops::inc, opsgroup::inc, addressMode::zeropageIndexedX, opsoperand::memory)},

    {0xe8, Operation(ops::inx, opsgroup::inc, addressMode::implied, opsoperand::x)},

    {0xc8, Operation(ops::iny, opsgroup::inc, addressMode::implied, opsoperand::y)},

    {0xce, Operation(ops::dec, opsgroup::dec, addressMode::absolute, opsoperand::memory)},
    {0xde, Operation(ops::dec, opsgroup::dec, addressMode::absoluteIndexedX, opsoperand::memory)},
    {0xc6, Operation(ops::dec, opsgroup::dec, addressMode::zeropage, opsoperand::memory)},
    {0xd6, Operation(ops::dec, opsgroup::dec, addressMode::zeropageIndexedX, opsoperand::memory)},

    {0xca, Operation(ops::dex, opsgroup::dec, addressMode::implied, opsoperand::x)},

    {0x88, Operation(ops::dey, opsgroup::dec, addressMode::implied, opsoperand::y)},

    {0x0e, Operation(ops::asl, opsgroup::shift, addressMode::absolute, opsoperand::none)},
    {0x1e, Operation(ops::asl, opsgroup::shift, addressMode::absoluteIndexedX, opsoperand::none)},
    {0x0a, Operation(ops::asl, opsgroup::shift, addressMode::accumulator, opsoperand::none)},
    {0x06, Operation(ops::asl, opsgroup::shift, addressMode::zeropage, opsoperand::none)},
    {0x16, Operation(ops::asl, opsgroup::shift, addressMode::zeropageIndexedX, opsoperand::none)},

    {0x4e, Operation(ops::lsr, opsgroup::shift, addressMode::absolute, opsoperand::none)},
    {0x5e, Operation(ops::lsr, opsgroup::shift, addressMode::absoluteIndexedX, opsoperand::none)},
    {0x4a, Operation(ops::lsr, opsgroup::shift, addressMode::accumulator, opsoperand::none)},
    {0x46, Operation(ops::lsr, opsgroup::shift, addressMode::zeropage, opsoperand::none)},
    {0x56, Operation(ops::lsr, opsgroup::shift, addressMode::zeropageIndexedX, opsoperand::none)},

    {0x2e, Operation(ops::rol, opsgroup::rotate, addressMode::absolute, opsoperand::none)},
    {0x3e, Operation(ops::rol, opsgroup::rotate, addressMode::absoluteIndexedX, opsoperand::none)},
    {0x2a, Operation(ops::rol, opsgroup::rotate, addressMode::accumulator, opsoperand::none)},
    {0x26, Operation(ops::rol, opsgroup::rotate, addressMode::zeropage, opsoperand::none)},
    {0x36, Operation(ops::rol, opsgroup::rotate, addressMode::zeropageIndexedX, opsoperand::none)},

    {0x6e, Operation(ops::ror, opsgroup::rotate, addressMode::absolute, opsoperand::none)},
    {0x7e, Operation(ops::ror, opsgroup::rotate, addressMode::absoluteIndexedX, opsoperand::none)},
    {0x6a, Operation(ops::ror, opsgroup::rotate, addressMode::accumulator, opsoperand::none)},
    {0x66, Operation(ops::ror, opsgroup::rotate, addressMode::zeropage, opsoperand::none)},
    {0x76, Operation(ops::ror, opsgroup::rotate, addressMode::zeropageIndexedX, opsoperand::none)},

    {0x2d, Operation(ops::and_, opsgroup::logic, addressMode::absolute, opsoperand::a)},
    {0x3d, Operation(ops::and_, opsgroup::logic, addressMode::absoluteIndexedX, opsoperand::a)},
    {0x39, Operation(ops::and_, opsgroup::logic, addressMode::absoluteIndexedY, opsoperand::a)},
    {0x29, Operation(ops::and_, opsgroup::logic, addressMode::immediate, opsoperand::a)},
    {0x25, Operation(ops::and_, opsgroup::logic, addressMode::zeropage, opsoperand::a)},
    {0x21, Operation(ops::and_, opsgroup::logic, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0x35, Operation(ops::and_, opsgroup::logic, addressMode::zeropageIndexedX, opsoperand::a)},
    {0x31, Operation(ops::and_, opsgroup::logic, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0x0d, Operation(ops::ora, opsgroup::logic, addressMode::absolute, opsoperand::a)},
    {0x1d, Operation(ops::ora, opsgroup::logic, addressMode::absoluteIndexedX, opsoperand::a)},
    {0x19, Operation(ops::ora, opsgroup::logic, addressMode::absoluteIndexedY, opsoperand::a)},
    {0x09, Operation(ops::ora, opsgroup::logic, addressMode::immediate, opsoperand::a)},
    {0x05, Operation(ops::ora, opsgroup::logic, addressMode::zeropage, opsoperand::a)},
    {0x01, Operation(ops::ora, opsgroup::logic, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0x15, Operation(ops::ora, opsgroup::logic, addressMode::zeropageIndexedX, opsoperand::a)},
    {0x11, Operation(ops::ora, opsgroup::logic, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0x4d, Operation(ops::eor, opsgroup::logic, addressMode::absolute, opsoperand::a)},
    {0x5d, Operation(ops::eor, opsgroup::logic, addressMode::absoluteIndexedX, opsoperand::a)},
    {0x59, Operation(ops::eor, opsgroup::logic, addressMode::absoluteIndexedY, opsoperand::a)},
    {0x49, Operation(ops::eor, opsgroup::logic, addressMode::immediate, opsoperand::a)},
    {0x45, Operation(ops::eor, opsgroup::logic, addressMode::zeropage, opsoperand::a)},
    {0x41, Operation(ops::eor, opsgroup::logic, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0x55, Operation(ops::eor, opsgroup::logic, addressMode::zeropageIndexedX, opsoperand::a)},
    {0x51, Operation(ops::eor, opsgroup::logic, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0xcd, Operation(ops::cmp, opsgroup::compare, addressMode::absolute, opsoperand::a)},
    {0xdd, Operation(ops::cmp, opsgroup::compare, addressMode::absoluteIndexedX, opsoperand::a)},
    {0xd9, Operation(ops::cmp, opsgroup::compare, addressMode::absoluteIndexedY, opsoperand::a)},
    {0xc9, Operation(ops::cmp, opsgroup::compare, addressMode::immediate, opsoperand::a)},
    {0xc5, Operation(ops::cmp, opsgroup::compare, addressMode::zeropage, opsoperand::a)},
    {0xc1, Operation(ops::cmp, opsgroup::compare, addressMode::zeropageIndexedIndirect, opsoperand::a)},
    {0xd5, Operation(ops::cmp, opsgroup::compare, addressMode::zeropageIndexedX, opsoperand::a)},
    {0xd1, Operation(ops::cmp, opsgroup::compare, addressMode::zeropageIndirectIndexed, opsoperand::a)},

    {0xec, Operation(ops::cpx, opsgroup::compare, addressMode::absolute, opsoperand::x)},
    {0xe0, Operation(ops::cpx, opsgroup::compare, addressMode::immediate, opsoperand::x)},
    {0xe4, Operation(ops::cpx, opsgroup::compare, addressMode::zeropage, opsoperand::x)},

    {0xcc, Operation(ops::cpy, opsgroup::compare, addressMode::absolute, opsoperand::y)},
    {0xc0, Operation(ops::cpy, opsgroup::compare, addressMode::immediate, opsoperand::y)},
    {0xc4, Operation(ops::cpy, opsgroup::compare, addressMode::zeropage, opsoperand::y)},

    {0x2c, Operation(ops::bit, opsgroup::compare, addressMode::absolute, opsoperand::a)},
    {0x89, Operation(ops::bit, opsgroup::compare, addressMode::immediate, opsoperand::a)},
    {0x24, Operation(ops::bit, opsgroup::compare, addressMode::zeropage, opsoperand::a)},

    {0x90, Operation(ops::bcc, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0xb0, Operation(ops::bcs, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0xf0, Operation(ops::beq, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0x30, Operation(ops::bmi, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0xd0, Operation(ops::bne, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0x10, Operation(ops::bpl, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0x50, Operation(ops::bvc, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0x70, Operation(ops::bvs, opsgroup::branch, addressMode::relative, opsoperand::none)},

    {0xaa, Operation(ops::tax, opsgroup::transfer, addressMode::implied, opsoperand::a, opsoperand::x)},

    {0x8a, Operation(ops::txa, opsgroup::transfer, addressMode::implied, opsoperand::x, opsoperand::a)},

    {0xa8, Operation(ops::tay, opsgroup::transfer, addressMode::implied, opsoperand::a, opsoperand::y)},

    {0x98, Operation(ops::tya, opsgroup::transfer, addressMode::implied, opsoperand::y, opsoperand::a)},

    {0xba, Operation(ops::tsx, opsgroup::transfer, addressMode::implied, opsoperand::stack, opsoperand::x)},

    {0x9a, Operation(ops::txs, opsgroup::transfer, addressMode::implied, opsoperand::x, opsoperand::stack)},

    {0x48, Operation(ops::pha, opsgroup::stack, addressMode::implied, opsoperand::a, opsoperand::stack)},

    {0x68, Operation(ops::pla, opsgroup::stack, addressMode::implied, opsoperand::stack, opsoperand::a)},

    {0x08, Operation(ops::php, opsgroup::stack, addressMode::implied, opsoperand::status, opsoperand::stack)},

    {0x28, Operation(ops::plp, opsgroup::stack, addressMode::implied, opsoperand::stack, opsoperand::status)},

    {0x4c, Operation(ops::jmp, opsgroup::jump, addressMode::absolute, opsoperand::none)},
    // {0x6c, Operation(ops::jmp, opsgroup::jump, addressMode::, opsoperand::none)}, <== not sure what's the address mode

    {0x20, Operation(ops::jsr, opsgroup::jump, addressMode::absolute, opsoperand::none)},

    {0x60, Operation(ops::rts, opsgroup::subroutine, addressMode::implied, opsoperand::none)},

    {0x40, Operation(ops::rti, opsgroup::subroutine, addressMode::implied, opsoperand::none)},

    {0x38, Operation(ops::sec, opsgroup::set, addressMode::implied, opsoperand::none)},

    {0xf8, Operation(ops::sed, opsgroup::set, addressMode::implied, opsoperand::none)},

    {0x78, Operation(ops::sei, opsgroup::set, addressMode::implied, opsoperand::none)},

    {0x18, Operation(ops::clc, opsgroup::clear, addressMode::implied, opsoperand::none)},

    {0xd8, Operation(ops::cld, opsgroup::clear, addressMode::implied, opsoperand::none)},

    {0x58, Operation(ops::cli, opsgroup::clear, addressMode::implied, opsoperand::none)},

    {0xb8, Operation(ops::clv, opsgroup::clear, addressMode::implied, opsoperand::none)},

    {0xea, Operation(ops::nop, opsgroup::other, addressMode::implied, opsoperand::none)},

    {0x00, Operation(ops::brk, opsgroup::other, addressMode::implied, opsoperand::none)},
  };

  struct Instruction {
    Instruction(Operation operation, int dataLength = 0,
                uint8_t dataLsb = 0, uint8_t dataMsb = 0)
      : operation(operation), dataLsb(dataLsb),
        dataMsb(dataMsb), dataLength(dataLength) {}

    std::ostringstream ostream() {
      std::ostringstream os;
      os << "Instruction("
         << "LSB=" << Utils::sstreamHexByte(dataLsb).str() << ", "
         << "MSB=" << Utils::sstreamHexByte(dataMsb).str() << ", "
         << "dataLength=" << dataLength
         << ")";
      return os;
    }

    Operation operation;
    uint8_t dataLsb; // least significant byte
    uint8_t dataMsb; // most significant byte
    int dataLength;
  };

  using Instructions = std::vector<Instruction>;
}

#endif /* __Instruction__ */
