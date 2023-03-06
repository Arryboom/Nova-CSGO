#pragma once
#include "../../utils.h"
#include "../Vector.h"

struct Matrix4x4;

struct CSGOPlayerInfo {
	__int64         unknown;            //0x0000 
	union {
		__int64       steamID64;          //0x0008 - SteamID64
		struct {
			__int32     xuid_low;
			__int32     xuid_high;
		};
	};

	char            szName[128];        //0x0010 - Player Name
	int             userId;             //0x0090 - Unique Server Identifier
	char            szSteamID[20];      //0x0094 - STEAM_X:Y:Z
	char            pad_0x00A8[0x10];   //0x00A8
	unsigned long   iSteamID;           //0x00B8 - SteamID 
	char            szFriendsName[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customfiles[4];
	unsigned char   filesdownloaded;
};

class IVEngineClient {
public:
	void GetScreenSize(int& width, int& height) {
		typedef void(__thiscall* oGetScreenSize)(void*, int&, int&);
		return utils::VirtualFunctionB<oGetScreenSize>(this, 5)(this, width, height);
	}

	bool GetPlayerInfo(int ent_num, CSGOPlayerInfo* pinfo) {
		typedef bool(__thiscall* oGetPlayerInfo)(void*, int, CSGOPlayerInfo*);
		return utils::VirtualFunctionB<oGetPlayerInfo>(this, 8)(this, ent_num, pinfo);
	}

	int GetLocalPlayer(void) {
		typedef int(__thiscall* oGetLocalPlayer)(void*);
		return utils::VirtualFunctionB<oGetLocalPlayer>(this, 12)(this);
	}

	void GetViewAngles(Vector* va) {
		typedef void(__thiscall* oGetViewAngles)(void*, Vector*);
		return utils::VirtualFunctionB<oGetViewAngles>(this, 19)(this, va);
	}

	void SetViewAngles(Vector* va) {
		typedef void(__thiscall* oSetViewAngles)(void*, Vector*);
		return utils::VirtualFunctionB<oSetViewAngles>(this, 20)(this, va);
	}

	int GetMaxClients(void) {
		typedef int(__thiscall* oGetMaxClients)(void*);
		return utils::VirtualFunctionB<oGetMaxClients>(this, 21)(this);
	}

	bool IsInGame(void) {
		typedef bool(__thiscall* oIsInGame)(void*);
		return utils::VirtualFunctionB<oIsInGame>(this, 26)(this);
	}

	bool IsConnected(void) {
		typedef bool(__thiscall* oIsConnected)(void*);
		return utils::VirtualFunctionB<oIsConnected>(this, 27)(this);
	}

	const Matrix4x4& WorldToScreenMatrix() {
		typedef const Matrix4x4& (__thiscall* oWorldToScreenMatrix)(void*);
		return utils::VirtualFunctionB<oWorldToScreenMatrix>(this, 37)(this);
	}
};