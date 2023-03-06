#pragma once

namespace utils {
    inline constexpr unsigned int base = 0x811C9DC5;
    inline constexpr unsigned int prime = 0x1000193;

    constexpr float DEG2RAD(float degrees) noexcept {
        return degrees * (3.14159f / 180.f);
    }

    constexpr float RAD2DEG(float radians) noexcept { 
        return radians * (180.f / 3.14159f);
    }

    constexpr void* VirtualFunctionA(void* thisPointer, unsigned int index) noexcept {
        return (*(void***)(thisPointer))[index];
    }

    template< typename Function >
    constexpr Function VirtualFunctionB(void* thisPointer, unsigned int index) noexcept {
        return (*(Function**)(thisPointer))[index];
    }

    unsigned int HashConst(const char* data, const unsigned int value = base) noexcept;
    unsigned int Hash(const char* data) noexcept;
    unsigned char* PatternScan(const char* moduleName, const char* signature) noexcept;
}