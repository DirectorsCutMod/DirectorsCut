//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: TimeFrame for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "dxe_timeframe.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DxeTimeFrame::DxeTimeFrame(const char* name) : DxElement(name, "DxeTimeFrame")
{
    InitElement();
}

DxeTimeFrame::DxeTimeFrame(const char* name, const char* typeName) : DxElement(name, typeName)
{
    InitElement();
}

void DxeTimeFrame::InitElement()
{
    DxElement::InitElement();
    // Initial values
    SetStart(0.0f);
    SetDuration(0.0f);
    SetScale(1.0f);
    // Factory attributes
    AddFactoryAttribute("start");
    AddFactoryAttribute("end");
    AddFactoryAttribute("duration");
    AddFactoryAttribute("scale");
}
