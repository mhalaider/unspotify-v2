#include "utils.hpp"

std::uintptr_t utils::pattern_scan(void* module_address, const char* signature)
{
    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);

        for(auto current = start; current < end; ++current) {
            if(*current == '?') {
                ++current;
                if(*current == '?')
                    ++current;
                bytes.push_back(-1);
            } else {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
        };

    auto dos_header = static_cast<PIMAGE_DOS_HEADER>(module_address);
    auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(static_cast<std::uint8_t*>(module_address) + dos_header->e_lfanew);

    auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    auto pattern_bytes = pattern_to_byte(signature);
    auto scan_bytes = static_cast<std::uint8_t*>(module_address);

    auto pattern_bytes_size = pattern_bytes.size();
    auto pattern_data = pattern_bytes.data();

    for(auto i = 0ul; i < size_of_image - pattern_bytes_size; ++i) {
        bool found = true;
        for(auto j = 0ul; j < pattern_bytes_size; ++j) {
            if(scan_bytes[i + j] != pattern_data[j] && pattern_data[j] != -1) {
                found = false;
                break;
            }
        }
        if(found) {
            return reinterpret_cast<std::uintptr_t>(&scan_bytes[i]);
        }
    }
    return 0;
}

std::uintptr_t utils::get_abs_call(std::uintptr_t address, std::uint32_t pre, std::uint32_t post)
{
    return address + *reinterpret_cast<std::int32_t*>(address + pre) + post;
}
