#pragma once
#include "../utils.h"
#include "constants/MaterialVarFlag.h"

class Material {
public:
	const char* GetTextureGroupName() {
		typedef const char* (__thiscall* oGetTextureGroupName)(void*);
		return utils::VirtualFunctionB<oGetTextureGroupName>(this, 1)(this);
	}

	void AlphaModulate(float alpha) {
		typedef void(__thiscall* oAlphaModulate)(void*, float);
		return utils::VirtualFunctionB<oAlphaModulate>(this, 27)(this, alpha);
	}

	void ColorModulate(float r, float g, float b) {
		typedef void(__thiscall* oColorModulate)(void*, float, float, float);
		return utils::VirtualFunctionB<oColorModulate>(this, 28)(this, r, g, b);
	}

	void SetMaterialVarFlag(MaterialVarFlag flag, bool on) {
		typedef void(__thiscall* oSetMaterialVarFlag)(void*, MaterialVarFlag, bool);
		return utils::VirtualFunctionB<oSetMaterialVarFlag>(this, 29)(this, flag, on);
	}

	bool IsPrecached() {
		typedef bool(__thiscall* oIsPrecached)(void*);
		return utils::VirtualFunctionB<oIsPrecached>(this, 70)(this);
	}
};