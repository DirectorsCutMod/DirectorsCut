//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Selected properties are edited in an all-in-one window.
//
// $NoKeywords: $
//=================================================================================//

#ifndef DXPROPERTIES_H
#define DXPROPERTIES_H

#ifdef _WIN32
#pragma once
#endif

/*
#include "vgui_controls/Panel.h"
#include <dmxloader/dmxelement.h>

using namespace vgui;

// How views are handled depends on their origin
// For instance, animation sets can have a model preview that can edit its properties
// While the asset browser can have a model preview that can only show a preview
enum DXPropertyOrigin
{
    DX_PROP_ORIGIN_GENERIC = 0, // not specific to any origin
    DX_PROP_ORIGIN_ANIMSET,
    DX_PROP_ORIGIN_ASSETBROWSER,
    DX_PROP_ORIGIN_TIMELINE,
    DX_PROP_ORIGIN_PREFERENCES,
};

enum DXPropertyView
{
    DX_PROP_VIEW_NONE = 0, // no special view
    DX_PROP_VIEW_MODEL, // model preview: show model and set skin, bodygroups, etc.
    DX_PROP_VIEW_CAMERA, // camera preview: show render target and set FOV, etc.
    DX_PROP_VIEW_LIGHT, // light preview: show render target and set color, brightness, etc.
    DX_PROP_VIEW_PARTICLE, // particle preview: show particle and set parameters
    DX_PROP_VIEW_MATERIAL, // material preview: show material and set parameters
    DX_PROP_VIEW_TEXTURE, // texture preview: show texture and set parameters
    DX_PROP_VIEW_SOUND, // sound preview: play sound and set parameters
};

// Properties are pointers to DMX elements
// The right combination of origin and view will set up its "factory"
// Views are reused for different origins
class DXProperty
{
protected:
    CDmxElement* m_pElement;
    DXPropertyOrigin m_iOrigin;
    DXPropertyView m_iView;
    Panel* m_pPreview = NULL;
public:
    DXProperty( CDmxElement* pElement, DXPropertyOrigin iOrigin, DXPropertyView iView );
    virtual ~DXProperty();
    void CreatePanel( Panel* pLeftPanel, Panel* pRightPanel );
};
*/

#endif // DXPROPERTIES_H
