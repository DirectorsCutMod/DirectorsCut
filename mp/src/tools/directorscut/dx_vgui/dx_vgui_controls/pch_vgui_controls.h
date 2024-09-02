//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef PCH_VGUI_CONTROLS_H
#define PCH_VGUI_CONTROLS_H

#ifdef _WIN32
#pragma once
#endif

// general includes
#include <ctype.h>
#include <stdlib.h>
#include "tier0/dbg.h"
#include "tier0/valve_off.h"
#include "tier1/KeyValues.h"

#include "tier0/valve_on.h"
#include "tier0/memdbgon.h"

#include "FileSystem.h"
#include "tier0/validator.h"

// vgui includes
#include "vgui/IBorder.h"
#include "vgui/IInput.h"
#include "vgui/ILocalize.h"
#include "vgui/IPanel.h"
#include "vgui/IScheme.h"
#include "vgui/ISurface.h"
#include "vgui/ISystem.h"
#include "vgui/IVGui.h"
#include "vgui/KeyCode.h"
#include "vgui/Cursor.h"
#include "vgui/MouseCode.h"

// vgui controls includes
#include "dx_vgui_controls/controls.h"

#include "dx_vgui_controls/AnimatingImagePanel.h"
#include "dx_vgui_controls/AnimationController.h"
#include "dx_vgui_controls/BitmapImagePanel.h"
#include "dx_vgui_controls/BuildGroup.h"
#include "dx_vgui_controls/BuildModeDialog.h"
#include "dx_vgui_controls/Button.h"
#include "dx_vgui_controls/CheckButton.h"
#include "dx_vgui_controls/CheckButtonList.h"
#include "dx_vgui_controls/ComboBox.h"
#include "dx_vgui_controls/Controls.h"
#include "dx_vgui_controls/DialogManager.h"
#include "dx_vgui_controls/DirectorySelectDialog.h"
#include "dx_vgui_controls/Divider.h"
#include "dx_vgui_controls/EditablePanel.h"
#include "dx_vgui_controls/FileOpenDialog.h"
#include "dx_vgui_controls/FocusNavGroup.h"
#include "dx_vgui_controls/Frame.h"
#include "dx_vgui_controls/GraphPanel.h"
#include "dx_vgui_controls/HTML.h"
#include "dx_vgui_controls/Image.h"
#include "dx_vgui_controls/ImageList.h"
#include "dx_vgui_controls/ImagePanel.h"
#include "dx_vgui_controls/Label.h"
#include "dx_vgui_controls/ListPanel.h"
#include "dx_vgui_controls/ListViewPanel.h"
#include "dx_vgui_controls/Menu.h"
#include "dx_vgui_controls/MenuBar.h"
#include "dx_vgui_controls/MenuButton.h"
#include "dx_vgui_controls/MenuItem.h"
#include "dx_vgui_controls/MessageBox.h"
#include "dx_vgui_controls/Panel.h"
#ifndef HL1
#include "dx_vgui_controls/PanelAnimationVar.h"
#endif
#include "dx_vgui_controls/PanelListPanel.h"
#include "dx_vgui_controls/PHandle.h"
#include "dx_vgui_controls/ProgressBar.h"
#include "dx_vgui_controls/ProgressBox.h"
#include "dx_vgui_controls/PropertyDialog.h"
#include "dx_vgui_controls/PropertyPage.h"
#include "dx_vgui_controls/PropertySheet.h"
#include "dx_vgui_controls/QueryBox.h"
#include "dx_vgui_controls/RadioButton.h"
#include "dx_vgui_controls/RichText.h"
#include "dx_vgui_controls/ScrollBar.h"
#include "dx_vgui_controls/ScrollBarSlider.h"
#include "dx_vgui_controls/SectionedListPanel.h"
#include "dx_vgui_controls/Slider.h"
#ifndef HL1
#include "dx_vgui_controls/Splitter.h"
#endif
#include "dx_vgui_controls/TextEntry.h"
#include "dx_vgui_controls/TextImage.h"
#include "dx_vgui_controls/ToggleButton.h"
#include "dx_vgui_controls/Tooltip.h"
#ifndef HL1
#include "dx_vgui_controls/ToolWindow.h"
#endif
#include "dx_vgui_controls/TreeView.h"
#ifndef HL1
#include "dx_vgui_controls/TreeViewListControl.h"
#endif
#include "dx_vgui_controls/URLLabel.h"
#include "dx_vgui_controls/WizardPanel.h"
#include "dx_vgui_controls/WizardSubPanel.h"

#ifndef HL1
#include "dx_vgui_controls/KeyBoardEditorDialog.h"
#include "dx_vgui_controls/InputDialog.h"
#endif

#endif // PCH_VGUI_CONTROLS_H