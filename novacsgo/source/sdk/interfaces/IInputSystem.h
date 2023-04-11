#pragma once
#include "../../utils.h"

class IInputSystem {
public:
	void EnableInput(bool bEnable) {
		typedef void(__thiscall* oEnableInput)(void*, bool);
		return utils::VirtualFunctionB<oEnableInput>(this, 11)(this, bEnable);
	}

	void ResetInputState() {
		typedef void(__thiscall* oResetInputState)(void*);
		return utils::VirtualFunctionB<oResetInputState>(this, 39)(this);
	}
};