#pragma once
#include "../../utils.h"

class Material;

class IMaterialSystem {
public:
    Material* FindMaterial(const char* materialName, const char* textureGroupName = nullptr, bool complain = true, const char* complainPrefix = nullptr) {
        typedef Material* (__thiscall* oFindMaterial)(void*, const char*, const char*, bool, const char*);
        return utils::VirtualFunctionB<oFindMaterial>(this, 84)(this, materialName, textureGroupName, complain, complainPrefix);
    }
    
    short FirstMaterial() {
        typedef short(__thiscall* oFirstMaterial)(void*);
        return utils::VirtualFunctionB<oFirstMaterial>(this, 86)(this);
    }

    short NextMaterial(short handle) {
        typedef short(__thiscall* oNextMaterial)(void*, short);
        return utils::VirtualFunctionB<oNextMaterial>(this, 87)(this, handle);
    }

    short InvalidMaterial() {
        typedef short(__thiscall* oInvalidMaterial)(void*);
        return utils::VirtualFunctionB<oInvalidMaterial>(this, 88)(this);
    }

    Material* GetMaterial(short handle) {
        typedef Material* (__thiscall* oGetMaterial)(void*, short);
        return utils::VirtualFunctionB<oGetMaterial>(this, 89)(this, handle);
    }
};