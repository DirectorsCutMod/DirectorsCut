//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: KeyValues helpers for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "kvhelpers.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//// Generic Array ////
KvArray::KvArray(const char* name, const char* typeName) : DxElement(name, typeName)
{
    // Array elements should not have a name
    KeyValues *kName = FindKey( "name" );
    if (kName)
    {
        RemoveSubKey(kName);
        kName->deleteThis();
    }
    RemoveFactoryAttribute("name");
}

const char* KvArray::GetIndexChar(int index)
{
    const char* key = VarArgs("%i", index);
    return key;
}
bool KvArray::RemoveElement(int index)
{
    KeyValues* child = FindKey(index);
    if (child)
    {
        child->deleteThis();
        return true;
    }
    return false;
}
int KvArray::GetSize()
{
    int size = 0;
    for (KeyValues* child = GetFirstSubKey(); child; child = child->GetNextKey())
    {
        size++;
    }
    return size;
}
void KvArray::Clear()
{
    for (KeyValues* child = GetFirstSubKey(); child; child = child->GetNextKey())
    {
        child->deleteThis();
    }
}

//// String Array ////
void KvStringArray::SetElement(int index, const char* element)
{
    const char* key = GetIndexChar(index);
    SetString(key, element);
}
const char* KvStringArray::GetElement(int index)
{
    const char* key = GetIndexChar(index);
    return GetString(key);
}
void KvStringArray::AddElement(const char* element)
{
    int index = GetSize();
    SetElement(index, element);
}

//// Int Array ////
void KvIntArray::SetElement(int index, int element)
{
    const char* key = GetIndexChar(index);
    SetInt(key, element);
}
int KvIntArray::GetElement(int index)
{
    const char* key = GetIndexChar(index);
    return GetInt(key);
}
void KvIntArray::AddElement(int element)
{
    int index = GetSize();
    SetElement(index, element);
}

//// Float Array ////
void KvFloatArray::SetElement(int index, float element)
{
    const char* key = GetIndexChar(index);
    SetFloat(key, element);
}
float KvFloatArray::GetElement(int index)
{
    const char* key = GetIndexChar(index);
    return GetFloat(key);
}
void KvFloatArray::AddElement(float element)
{
    int index = GetSize();
    SetElement(index, element);
}

//// Bool Array ////
void KvBoolArray::SetElement(int index, bool element)
{
    const char* key = GetIndexChar(index);
    SetBool(key, element);
}
bool KvBoolArray::GetElement(int index)
{
    const char* key = GetIndexChar(index);
    return GetBool(key);
}
void KvBoolArray::AddElement(bool element)
{
    int index = GetSize();
    SetElement(index, element);
}

//// Color Array ////
void KvColorArray::SetElement(int index, Color element)
{
    const char* key = GetIndexChar(index);
    SetColor(key, element);
}
Color KvColorArray::GetElement(int index)
{
    const char* key = GetIndexChar(index);
    return GetColor(key);
}
void KvColorArray::AddElement(Color element)
{
    int index = GetSize();
    SetElement(index, element);
}

//// Generic Element Array ////
void KvDxElementArray::SetElement(int index, DxElement* element)
{
    const char* key = GetIndexChar(index);
    // Check if the element already exists
    KeyValues* existing = FindKey(key);
    if (existing)
    {
        existing->deleteThis();
    }
    // Set name of the new element
    element->SetName(key);
    AddSubKey(element);
}
DxElement* KvDxElementArray::GetElement(int index)
{
    const char* key = GetIndexChar(index);
    return (DxElement*)FindKey(key);
}
void KvDxElementArray::AddElement(DxElement* element)
{
    int index = GetSize();
    SetElement(index, element);
}

//// Vector ////
KvVector::KvVector(const char* name) : DxElement(name, "vector")
{
    SetX(0.0f);
    SetY(0.0f);
    SetZ(0.0f);
}

//// Quaternion ////
KvQuaternion::KvQuaternion(const char* name) : DxElement(name, "quaternion")
{
    SetX(0.0f);
    SetY(0.0f);
    SetZ(0.0f);
    SetW(1.0f);
}

//// QAngle ////
KvQAngle::KvQAngle(const char* name) : DxElement(name, "qangle")
{
    SetPitch(0.0f);
    SetYaw(0.0f);
    SetRoll(0.0f);
}
