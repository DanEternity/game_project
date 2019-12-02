#pragma once

#include <cstdint>

// 32-bit random generator
unsigned int getRand();

std::uint64_t getRand64();

// procedural pseudo random parameter based generator
uint64_t procRandom(uint64_t a = 0, uint64_t b = 0, uint64_t c = 0, uint64_t d = 0);
