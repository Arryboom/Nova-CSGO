#pragma once
#include "../WeaponInfo.h"
#include "../../utils.h"

class IWeaponSystem {
public:
	WeaponInfo* GetWeaponData(unsigned int index) {
		typedef WeaponInfo* (__thiscall* oGetWeaponData)(void*, unsigned int);
		return utils::VirtualFunctionB<oGetWeaponData>(this, 2)(this, index);
	}
};