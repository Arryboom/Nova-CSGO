#pragma once

class IClientNetworkable;
class IClientUnknown;
class C_BasePlayer;
class CBaseHandle;

class IClientEntityList {
public:
	virtual IClientNetworkable* GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientUnknown*     GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
	virtual C_BasePlayer*       GetClientEntity(int entnum) = 0;
	virtual C_BasePlayer*       GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int					GetHighestEntityIndex(void) = 0;
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};