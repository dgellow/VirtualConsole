#ifndef __Instruction__
#define __Instruction__

#include <map>
#include <string>
#include <vector>

namespace Instruction {
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

  struct Operation {
    Operation() {}

    Operation(ops ops, addressMode addressMode)
      : ops(ops), addressMode(addressMode) {};

    ops ops;
    addressMode addressMode;
  };

  const std::map<uint8_t, Operation> opscodes = {
    {0xad, Operation(ops::lda, addressMode::absolute)},
    {0xbd, Operation(ops::lda, addressMode::absoluteIndexedX)},
    {0xb9, Operation(ops::lda, addressMode::absoluteIndexedY)},
    {0xa9, Operation(ops::lda, addressMode::immediate)},
    {0xa5, Operation(ops::lda, addressMode::zeropage)},
    {0xa1, Operation(ops::lda, addressMode::zeropageIndexedIndirect)},
    {0xb5, Operation(ops::lda, addressMode::zeropageIndexedX)},
    {0xb1, Operation(ops::lda, addressMode::zeropageIndirectIndexed)},

    {0xae, Operation(ops::ldx, addressMode::absolute)},
    {0xbe, Operation(ops::ldx, addressMode::absoluteIndexedY)},
    {0xa2, Operation(ops::ldx, addressMode::immediate)},
    {0xa6, Operation(ops::ldx, addressMode::zeropage)},
    {0xb6, Operation(ops::ldx, addressMode::zeropageIndexedY)},

    {0xac, Operation(ops::ldy, addressMode::absolute)},
    {0xbc, Operation(ops::ldy, addressMode::absoluteIndexedX)},
    {0xa0, Operation(ops::ldy, addressMode::immediate)},
    {0xa4, Operation(ops::ldy, addressMode::zeropage)},
    {0xb4, Operation(ops::ldy, addressMode::zeropageIndexedX)},

    {0x8d, Operation(ops::sta, addressMode::absolute)},
    {0x9d, Operation(ops::sta, addressMode::absoluteIndexedX)},
    {0x99, Operation(ops::sta, addressMode::absoluteIndexedY)},
    {0x85, Operation(ops::sta, addressMode::zeropage)},
    {0x81, Operation(ops::sta, addressMode::zeropageIndexedIndirect)},
    {0x95, Operation(ops::sta, addressMode::zeropageIndexedX)},
    {0x91, Operation(ops::sta, addressMode::zeropageIndirectIndexed)},

    {0x8e, Operation(ops::stx, addressMode::absolute)},
    {0x86, Operation(ops::stx, addressMode::zeropage)},
    {0x96, Operation(ops::stx, addressMode::zeropageIndexedY)},

    {0x8c, Operation(ops::sty, addressMode::absolute)},
    {0x84, Operation(ops::sty, addressMode::zeropage)},
    {0x94, Operation(ops::sty, addressMode::zeropageIndexedX)},

    {0x6d, Operation(ops::adc, addressMode::absolute)},
    {0x7d, Operation(ops::adc, addressMode::absoluteIndexedX)},
    {0x79, Operation(ops::adc, addressMode::absoluteIndexedY)},
    {0x69, Operation(ops::adc, addressMode::immediate)},
    {0x65, Operation(ops::adc, addressMode::zeropage)},
    {0x61, Operation(ops::adc, addressMode::zeropageIndexedIndirect)},
    {0x75, Operation(ops::adc, addressMode::zeropageIndexedX)},
    {0x71, Operation(ops::adc, addressMode::zeropageIndirectIndexed)},

    {0xed, Operation(ops::sbc, addressMode::absolute)},
    {0xfd, Operation(ops::sbc, addressMode::absoluteIndexedX)},
    {0xf9, Operation(ops::sbc, addressMode::absoluteIndexedY)},
    {0xe9, Operation(ops::sbc, addressMode::immediate)},
    {0xe5, Operation(ops::sbc, addressMode::zeropage)},
    {0xe1, Operation(ops::sbc, addressMode::zeropageIndexedIndirect)},
    {0xf5, Operation(ops::sbc, addressMode::zeropageIndexedX)},
    {0xf1, Operation(ops::sbc, addressMode::zeropageIndirectIndexed)},

    {0xee, Operation(ops::inc, addressMode::absolute)},
    {0xfe, Operation(ops::inc, addressMode::absoluteIndexedX)},
    {0xe6, Operation(ops::inc, addressMode::zeropage)},
    {0xf6, Operation(ops::inc, addressMode::zeropageIndexedX)},

    {0xe8, Operation(ops::inx, addressMode::implied)},

    {0xc8, Operation(ops::iny, addressMode::implied)},

    {0xce, Operation(ops::dec, addressMode::absolute)},
    {0xde, Operation(ops::dec, addressMode::absoluteIndexedX)},
    {0xc6, Operation(ops::dec, addressMode::zeropage)},
    {0xd6, Operation(ops::dec, addressMode::zeropageIndexedX)},

    {0xca, Operation(ops::dex, addressMode::implied)},

    {0x88, Operation(ops::dey, addressMode::implied)},

    {0x0e, Operation(ops::asl, addressMode::absolute)},
    {0x1e, Operation(ops::asl, addressMode::absoluteIndexedX)},
    {0x0a, Operation(ops::asl, addressMode::accumulator)},
    {0x06, Operation(ops::asl, addressMode::zeropage)},
    {0x16, Operation(ops::asl, addressMode::zeropageIndexedX)},

    {0x4e, Operation(ops::lsr, addressMode::absolute)},
    {0x5e, Operation(ops::lsr, addressMode::absoluteIndexedX)},
    {0x4a, Operation(ops::lsr, addressMode::accumulator)},
    {0x46, Operation(ops::lsr, addressMode::zeropage)},
    {0x56, Operation(ops::lsr, addressMode::zeropageIndexedX)},

    {0x2e, Operation(ops::rol, addressMode::absolute)},
    {0x3e, Operation(ops::rol, addressMode::absoluteIndexedX)},
    {0x2a, Operation(ops::rol, addressMode::accumulator)},
    {0x26, Operation(ops::rol, addressMode::zeropage)},
    {0x36, Operation(ops::rol, addressMode::zeropageIndexedX)},

    {0x6e, Operation(ops::ror, addressMode::absolute)},
    {0x7e, Operation(ops::ror, addressMode::absoluteIndexedX)},
    {0x6a, Operation(ops::ror, addressMode::accumulator)},
    {0x66, Operation(ops::ror, addressMode::zeropage)},
    {0x76, Operation(ops::ror, addressMode::zeropageIndexedX)},

    {0x2d, Operation(ops::and_, addressMode::absolute)},
    {0x3d, Operation(ops::and_, addressMode::absoluteIndexedX)},
    {0x39, Operation(ops::and_, addressMode::absoluteIndexedY)},
    {0x29, Operation(ops::and_, addressMode::immediate)},
    {0x25, Operation(ops::and_, addressMode::zeropage)},
    {0x21, Operation(ops::and_, addressMode::zeropageIndexedIndirect)},
    {0x35, Operation(ops::and_, addressMode::zeropageIndexedX)},
    {0x31, Operation(ops::and_, addressMode::zeropageIndirectIndexed)},

    {0x0d, Operation(ops::ora, addressMode::absolute)},
    {0x1d, Operation(ops::ora, addressMode::absoluteIndexedX)},
    {0x19, Operation(ops::ora, addressMode::absoluteIndexedY)},
    {0x09, Operation(ops::ora, addressMode::immediate)},
    {0x05, Operation(ops::ora, addressMode::zeropage)},
    {0x01, Operation(ops::ora, addressMode::zeropageIndexedIndirect)},
    {0x15, Operation(ops::ora, addressMode::zeropageIndexedX)},
    {0x11, Operation(ops::ora, addressMode::zeropageIndirectIndexed)},

    {0x4d, Operation(ops::eor, addressMode::absolute)},
    {0x5d, Operation(ops::eor, addressMode::absoluteIndexedX)},
    {0x59, Operation(ops::eor, addressMode::absoluteIndexedY)},
    {0x49, Operation(ops::eor, addressMode::immediate)},
    {0x45, Operation(ops::eor, addressMode::zeropage)},
    {0x41, Operation(ops::eor, addressMode::zeropageIndexedIndirect)},
    {0x55, Operation(ops::eor, addressMode::zeropageIndexedX)},
    {0x51, Operation(ops::eor, addressMode::zeropageIndirectIndexed)},

    {0xcd, Operation(ops::cmp, addressMode::absolute)},
    {0xdd, Operation(ops::cmp, addressMode::absoluteIndexedX)},
    {0xd9, Operation(ops::cmp, addressMode::absoluteIndexedY)},
    {0xc9, Operation(ops::cmp, addressMode::immediate)},
    {0xc5, Operation(ops::cmp, addressMode::zeropage)},
    {0xc1, Operation(ops::cmp, addressMode::zeropageIndexedIndirect)},
    {0xd5, Operation(ops::cmp, addressMode::zeropageIndexedX)},
    {0xd1, Operation(ops::cmp, addressMode::zeropageIndirectIndexed)},

    {0xec, Operation(ops::cpx, addressMode::absolute)},
    {0xe0, Operation(ops::cpx, addressMode::immediate)},
    {0xe4, Operation(ops::cpx, addressMode::zeropage)},

    {0xcc, Operation(ops::cpy, addressMode::absolute)},
    {0xc0, Operation(ops::cpy, addressMode::immediate)},
    {0xc4, Operation(ops::cpy, addressMode::zeropage)},

    {0x2c, Operation(ops::bit, addressMode::absolute)},
    {0x89, Operation(ops::bit, addressMode::immediate)},
    {0x24, Operation(ops::bit, addressMode::zeropage)},

    {0x90, Operation(ops::bcc, addressMode::relative)},

    {0xb0, Operation(ops::bcs, addressMode::relative)},

    {0xf0, Operation(ops::beq, addressMode::relative)},

    {0x30, Operation(ops::bmi, addressMode::relative)},

    {0xd0, Operation(ops::bne, addressMode::relative)},

    {0x10, Operation(ops::bpl, addressMode::relative)},

    {0x50, Operation(ops::bvc, addressMode::relative)},

    {0x70, Operation(ops::bvs, addressMode::relative)},

    {0xaa, Operation(ops::tax, addressMode::implied)},

    {0x8a, Operation(ops::txa, addressMode::implied)},

    {0xa8, Operation(ops::tay, addressMode::implied)},

    {0x98, Operation(ops::tya, addressMode::implied)},

    {0xba, Operation(ops::tsx, addressMode::implied)},

    {0x9a, Operation(ops::txs, addressMode::implied)},

    {0x48, Operation(ops::pha, addressMode::implied)},

    {0x68, Operation(ops::pla, addressMode::implied)},

    {0x08, Operation(ops::php, addressMode::implied)},

    {0x28, Operation(ops::plp, addressMode::implied)},

    {0x4c, Operation(ops::jmp, addressMode::absolute)},
    // {0x6c, Operation(ops::jmp, addressMode::)}, <== not sure what's the address mode

    {0x20, Operation(ops::jsr, addressMode::absolute)},

    {0x60, Operation(ops::rts, addressMode::implied)},

    {0x40, Operation(ops::rti, addressMode::implied)},

    {0x38, Operation(ops::sec, addressMode::implied)},

    {0xf8, Operation(ops::sed, addressMode::implied)},

    {0x78, Operation(ops::sei, addressMode::implied)},

    {0x18, Operation(ops::clc, addressMode::implied)},

    {0xd8, Operation(ops::cld, addressMode::implied)},

    {0x58, Operation(ops::cli, addressMode::implied)},

    {0xb8, Operation(ops::clv, addressMode::implied)},

    {0xea, Operation(ops::nop, addressMode::implied)},

    {0x00, Operation(ops::brk, addressMode::implied)},
  };

  struct Instruction {
    Instruction(Operation operation, uint8_t dataLsb = 0, uint8_t dataMsb = 0)
      : operation(operation), dataLsb(dataLsb), dataMsb(dataMsb) {}

    Operation operation;
    uint8_t dataLsb; // least significant byte
    uint8_t dataMsb; // most significant byte
  };

  using Instructions = std::vector<Instruction>;
}

#endif /* __Instruction__ */
