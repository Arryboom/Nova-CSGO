#pragma once
#include "../C_BasePlayer.h"
#include "IMoveHelper.h"
#include "../../utils.h"

class IGameMovement {
public:
    void ProcessMovement(C_BasePlayer* localPlayer, MoveData* moveData) {
        typedef void(__thiscall* oProcessMovement)(void*, C_BasePlayer*, MoveData*);
        return utils::VirtualFunctionB<oProcessMovement>(this, 1)(this, localPlayer, moveData);
    }
};