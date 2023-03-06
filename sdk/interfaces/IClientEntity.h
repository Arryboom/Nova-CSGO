#pragma once
#include "IClientUnknown.h"
#include "IClientRenderable.h"
#include "IClientNetworkable.h"
#include "IClientThinkable.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable {
public:
	virtual void Release(void) = 0;
};