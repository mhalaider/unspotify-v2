#pragma once

namespace utils
{
	std::uintptr_t pattern_scan(void* module_address, const char* signature);
	std::uintptr_t get_abs_call(std::uintptr_t address, std::uint32_t pre = 1, std::uint32_t post = 5);
}