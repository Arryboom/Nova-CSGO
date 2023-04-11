#pragma once
#include "Vector.h"
#include "Matrix.h"

struct StudioBBox {
    int bone;
    int group;
    Vector bbMin;
    Vector bbMax;
    int hitboxNameIndex;
    Vector offsetOrientation;
    float capsuleRadius;
    int	unused[4];
};

struct StudioHitboxSet {
    int    sznameindex;
    int    numhitboxes;
    int    hitboxindex;

    const char* GetName()
    {
        if (!sznameindex) return nullptr;
        return (const char*)((uint8_t*)this + sznameindex);
    }

    StudioBBox* GetHitbox(int i)
    {
        if (i > numhitboxes) return nullptr;
        return (StudioBBox*)((uint8_t*)this + hitboxindex) + i;
    }
};

struct StudioBone {
    int                    sznameindex;
    inline char* const    pszName(void) const { return ((char*)this) + sznameindex; }
    int                    parent;
    int                    bonecontroller[6];    // bone controller index, -1 == none
    Vector                 pos;
    float             quat[4];
    float            rot[3];
    // compression scale
    Vector                 posscale;
    Vector                 rotscale;

    Matrix3x4            poseToBone;
    float             qAlignment[4];
    int                    flags;
    int                    proctype;
    int                    procindex;
    mutable int            physicsbone;
    inline void* pProcedure() const { if (procindex == 0) return NULL; else return  (void*)(((unsigned char*)this) + procindex); };
    int                    surfacepropidx;
    inline char* const    pszSurfaceProp(void) const { return ((char*)this) + surfacepropidx; }
    inline int             GetSurfaceProp(void) const { return surfacepropLookup; }

    int                    contents;
    int                    surfacepropLookup;
    int                    m_iPad01[7];

    StudioBone() {}
private:
    // No copy constructors allowed
    StudioBone(const StudioBone& vOther);
};

class StudioHdr {
public:
    __int32 id;                     //0x0000 
    __int32 version;                //0x0004 
    long    checksum;               //0x0008 
    char    szName[64];             //0x000C 
    __int32 length;                 //0x004C 
    Vector  vecEyePos;              //0x0050 
    Vector  vecIllumPos;            //0x005C 
    Vector  vecHullMin;             //0x0068 
    Vector  vecHullMax;             //0x0074 
    Vector  vecBBMin;               //0x0080 
    Vector  vecBBMax;               //0x008C 
    __int32 flags;                  //0x0098 
    __int32 numbones;               //0x009C 
    __int32 boneindex;              //0x00A0 
    __int32 numbonecontrollers;     //0x00A4 
    __int32 bonecontrollerindex;    //0x00A8 
    __int32 numhitboxsets;          //0x00AC 
    __int32 hitboxsetindex;         //0x00B0 
    __int32 numlocalanim;           //0x00B4 
    __int32 localanimindex;         //0x00B8 
    __int32 numlocalseq;            //0x00BC 
    __int32 localseqindex;          //0x00C0 
    __int32 activitylistversion;    //0x00C4 
    __int32 eventsindexed;          //0x00C8 
    __int32 numtextures;            //0x00CC 
    __int32 textureindex;           //0x00D0

    StudioHitboxSet* GetHitboxSet(int i) {
        if (i > numhitboxsets) return nullptr;
        return (StudioHitboxSet*)((uint8_t*)this + hitboxsetindex) + i;
    }

    const StudioBone* GetBone(int i) {
        if (i > numbones) return nullptr;
        return (StudioBone*)((uint8_t*)this + boneindex) + i;
    }

};//Size=0x00D4

struct Model {
    void* handle;
    char name[260];
    int	loadFlags;
    int	serverCount;
    int	type;
    int	flags;
    Vector mins, maxs;
};

struct ModelRenderInfo {
    Vector origin;
    Vector angles;
    char pad[4];
    void* renderable;
    const Model* model;
    const Matrix3x4* modelToWorld;
    const Matrix3x4* lightingOffset;
    const Vector* lightingOrigin;
    int flags;
    int entityIndex;
};