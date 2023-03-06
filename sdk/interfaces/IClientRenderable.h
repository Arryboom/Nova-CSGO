#pragma once
#include "../../utils.h"

struct Model;
class Matrix3x4;

class IClientRenderable {
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;

	const Model* GetModel() {
		typedef Model* (__thiscall* oGetModel)(void*);
		return utils::VirtualFunctionB<oGetModel>(this, 8)(this);
	}

	bool SetupBones(Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) {
		typedef bool(__thiscall* oSetupBones)(void*, Matrix3x4*, int, int, float);
		return utils::VirtualFunctionB<oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
};