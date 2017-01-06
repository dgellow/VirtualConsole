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
    rts,
  };

  const std::string opsnames[] = {
    "org",
    "ldx",
    "ldy",
    "lda",
    "rts",
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
