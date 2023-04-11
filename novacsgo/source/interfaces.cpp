#include "interfaces.h"
#include <stdexcept>

typedef void* (__cdecl* CreateInterfaceFn)(const char* pName, int* pReturnCode);
void* interfaces::GetInterface(const char* dllName, const char* interfaceName) {
	HMODULE handle = GetModuleHandle(dllName);
	if (!handle)
		throw std::runtime_error("Failed to get interfaces.");

	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(handle, "CreateInterface");
	if (!CreateInterface)
		throw std::runtime_error("Failed to get interfaces.");

	int returnCode = 0;
	void* pInterface = CreateInterface(interfaceName, &returnCode);

	return pInterface;
}

void interfaces::Setup() noexcept {
	g_GlobalVarsBase = **(C_GlobalVarsBase***)(utils::PatternScan("client.dll", "A1 ? ? ? ? 5E 8B 40 10") + 1);
	g_ViewRender = **(ViewRender***)(utils::PatternScan("client.dll", "8B 0D ? ? ? ? FF 75 0C 8B 45 08") + 2);

	g_BaseClientDLL = (IBaseClientDLL*)(GetInterface("client.dll", "VClient018"));
	g_ClientEntityList = (IClientEntityList*)(GetInterface("client.dll", "VClientEntityList003"));
	g_VEngineClient = (IVEngineClient*)(GetInterface("engine.dll", "VEngineClient014"));
	g_VModelInfoClient = (IVModelInfoClient*)(GetInterface("engine.dll", "VModelInfoClient004"));
	g_Surface = (ISurface*)(GetInterface("vguimatsurface.dll", "VGUI_Surface031"));
	g_InputSystem = (IInputSystem*)(GetInterface("inputsystem.dll", "InputSystemVersion001"));
	g_MaterialSystem = (IMaterialSystem*)(GetInterface("materialsystem.dll", "VMaterialSystem080"));
	g_WeaponSystem = *(IWeaponSystem**)(utils::PatternScan("client.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0") + 2);
}