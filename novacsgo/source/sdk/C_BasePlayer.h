#pragma once
#include "C_BaseEntity.h"
#include "C_BaseCombatWeapon.h"
#include "../utils.h"

class C_BasePlayer : public C_BaseEntity {
public:
	NETVAR(m_iHealth, "CBasePlayer->m_iHealth", int)
	NETVAR(m_fFlags, "CBasePlayer->m_fFlags", int)
	NETVAR(m_nTickBase, "CBasePlayer->m_nTickBase", int)
	NETVAR(m_vecVelocity, "CBasePlayer->m_vecVelocity[0]", Vector)
	NETVAR(m_nHitboxSet, "CBaseAnimating->m_nHitboxSet", int)

	bool IsAlive() {
		typedef bool(__thiscall* oIsAlive)(void*);
		return utils::VirtualFunctionB<oIsAlive>(this, 156)(this);
	}

	C_BaseCombatWeapon* GetActiveWeapon() {
		typedef C_BaseCombatWeapon* (__thiscall* oGetActiveWeapon)(void*);
		return utils::VirtualFunctionB<oGetActiveWeapon>(this, 268)(this);
	}
};