#pragma once
#include "C_BaseCombatWeapon.h"
#include "Matrix.h"
#include "Studio.h"
#include "interfaces/IVEngineClient.h"
#include "../interfaces.h"
#include "../sdk/PlayerInfo.h"
#include "../gui.h"

class PlayerInfo {
public:
	bool active;

	char name[128];
	int health;
	int team;
	bool dormant;
	C_BaseCombatWeapon* weapon;
	WeaponInfo* weaponInfo;
	Matrix3x4 boneMatrices[256];
	StudioHitboxSet* hitboxSet;

	static void Update(PlayerInfo* playerInfo, C_BasePlayer* player) {
		playerInfo->active = true;

		CSGOPlayerInfo csgoPlayerInfo;
		g_VEngineClient->GetPlayerInfo(player->EntityIndex(), &csgoPlayerInfo);

		strcpy_s(playerInfo->name, 128, csgoPlayerInfo.szName);
		playerInfo->health = player->m_iHealth();
		playerInfo->team = player->m_iTeamNum();
		playerInfo->dormant = player->IsDormant();
		playerInfo->weapon = player->GetActiveWeapon();

		if (playerInfo->weapon)
			playerInfo->weaponInfo = g_WeaponSystem->GetWeaponData((unsigned int)playerInfo->weapon->m_iItemDefinitionIndex());

		if (gui::config::esp::master_switch) // setupbones fucks your fps so we dont wanna do it when we dont need it
			player->SetupBones(playerInfo->boneMatrices, 256, 0x100, g_GlobalVarsBase->curtime);

		const Model* model = player->GetModel();
		if (!model)
			return;

		StudioHdr* studioModel = g_VModelInfoClient->GetStudioModel(model);
		if (!studioModel)
			return;

		StudioHitboxSet* hitboxSet = studioModel->GetHitboxSet(player->m_nHitboxSet());
		if (!hitboxSet)
			return;

		playerInfo->hitboxSet = hitboxSet;
	}
};