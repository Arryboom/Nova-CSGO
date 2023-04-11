#pragma once
#include "../../utils.h"

class ISurface {
public:
    void UnlockCursor() {
        typedef void(__thiscall* oUnlockCursor)(void*);
        return utils::VirtualFunctionB<oUnlockCursor>(this, 66)(this);
    }
};