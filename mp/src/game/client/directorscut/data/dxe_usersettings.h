//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: User settings for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#ifndef _DIRECTORSCUT_DXE_USERSETTINGS_H_
#define _DIRECTORSCUT_DXE_USERSETTINGS_H_

#include "dxelement.h"

class DxeUserSettings : public DxElement
{
public:
    DxeUserSettings(const char* name);
    DxeUserSettings(const char* name, const char* typeName);
    void InitElement() override;
    // Attributes
};

#endif // _DIRECTORSCUT_DXE_USERSETTINGS_H_
