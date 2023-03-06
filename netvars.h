#pragma once
#include "utils.h"
#include "sdk/Recv.h"
#include <unordered_map>

#define NETVAR(functionName, netvar, type) type& functionName() \
{ \
	static auto offset = netvars::netvars[utils::HashConst(netvar)]; \
	return *(type*)((unsigned int)this + offset); \
}

namespace netvars {
	void Setup() noexcept;
	void Dump(const char* baseClass, RecvTable* table, unsigned int offset = 0) noexcept;

	inline std::unordered_map<unsigned int, unsigned int> netvars;
}