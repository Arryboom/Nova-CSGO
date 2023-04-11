#pragma once
#include "../../utils.h"

class StudioHdr;
struct Model;

class IVModelInfo {
public:
	StudioHdr* GetStudioModel(const Model* mod) {
		typedef StudioHdr* (__thiscall* oGetStudioModel)(void*, const Model*);
		return utils::VirtualFunctionB<oGetStudioModel>(this, 32)(this, mod);
	}
};