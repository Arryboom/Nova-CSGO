#pragma once
#include "../netvars.h"
#include "constants/WeaponId.h"
#include "constants/WeaponType.h"
#include "WeaponInfo.h"

class C_BaseCombatWeapon {
public:
	NETVAR(m_flNextPrimaryAttack, "CBaseCombatWeapon->m_flNextPrimaryAttack", float)
	NETVAR(m_iItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex", WeaponId)
	NETVAR(m_iClip1, "CBaseCombatWeapon->m_iClip1", int)

	WeaponType GetWeaponType() {
		typedef WeaponType(__thiscall* oGetWeaponType)(void*);
		return utils::VirtualFunctionB<oGetWeaponType>(this, 455)(this);
	}
};