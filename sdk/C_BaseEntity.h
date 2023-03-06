#pragma once
#include "interfaces/IClientEntity.h"
#include "../netvars.h"
#include "Vector.h"
#include "constants/MoveType.h"
#include "../utils.h"

class C_BaseEntity : public IClientEntity {
public:
	NETVAR(m_bSpotted, "CBaseEntity->m_bSpotted", bool)
	NETVAR(m_iTeamNum, "CBaseEntity->m_iTeamNum", int)
	NETVAR(m_vecOrigin, "CBaseEntity->m_vecOrigin", Vector)
	NETVAR(m_nMoveType, "CBaseEntity->m_nRenderMode", MoveType)

	bool IsPlayer() {
		typedef bool(__thiscall* oIsPlayer)(void*);
		return utils::VirtualFunctionB<oIsPlayer>(this, 158)(this);
	}
};