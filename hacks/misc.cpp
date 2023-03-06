#include "misc.h"
#include "../sdk/C_BaseCombatWeapon.h"
#include <iostream>

void misc::AutoJump(UserCmd* cmd) noexcept {
    if (gui::config::misc::auto_jump && g_LocalPlayer && !(g_LocalPlayer->m_fFlags() & 0x1))
        cmd->buttons &= ~IN_JUMP;
}

void misc::AutoFire(UserCmd* cmd) noexcept {
    if (gui::config::misc::auto_fire && g_LocalPlayer) {
        C_BaseCombatWeapon* activeWeapon = g_LocalPlayer->GetActiveWeapon();

        if (activeWeapon && activeWeapon->m_flNextPrimaryAttack() > g_GlobalVarsBase->ServerTime()) {
            if (activeWeapon->m_iItemDefinitionIndex() == WeaponId::Revolver)
                cmd->buttons &= ~CommandButtons::IN_SECOND_ATTACK;
            else
                cmd->buttons &= ~CommandButtons::IN_ATTACK;
        }
    }
}

void misc::QuickStop(UserCmd* cmd) noexcept {
    if (!gui::config::misc::quick_stop)
        return;

    if (!g_LocalPlayer || !g_LocalPlayer->IsAlive())
        return;

    if (g_LocalPlayer->m_nMoveType() == MoveType::NOCLIP || g_LocalPlayer->m_nMoveType() == MoveType::LADDER || !(g_LocalPlayer->m_fFlags() & 1) || cmd->buttons & CommandButtons::IN_JUMP)
        return;

    if (cmd->buttons & (CommandButtons::IN_MOVELEFT | CommandButtons::IN_MOVERIGHT | CommandButtons::IN_FORWARD | CommandButtons::IN_BACK))
        return;

    const Vector velocity = g_LocalPlayer->m_vecVelocity();
    const float speed = velocity.length2D();
    if (speed < 15.f)
        return;

    Vector direction = velocity.toAngle();
    direction.y = cmd->viewPoint.y - direction.y;

    const Vector negatedDirection = Vector::fromAngle(direction) * -speed;
    cmd->forwardMove = negatedDirection.x;
    cmd->sideMove = negatedDirection.y;
}

void misc::InfiniteStamina(UserCmd* cmd) noexcept {
    if (gui::config::misc::infinite_stamina)
        cmd->buttons |= CommandButtons::IN_BULLRUSH;
}