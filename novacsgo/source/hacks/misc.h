#pragma once
#include "../sdk/UserCmd.h"
#include "../gui.h"
#include "../interfaces.h"

namespace misc {
	void AutoJump(UserCmd* cmd) noexcept;
	void AutoFire(UserCmd* cmd) noexcept;
	void QuickStop(UserCmd* cmd) noexcept;
	void InfiniteStamina(UserCmd* cmd) noexcept;
}