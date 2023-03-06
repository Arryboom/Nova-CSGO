#pragma once
#include "sdk/C_BasePlayer.h"
#include "sdk/C_GlobalVarsBase.h"
#include "sdk/interfaces/IBaseClientDLL.h"
#include "sdk/interfaces/IClientEntityList.h"
#include "sdk/interfaces/IVEngineClient.h"
#include "sdk/interfaces/IVModelInfoClient.h"
#include "sdk/interfaces/ISurface.h"
#include "sdk/interfaces/IInputSystem.h"
#include "sdk/interfaces/IMaterial.h"
#include "sdk/interfaces/IWeaponSystem.h"
#include "sdk/ViewRender.h"
#include "sdk/Matrix.h"
#include <Windows.h>

namespace interfaces {
	void* GetInterface(const char* dllName, const char* interfaceName);
	void Setup() noexcept;
}

inline C_BasePlayer* g_LocalPlayer = nullptr;
inline C_GlobalVarsBase* g_GlobalVarsBase = nullptr;

inline IBaseClientDLL* g_BaseClientDLL = nullptr;
inline IClientEntityList* g_ClientEntityList = nullptr;
inline IVEngineClient* g_VEngineClient = nullptr;
inline IVModelInfoClient* g_VModelInfoClient = nullptr;
inline ISurface* g_Surface = nullptr;
inline IInputSystem* g_InputSystem = nullptr;
inline IMaterialSystem* g_MaterialSystem = nullptr;
inline IWeaponSystem* g_WeaponSystem = nullptr;

inline ViewRender* g_ViewRender = nullptr;
inline Matrix4x4& g_ScreenMatrix = *(Matrix4x4*)(*(unsigned int*)(utils::PatternScan("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9") + 3) + 176);