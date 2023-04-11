#include "hooks.h"
#include "minhook/minhook.h"
#include "utils.h"
#include "imgui/imgui_impl_dx9.h"
#include "hacks/misc.h"
#include "hacks/visuals.h"
#include "gui.h"
#include "x86RetSpoof.h"
#include <stdexcept>
#include <intrin.h>
#include <algorithm>

void hooks::Setup() {
	clientMode = **(void***)((*(unsigned int**)g_BaseClientDLL)[10] + 0x5);

	if (!clientMode)
		throw std::runtime_error("Please wait a bit longer before injecting.");

	if (MH_Initialize())
		throw std::runtime_error("Failed to initialize MinHook.");

	if (MH_CreateHook(
		utils::VirtualFunctionA(gui::device, 42),
		&EndScene,
		(void**)&EndSceneOriginal
	)) throw std::runtime_error("Failed to hook EndScene.");

	if (MH_CreateHook(
		utils::VirtualFunctionA(gui::device, 16),
		&Reset,
		(void**)&ResetOriginal
	)) throw std::runtime_error("Failed to hook Reset.");

	if (MH_CreateHook(
		utils::VirtualFunctionA(clientMode, 24),
		&CreateMove,
		(void**)&CreateMoveOriginal
	)) throw std::runtime_error("Failed to hook CreateMove.");

	if (MH_CreateHook(
		utils::VirtualFunctionA(g_BaseClientDLL, 37),
		&FrameStageNotify,
		(void**)&FrameStageNotifyOriginal
	)) throw std::runtime_error("Failed to hook FrameStageNotify.");

	if (MH_CreateHook(
		utils::VirtualFunctionA(g_Surface, 67),
		&LockCursor,
		(void**)&LockCursorOriginal
	)) throw std::runtime_error("Failed to hook LockCursor.");

	if (MH_CreateHook(
		utils::VirtualFunctionA(g_ViewRender, 41),
		&RenderSmokeOverlay,
		(void**)&RenderSmokeOverlayOriginal
	)) throw std::runtime_error("Failed to hook RenderSmokeOverlay.");

	if (MH_EnableHook(MH_ALL_HOOKS))
		throw std::runtime_error("Failed to enable hooks.");

	gui::DestroyDirectX();
}

void hooks::Destroy() noexcept {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

long __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept {
	static void* returnAddress = _ReturnAddress();
	long result = EndSceneOriginal(device, device);

	if (_ReturnAddress() == returnAddress)
		return result;

	if (!gui::setup)
		gui::SetupMenu(device);

	gui::Render();

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept {
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}

bool __stdcall hooks::CreateMove(float frameTime, UserCmd* cmd) noexcept {
	bool result = x86RetSpoof::invokeThiscall<bool>(
		(unsigned int)clientMode, 
		(unsigned int)CreateMoveOriginal, 
		clientGadget, 
		frameTime, 
		cmd
	);

	if (!cmd->commandNumber)
		return result;

	g_LocalPlayer = g_ClientEntityList->GetClientEntity(g_VEngineClient->GetLocalPlayer());

	for (int i = 1; i <= 64; i++) {
		C_BasePlayer* player = g_ClientEntityList->GetClientEntity(i);

		if (player && player != g_LocalPlayer)
			PlayerInfo::Update(&visuals::g_PlayerInfoList[i - 1], player);
		else
			visuals::g_PlayerInfoList[i - 1].active = false;
	}
	
	g_GlobalVarsBase->ServerTime(cmd);
	misc::AutoJump(cmd);
	misc::AutoFire(cmd);
	misc::QuickStop(cmd);
	misc::InfiniteStamina(cmd);

	cmd->forwardMove = std::clamp(cmd->forwardMove, -450.0f, 450.0f);
	cmd->sideMove = std::clamp(cmd->sideMove, -450.0f, 450.0f);
	cmd->upMove = std::clamp(cmd->upMove, -320.0f, 320.0f);

	cmd->viewPoint.normalize();
	cmd->viewPoint.x = std::clamp(cmd->viewPoint.x, -89.f, 89.f);
	cmd->viewPoint.y = std::clamp(cmd->viewPoint.y, -180.f, 180.f);
	cmd->viewPoint.z = 0.f;

	return false;
}

void __stdcall hooks::FrameStageNotify(FrameStage stage) noexcept {
	if (g_VEngineClient->IsInGame())
		visuals::ModifySmoke(stage);

	return x86RetSpoof::invokeThiscall<void>(
		(unsigned int)g_BaseClientDLL,
		(unsigned int)FrameStageNotifyOriginal,
		clientGadget,
		stage
	);
}

void __stdcall hooks::LockCursor() noexcept {
	if (gui::open)
		return g_Surface->UnlockCursor();
	
	return x86RetSpoof::invokeThiscall<void>(
		(unsigned int)g_Surface,
		(unsigned int)LockCursorOriginal,
		clientGadget
	);
}

void __stdcall hooks::RenderSmokeOverlay(bool update) noexcept {
	if (gui::config::visuals::smoke_type == 1 || gui::config::visuals::smoke_type == 2)
		g_ViewRender->smokeOverlayAmount = 0.f;
	else {
		return x86RetSpoof::invokeThiscall<void>(
			(unsigned int)g_ViewRender,
			(unsigned int)RenderSmokeOverlayOriginal,
			clientGadget,
			update
		);
	}
}