//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: KeyValues helpers for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_KVHELPERS_H_
#define _DIRECTORSCUT_KVHELPERS_H_

#include "dxelement.h"

class KvArray : public DxElement
{
public:
    KvArray(const char* name, const char* typeName);
    const char* GetIndexChar(int index);
    bool RemoveElement(int index);
    int GetSize();
    void Clear();
};

class KvStringArray : public KvArray
{
public:
    KvStringArray(const char* name) : KvArray(name, "string_array") {}
    void SetElement(int index, const char* element);
    const char* GetElement(int index);
    void AddElement(const char* element);
};

class KvIntArray : public KvArray
{
public:
    KvIntArray(const char* name) : KvArray(name, "int_array") {}
    void SetElement(int index, int element);
    int GetElement(int index);
    void AddElement(int element);
};

class KvFloatArray : public KvArray
{
public:
    KvFloatArray(const char* name) : KvArray(name, "float_array") {}
    void SetElement(int index, float element);
    float GetElement(int index);
    void AddElement(float element);
};

class KvBoolArray : public KvArray
{
public:
    KvBoolArray(const char* name) : KvArray(name, "bool_array") {}
    void SetElement(int index, bool element);
    bool GetElement(int index);
    void AddElement(bool element);
};

class KvColorArray : public KvArray
{
public:
    KvColorArray(const char* name) : KvArray(name, "color_array") {}
    void SetElement(int index, Color element);
    Color GetElement(int index);
    void AddElement(Color element);
};

class KvDxElementArray : public KvArray
{
public:
    KvDxElementArray(const char* name) : KvArray(name, "element_array") {}
    KvDxElementArray(const char* name, const char* typeName) : KvArray(name, typeName) {}
    virtual void SetElement(int index, DxElement* element);
    virtual DxElement* GetElement(int index);
    virtual void AddElement(DxElement* element);
};


class KvVector : public DxElement
{
public:
    KvVector(const char* name);
    void SetX(float x) { SetFloat("x", x); }
    float GetX() { return GetFloat("x"); }
    void SetY(float y) { SetFloat("y", y); }
    float GetY() { return GetFloat("y"); }
    void SetZ(float z) { SetFloat("z", z); }
    float GetZ() { return GetFloat("z"); }
    void SetVector(Vector vec) { SetX(vec.x); SetY(vec.y); SetZ(vec.z); }
    Vector GetVector() { return Vector(GetX(), GetY(), GetZ()); }
};

class KvQuaternion : public DxElement
{
public:
    KvQuaternion(const char* name);
    void SetX(float x) { SetFloat("x", x); }
    float GetX() { return GetFloat("x"); }
    void SetY(float y) { SetFloat("y", y); }
    float GetY() { return GetFloat("y"); }
    void SetZ(float z) { SetFloat("z", z); }
    float GetZ() { return GetFloat("z"); }
    void SetW(float w) { SetFloat("w", w); }
    float GetW() { return GetFloat("w"); }
    void SetQuaternion(Quaternion quat) { SetX(quat.x); SetY(quat.y); SetZ(quat.z); SetW(quat.w); }
    Quaternion GetQuaternion() { return Quaternion(GetX(), GetY(), GetZ(), GetW()); }
};

class KvQAngle : public DxElement
{
public:
    KvQAngle(const char* name);
    void SetPitch(float pitch) { SetFloat("pitch", pitch); }
    float GetPitch() { return GetFloat("pitch"); }
    void SetYaw(float yaw) { SetFloat("yaw", yaw); }
    float GetYaw() { return GetFloat("yaw"); }
    void SetRoll(float roll) { SetFloat("roll", roll); }
    float GetRoll() { return GetFloat("roll"); }
    void SetX(float x) { SetPitch(x); }
    float GetX() { return GetPitch(); }
    void SetY(float y) { SetYaw(y); }
    float GetY() { return GetYaw(); }
    void SetZ(float z) { SetRoll(z); }
    float GetZ() { return GetRoll(); }
    void SetQAngle(QAngle ang) { SetPitch(ang.x); SetYaw(ang.y); SetRoll(ang.z); }
    QAngle GetQAngle() { return QAngle(GetPitch(), GetYaw(), GetRoll()); }
};

#endif // _DIRECTORSCUT_KvELPERS_H_
