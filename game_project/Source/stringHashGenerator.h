#pragma once

//
// This file contain function to implement switch(string)
//
//
//
//

#include <cstdint>

// FNV-1a hash, 32-bit 
inline constexpr std::uint32_t getHash(const wchar_t* str, std::uint32_t hash = 2166136261UL) {
	return *str ? getHash(str + 1, (hash ^ *str) * 16777619ULL) : hash;
}