#include "visuals.h"
#include "../gui.h"
#include "../sdk/Matrix.h"
#include "../interfaces.h"
#include "../imgui/imgui_internal.h"
#include "../sdk/constants/Hitbox.h"
#include "../sdk/C_Material.h"
#include <Windows.h>
#include <iostream>

void visuals::DrawESP() noexcept {
	for (int i = 1; i <= 64; i++) {
		PlayerInfo player = g_PlayerInfoList[i - 1];

		if (!player.active || !player.boneMatrices || player.health == 0)
			continue;

		if (!gui::config::esp::enemy_dormant && player.dormant)
			continue;

		StudioHitboxSet* hitboxSet = player.hitboxSet;
		if (!hitboxSet)
			continue;

		const StudioBBox* head = hitboxSet->GetHitbox(0);
		const StudioBBox* pelvis = hitboxSet->GetHitbox(2);

		Vector headMin = transform(head->bbMin, player.boneMatrices[head->bone]);
		Vector headMax = transform(head->bbMax, player.boneMatrices[head->bone]);
		Vector headPos = (headMin + headMax) / 2.f;
		Vector pelvisMin = transform(pelvis->bbMin, player.boneMatrices[pelvis->bone]);
		Vector pelvisMax = transform(pelvis->bbMax, player.boneMatrices[pelvis->bone]);
		Vector pelvisPos = (pelvisMin + pelvisMax) / 2.f;

		ImVec2 pelvisScreen, headScreen;
		if (visuals::WorldToScreen(pelvisPos, pelvisScreen) && visuals::WorldToScreen(headPos, headScreen)) {
			if (player.team == g_LocalPlayer->m_iTeamNum()) {
				if (gui::config::esp::teammate_name)
					DrawName(player, pelvisScreen, headScreen);

				if (gui::config::esp::teammate_box)
					DrawBoundingBox(player, pelvisScreen, headScreen);

				if (gui::config::esp::teammate_health_bar)
					DrawHealthBar(player, pelvisScreen, headScreen);

				if (gui::config::esp::teammate_ammo_bar)
					DrawAmmoBar(player, pelvisScreen, headScreen);

				if (gui::config::esp::teammate_weapon_name)
					DrawWeaponName(player, pelvisScreen, headScreen);
			} else {
				if (gui::config::esp::enemy_name)
					DrawName(player, pelvisScreen, headScreen);

				if (gui::config::esp::enemy_box)
					DrawBoundingBox(player, pelvisScreen, headScreen);

				if (gui::config::esp::enemy_health_bar)
					DrawHealthBar(player, pelvisScreen, headScreen);

				if (gui::config::esp::enemy_ammo_bar)
					DrawAmmoBar(player, pelvisScreen, headScreen);

				if (gui::config::esp::enemy_weapon_name)
					DrawWeaponName(player, pelvisScreen, headScreen);
			}
		}
	}
}

void visuals::DrawName(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept {
	ImVec2 nameSize = ImGui::CalcTextSize(player.name);

	float distance = pelvisScreen.y - headScreen.y;
	if (distance < 0) distance = -distance;

	ImVec2 screenPositionMin = ImFloor(ImVec2(
		pelvisScreen.x - distance * 0.75f,
		pelvisScreen.y - distance * 1.3f
	));

	ImVec2 screenPositionMax = ImFloor(ImVec2(
		pelvisScreen.x + distance * 0.75f,
		pelvisScreen.y + distance * 1.3f
	));

	ImVec2 screenPosition = ImFloor(ImVec2(
		(screenPositionMin.x + screenPositionMax.x) / 2.f - nameSize.x / 2.f,
		screenPositionMin.y - nameSize.y - 2.f
	));

	ImVec2 screenPositionOutline = ImFloor(ImVec2(screenPosition.x + 1.f, screenPosition.y + 1.f));

	ImU32 color; 
	ImU32 outlineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	if (player.team == g_LocalPlayer->m_iTeamNum()) {
		 color = ImGui::ColorConvertFloat4ToU32(ImVec4(
			gui::config::esp::teammate_name_color[0], 
			gui::config::esp::teammate_name_color[1], 
			gui::config::esp::teammate_name_color[2],
			1.f
		));
	} else {
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(
			gui::config::esp::enemy_name_color[0],
			gui::config::esp::enemy_name_color[1],
			gui::config::esp::enemy_name_color[2],
			1.f
		));
	}

	ImGui::GetBackgroundDrawList()->AddText(screenPositionOutline, outlineColor, player.name);
	ImGui::GetBackgroundDrawList()->AddText(screenPosition, color, player.name);
}

void visuals::DrawBoundingBox(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept {
	float distance = pelvisScreen.y - headScreen.y;
	if (distance < 0) distance = -distance;

	ImVec2 screenPositionMin = ImFloor(ImVec2(
		pelvisScreen.x - distance * 0.75f,
		pelvisScreen.y - distance * 1.3f
	));

	ImVec2 screenPositionMax = ImFloor(ImVec2(
		pelvisScreen.x + distance * 0.75f,
		pelvisScreen.y + distance * 1.3f
	));

	ImU32 color;
	ImU32 outlineColor;

	if (player.team == g_LocalPlayer->m_iTeamNum()) {
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(
			gui::config::esp::teammate_box_color[0], 
			gui::config::esp::teammate_box_color[1],
			gui::config::esp::teammate_box_color[2],
			1.f
		));

		outlineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	}
	else {
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(
			gui::config::esp::enemy_box_color[0],
			gui::config::esp::enemy_box_color[1],
			gui::config::esp::enemy_box_color[2],
			1.f
		));

		outlineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	}

	if (player.dormant) {
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));
		outlineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	}

	ImGui::GetBackgroundDrawList()->AddRect(screenPositionMin, screenPositionMax, outlineColor, 0.f, ImDrawFlags_None, 2.f);
	ImGui::GetBackgroundDrawList()->AddRect(screenPositionMin, screenPositionMax, color);
}

void visuals::DrawHealthBar(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept {
	float distance = pelvisScreen.y - headScreen.y;
	if (distance < 0) distance = -distance;

	ImVec2 screenPositionTopMax = ImFloor(ImVec2(
		pelvisScreen.x - distance * 0.75f - 3.f,
		pelvisScreen.y - distance * 1.3f
	));

	ImVec2 screenPositionBottom = ImFloor(ImVec2(
		pelvisScreen.x - distance * 0.75f - 3.f,
		pelvisScreen.y + distance * 1.3f
	));

	int health = player.health;
	float barDistance = screenPositionBottom.y - screenPositionTopMax.y;
	float sizeGradient = health * barDistance / 100.f;

	ImVec2 screenPositionTop = ImFloor(ImVec2(
		screenPositionBottom.x,
		screenPositionBottom.y - sizeGradient
	));

	ImU32 outlineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.5f));
	ImU32 color;
	if (!player.dormant)
		color = ImGui::ColorConvertFloat4ToU32(ImVec4((100.f - health) / 100.f, health / 100.f, 0.f, 1.f));
	else
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(screenPositionTopMax.x - 2.f, screenPositionTopMax.y - 1.f), ImVec2(screenPositionBottom.x + 1.f, screenPositionBottom.y + 1.f), outlineColor);
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(screenPositionTop.x - 1.f, screenPositionTop.y), screenPositionBottom, color);
}

void visuals::DrawAmmoBar(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept {
	C_BaseCombatWeapon* weapon = player.weapon;
	if (!weapon)
		return;

	WeaponInfo* weaponInfo = player.weaponInfo;
	if (!weaponInfo)
		return;

	float distance = pelvisScreen.y - headScreen.y;
	if (distance < 0) distance = -distance;

	ImVec2 screenPositionLeft = ImFloor(ImVec2(
		pelvisScreen.x - distance * 0.75f,
		pelvisScreen.y + distance * 1.3f + 3.f
	));

	ImVec2 screenPositionRightMax = ImFloor(ImVec2(
		pelvisScreen.x + distance * 0.75f,
		pelvisScreen.y + distance * 1.3f + 4.f
	));

	int ammo = weapon->m_iClip1();
	int maxAmmo = weaponInfo->maxClip;
	float barDistance = screenPositionRightMax.x - screenPositionLeft.x;
	float sizeGradient = ammo * barDistance / maxAmmo;

	if (ammo < 0)
		return;

	ImVec2 screenPositionRight = ImFloor(ImVec2(
		screenPositionLeft.x + sizeGradient,
		screenPositionRightMax.y
	));

	ImU32 outlineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 0.5f));
	ImU32 color;
	if (player.team == g_LocalPlayer->m_iTeamNum()) {
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(
			gui::config::esp::teammate_ammo_bar_color[0],
			gui::config::esp::teammate_ammo_bar_color[1],
			gui::config::esp::teammate_ammo_bar_color[2],
			1.f
		));
	}
	else {
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(
			gui::config::esp::enemy_ammo_bar_color[0],
			gui::config::esp::enemy_ammo_bar_color[1],
			gui::config::esp::enemy_ammo_bar_color[2],
			1.f
		));
	}

	if (player.dormant)
		color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));

	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(screenPositionLeft.x - 1.f, screenPositionLeft.y - 1.f), ImVec2(screenPositionRightMax.x + 1.f, screenPositionRightMax.y + 1.f), outlineColor);
	ImGui::GetBackgroundDrawList()->AddRectFilled(screenPositionLeft, screenPositionRight, color);
}

void visuals::DrawWeaponName(PlayerInfo player, ImVec2 pelvisScreen, ImVec2 headScreen) noexcept {
	C_BaseCombatWeapon* weapon = player.weapon;
	if (!weapon)
		return;

	WeaponInfo* weaponInfo = player.weaponInfo;
	if (!weaponInfo)
		return;

	std::string weaponName = weaponInfo->name;
	weaponName = weaponName.substr(13, weaponName.size());
	for (unsigned int i = 0; i < weaponName.size(); i++)
		weaponName[i] = std::toupper(weaponName[i]);

	float distance = pelvisScreen.y - headScreen.y;
	if (distance < 0) distance = -distance;

	ImVec2 screenPositionLeft = ImFloor(ImVec2(
		pelvisScreen.x - distance * 0.75f,
		pelvisScreen.y + distance * 1.3f
	));

	ImVec2 screenPositionRight = ImFloor(ImVec2(
		pelvisScreen.x + distance * 0.75f,
		pelvisScreen.y + distance * 1.3f
	));

	ImU32 outlineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 1.f));
	ImU32 color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, 1.f));
	ImVec2 weaponNameSize = ImGui::CalcTextSize(weaponName.c_str());

	ImVec2 screenPositionMiddle;
	if (player.team == g_LocalPlayer->m_iTeamNum()) {
		if (gui::config::esp::teammate_ammo_bar && weapon->m_iClip1() > 0) {
			screenPositionMiddle = ImFloor(ImVec2(
				(screenPositionLeft.x + screenPositionRight.x) / 2.f - weaponNameSize.x / 2.f,
				screenPositionRight.y + 4.f
			));
		} else {
			screenPositionMiddle = ImFloor(ImVec2(
				(screenPositionLeft.x + screenPositionRight.x) / 2.f - weaponNameSize.x / 2.f,
				screenPositionRight.y
			));
		}
	} else {
		if (gui::config::esp::enemy_ammo_bar && weapon->m_iClip1() > 0) {
			screenPositionMiddle = ImFloor(ImVec2(
				(screenPositionLeft.x + screenPositionRight.x) / 2.f - weaponNameSize.x / 2.f,
				screenPositionRight.y + 4.f
			));
		} else {
			screenPositionMiddle = ImFloor(ImVec2(
				(screenPositionLeft.x + screenPositionRight.x) / 2.f - weaponNameSize.x / 2.f,
				screenPositionRight.y 
			));
		}
	}

	ImGui::GetBackgroundDrawList()->AddText(ImVec2(screenPositionMiddle.x + 1.f, screenPositionMiddle.y + 1.f), outlineColor, weaponName.c_str());
	ImGui::GetBackgroundDrawList()->AddText(screenPositionMiddle, color, weaponName.c_str());
}

bool visuals::WorldToScreen(const Vector& worldPosition, ImVec2& screenPosition) noexcept {
	const float w = g_ScreenMatrix._41 * worldPosition.x + g_ScreenMatrix._42 * worldPosition.y + g_ScreenMatrix._43 * worldPosition.z + g_ScreenMatrix._44;
	if (w < 0.001f)
		return false;

	screenPosition.x = ImGui::GetIO().DisplaySize.x / 2.f;
	screenPosition.y = ImGui::GetIO().DisplaySize.y / 2.f;
	screenPosition.x *= 1.f + (g_ScreenMatrix._11 * worldPosition.x + g_ScreenMatrix._12 * worldPosition.y + g_ScreenMatrix._13 * worldPosition.z + g_ScreenMatrix._14) / w;
	screenPosition.y *= 1.f - (g_ScreenMatrix._21 * worldPosition.x + g_ScreenMatrix._22 * worldPosition.y + g_ScreenMatrix._23 * worldPosition.z + g_ScreenMatrix._24) / w;
	screenPosition = ImFloor(screenPosition);

	return true;
}

void visuals::ModifySmoke(FrameStage stage) noexcept {
	if (stage != FrameStage::RENDER_START)
		return;

	static constexpr const char* smokeMaterials[4]{
		"particle/vistasmokev1/vistasmokev1_emods",
		"particle/vistasmokev1/vistasmokev1_emods_impactdust",
		"particle/vistasmokev1/vistasmokev1_fire",
		"particle/vistasmokev1/vistasmokev1_smokegrenade"
	};

	for (const char* materialName : smokeMaterials) {
		Material* material = g_MaterialSystem->FindMaterial(materialName);
		
		material->SetMaterialVarFlag(MaterialVarFlag::NO_DRAW, (stage == FrameStage::RENDER_START && gui::config::visuals::smoke_type == 1));
		material->SetMaterialVarFlag(MaterialVarFlag::WIREFRAME, (stage == FrameStage::RENDER_START && gui::config::visuals::smoke_type == 2));
	}
}