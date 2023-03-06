#include "C_GlobalVarsBase.h"
#include "../interfaces.h"

float C_GlobalVarsBase::ServerTime(UserCmd* cmd) const noexcept {
    static int tick;
    static UserCmd* lastCmd;

    if (cmd) {
        if (g_LocalPlayer && (!lastCmd || lastCmd->hasBeenPredicted))
            tick = g_LocalPlayer->m_nTickBase();
        else
            tick++;

        lastCmd = cmd;
    }

    return tick * interval_per_tick;
}