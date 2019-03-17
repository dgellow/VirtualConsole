#include <iostream>
#include <math.h>

#include "virtualcpu/Memory.hpp"
#include "virtualcpu/Utils.hpp"

uint8_t Memory::at(uint16_t address) {
	if (address <= ramLastAddress) {
		return ram.at(address);
	} else if (address <= screenLastAddress) {
		return screen.at(address);
	} else {
		throw std::out_of_range("Memory error: address " + std::to_string(address) + " out of range");
	}
}

void Memory::set(uint16_t address, uint8_t value) {
	if (address <= ramLastAddress) {
		ram.set(address, value);
	} else if (address <= screenLastAddress) {
		screen.set(address, value);
	} else {
		throw std::out_of_range("Memory error: address " + std::to_string(address) + " out of range");
	}
}

void Memory::debugPrint(uint16_t from, uint16_t count) {
	std::cout << "==========  Debug memory: from=" << from << ", count=" << count << "  ==========" << std::endl;
	for (auto i = 0; i < count; i++) {
		if (i % 10 == 0) {
			std::cout << Utils::sstreamHexByte(from + i, 4).str() << ": ";
		}

		std::cout << Utils::sstreamHexByte(at(from + i), 4).str() << " ";

		if (i % 10 == 9) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

std::ostringstream Memory::ostream() {
	auto w = 4;
	std::ostringstream os;
	os << "Memory("
	   << "ramLastAddress=" << Utils::sstreamHexByte(ramLastAddress, w).str() << ", "
	   << "screenLastAddress=" << Utils::sstreamHexByte(screenLastAddress, w).str() << ", "
	   << "keyboardAddress=" << Utils::sstreamHexByte(keyboardAddress, w).str() << ", "
	   << "stackStartAddress=" << Utils::sstreamHexByte(stackStartAddress, w).str() << ", "
	   << "stackLastAddress=" << Utils::sstreamHexByte(stackLastAddress, w).str() << ")";
	return os;
}
