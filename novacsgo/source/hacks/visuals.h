#pragma once
#include "../sdk/Studio.h"
#include "../sdk/PlayerInfo.h"
#include "../sdk/Vector.h"
#include "../imgui/imgui.h"
#include "../sdk/constants/FrameStage.h"

namespace visuals {
	inline PlayerInfo g_PlayerInfoList[64];

	void DrawESP() noexcept;
	void DrawName(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept;
	void DrawBoundingBox(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept;
	void DrawHealthBar(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept;
	void DrawAmmoBar(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept;
	void DrawWeaponName(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept;
	bool WorldToScreen(const Vector& worldPosition, ImVec2& screenPosition) noexcept;

	void ModifySmoke(FrameStage stage) noexcept;
}