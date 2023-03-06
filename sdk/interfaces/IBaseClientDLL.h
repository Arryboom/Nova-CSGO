#pragma once

class ClientClass;

class IBaseClientDLL {
public:
    virtual int              Connect(void* appSystemFactory, void* pGlobals) = 0;
    virtual int              Disconnect(void) = 0;
    virtual int              Init(void* appSystemFactory, void* pGlobals) = 0;
    virtual void             PostInit() = 0;
    virtual void             Shutdown(void) = 0;
    virtual void             LevelInitPreEntity(char const* pMapName) = 0;
    virtual void             LevelInitPostEntity() = 0;
    virtual void             LevelShutdown(void) = 0;
    virtual ClientClass*     GetAllClasses(void) = 0;
};