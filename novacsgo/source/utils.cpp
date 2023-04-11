#include "utils.h"
#include <Windows.h>
#include <vector>

unsigned int utils::HashConst(const char* data, const unsigned int value) noexcept {
	return (data[0] == '\0') ? value : HashConst(&data[1], (value ^ unsigned int(data[0])) * prime);
}

unsigned int utils::Hash(const char* data) noexcept {
    unsigned int hashed = base;

    for (unsigned int i = 0U; i < strlen(data); ++i) {
        hashed ^= data[i];
        hashed *= prime;
    }

    return hashed;
}

unsigned char* utils::PatternScan(const char* moduleName, const char* signature) noexcept {
    HMODULE module = GetModuleHandle(moduleName);
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)module;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((unsigned char*)module + dosHeader->e_lfanew);
    unsigned long sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;

    std::vector<int> patternBytes = {};
    for (char* current = (char*)signature; current < (char*)signature + strlen(signature); ++current) {
        if (*current == '?') {
            ++current;

            if (*current == '?')
                ++current;

            patternBytes.push_back(-1);
        }
        else
            patternBytes.push_back(strtoul(current, &current, 16));
    }

    unsigned char* scanBytes = (unsigned char*)module;
    unsigned int patternBytesSize = patternBytes.size();
    int* patternBytesData = patternBytes.data();

    for (unsigned long i = 0UL; i < sizeOfImage - patternBytesSize; ++i) {
        bool found = true;

        for (unsigned long j = 0UL; j < patternBytesSize; ++j) {
            if (scanBytes[i + j] != patternBytesData[j] && patternBytesData[j] != -1) {
                found = false;
                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    return nullptr;
}