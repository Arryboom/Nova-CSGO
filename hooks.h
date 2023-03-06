#pragma once
#include "sdk/UserCmd.h"
#include "sdk/constants/FrameStage.h"
#include "x86RetSpoof.h"
#include <d3d9.h>

namespace hooks {
	static void* clientMode = nullptr;
	static unsigned int clientGadget = (unsigned int)utils::PatternScan("client.dll", "FF 23");
	static unsigned int engineGadget = (unsigned int)utils::PatternScan("engine.dll", "FF 23");

	void Setup();
	void Destroy() noexcept;

	template <typename ReturnType, typename... Args>
	ReturnType FunctionHook(std::uintptr_t functionAddress, std::uintptr_t gadgetAddress, Args... args) noexcept {
		return invokeThiscall<ReturnType, Args...>(0, functionAddress, gadgetAddress, args...);
	}

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndSceneFn EndSceneOriginal = nullptr;
	long __stdcall EndScene(IDirect3DDevice9* device) noexcept;

	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFn ResetOriginal = nullptr;
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept;

	using CreateMoveFn = bool(__thiscall*)(void*, float, UserCmd*) noexcept;
	inline CreateMoveFn CreateMoveOriginal = nullptr;
	bool __stdcall CreateMove(float frameTime, UserCmd* cmd) noexcept;

	using FrameStageNotifyFn = void(__thiscall*)(void*, FrameStage) noexcept;
	inline FrameStageNotifyFn FrameStageNotifyOriginal = nullptr;
	void __stdcall FrameStageNotify(FrameStage stage) noexcept;

	using LockCursorFn = void(__thiscall*)(void*) noexcept;
	inline LockCursorFn LockCursorOriginal = nullptr;
	void __stdcall LockCursor() noexcept;

	using RenderSmokeOverlayFn = void(__thiscall*)(void*, bool);
	inline RenderSmokeOverlayFn RenderSmokeOverlayOriginal = nullptr;
	void __stdcall RenderSmokeOverlay(bool update) noexcept;
}