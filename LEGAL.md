# Third-Party Legal Notices
This document contains legal notices related to Director's Cut.

## Trademarks
Valve, Source, and the Source logo are trademarks and/or registered trademarks of Valve Corporation.

Director's Cut is not affiliated with Valve Corporation.

## Licenses
Below is a list of the licenses for third-party software used in Director's Cut.

### Director's Cut
https://github.com/KiwifruitDev/DirectorsCut

```text
MIT License

Copyright (c) 2024 Director's Cut Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

### ashifolfi/source-sdk-2013
https://github.com/ashifolfi/source-sdk-2013

*No license found.*

### Source-SDK-Resources/source-sdk-example-qt
https://github.com/Source-SDK-Resources/source-sdk-example-qt

```text
Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
```

### Source-SDK-Resources/source-sdk-vs2022
https://github.com/Source-SDK-Resources/source-sdk-vs2022

*No license found.*

### Source Shader Editor
https://github.com/Biohazard90/source-shader-editor

*No license found.*

### Mapbase
https://github.com/mapbase-source/source-sdk-2013

```text
//=========================================================================================================================

               Mapbase v7.2 - Source 2013
	https://github.com/mapbase-source/source-sdk-2013
		https://www.moddb.com/mods/mapbase
	
//=========================================================================================================================

This repository contains code from Mapbase, a modification of the Source 2013 SDK which serves as a combined package
of general-purpose improvements, fixes, and utility features for mods.

Mapbase's main content in this repository may include:

- 80+ custom entities (new logic entities, filters, etc.)
- Hundreds of Inputs/Outputs/KeyValues additions and modifications
- Custom SDK_ shaders with improvements adapted from Alien Swarm SDK code, including projected texture fixes and radial fog
- Custom VScript implementation based on public Squirrel API and Alien Swarm SDK interfaces/descriptions
- Additional gameplay control for Half-Life 2 mods, including grenade features for more NPCs and singleplayer respawning
- More map-specific capabilities for maps unable to branch into their own mods, e.g. MP mods or map compilations
- View rendering changes for drawing 3D skyboxes and RT-based entities
- Countless other fixes and improvements

For more information, view this page:
https://github.com/mapbase-source/source-sdk-2013/wiki/Introduction-to-Mapbase

//=========================================================================================================================

Mapbase is an open-source project and its contents can be distributed and used at the discretion of its users. However, this project contains content from
a vast number of different sources which have their own licensing or attribution requirements. We try to handle most of that ourselves, but users who plan on
distributing Mapbase content are expected to comply with certain rules.

	Up-to-date information about Mapbase content usage and credit are addressed in this article on Mapbase's wiki:
		https://github.com/mapbase-source/source-sdk-2013/wiki/Using-Mapbase-Content

//=========================================================================================================================

>>>>>>>> EXTERNAL CONTENT USED IN MAPBASE <<<<<<<<

The Mapbase project is a combination of original code from its creators, code contributed by other Source modders, and code borrowed from open-source articles
and repositories (especially ones which are specifically published as free source code). One of Mapbase's goals is to make the most popular fixes and the most obscure
or complicated code changes accessible and easy to use for level designers and other kinds of Source modders who would otherwise have no idea how to implement them.

*** DISCLAIMER: Mapbase has a strict no-leak-content policy and only allows content created directly by contributors or content originating from open-source repositories.
If you believe any content in Mapbase originates from any leak or unauthorized source (Valve or otherwise), please contact Blixibon immediately.
Mapbase is intended to be usable by everyone, including licensed Source projects and Steam mods. ***

Mapbase uses content from the following non-Source SDK 2013 Valve games or SDKs:

-- Alien Swarm SDK (Used to backport features and code from newer branches of Source into a Source 2013/Half-Life 2 environment)
-- Source SDK 2007 Code (Used to implement some of Tony Sergi's code changes)

-- Alien Swarm (Used to port assets from the aforementioned SDK code features, e.g. game instructor icons)
-- Left 4 Dead (Used to port certain animations as well as assets from the aforementioned SDK code features, e.g. particle rain)
-- Half-Life: Source (Used to port friction tool textures)

Valve allows assets from these titles to be distributed for modding purposes. Note that ported assets are only used in the release build, not the code repository.

Mapbase may also contain new third-party software distributed under specific licensing. Please see the bottom of thirdpartylegalnotices.txt for more information.

Here's a list of Mapbase's other external code sources:

- https://github.com/95Navigator/insolence-2013 (Initial custom shader code and projected texture improvements; also used to implement ASW SDK particle precipitation code)
-- https://github.com/Biohazard90/g-string_2013 (Custom shadow filters, included indirectly via Insolence repo)
-- https://github.com/KyleGospo/City-17-Episode-One-Source (Brush phong and projected texture changes, included indirectly via Insolence repo)
- https://github.com/DownFall-Team/DownFall (Multiple skybox code and fix for ent_fire delay not using floats; Also used as a guide to port certain Alien Swarm SDK changes to Source 2013,
including radial fog, rope code, and treesway)
- https://github.com/momentum-mod/game (Used as a guide to port postprocess_controller and env_dof_controller to Source 2013 from the Alien Swarm SDK)
- https://github.com/DeathByNukes/source-sdk-2013 (VBSP manifest fixes)
- https://github.com/entropy-zero/source-sdk-2013 (skill_changed game event)
- https://github.com/Nbc66/source-sdk-2013-ce/tree/v142 (Base for VS2019 toolset support)

//-------------------------------------------------------------------------------------------------------------------------

Valve Developer Community (VDC) sources:

- https://developer.valvesoftware.com/wiki/Dynamic_RTT_shadow_angles_in_Source_2007 (Dynamic RTT shadow angles by Saul Rennison)
- https://developer.valvesoftware.com/wiki/Parallax_Corrected_Cubemaps (Parallax corrected cubemaps implementation from Brian Charles)
- https://developer.valvesoftware.com/wiki/Adding_the_Game_Instructor (ASW SDK game instructor adapted to Source 2013 by Kolesias123; was implemented based on a translated article)
- https://developer.valvesoftware.com/wiki/Brush_ladders (Functional func_ladders in Source 2013)
- https://developer.valvesoftware.com/wiki/CAreaPortalOneWay (func_areaportal_oneway)
- https://developer.valvesoftware.com/wiki/Implementing_Discord_RPC (Discord RPC implementation; Mapbase has its own framework originally based on this article)
- https://developer.valvesoftware.com/wiki/Rain_splashes (NOTE: This code is not completely used in Mapbase, but may still exist in its codebase)
- https://developer.valvesoftware.com/wiki/Hand_Viewmodels (NOTE: This code is not completely supported by default because Mapbase does not yet have weapon viewmodels which support
interchangeable arms; this may change in the future)

- https://developer.valvesoftware.com/wiki/General_SDK_Snippets_%26_Fixes (Various snippets on the article, including the dropship gun fix)
- https://developer.valvesoftware.com/wiki/Memory_Leak_Fixes (Most of these snippets were applied in later SDK updates, but some were not and have been added to Mapbase)
- https://developer.valvesoftware.com/wiki/Env_projectedtexture/fixes (Misc. env_projectedtexture fixes; Some of these are superceded by Alien Swarm-based changes and not used)
- https://developer.valvesoftware.com/wiki/Scenes.image (Original raw VCD file support; Code was improved for Mapbase and the article was later updated with it)
- https://developer.valvesoftware.com/wiki/Extending_Prop_Sphere (prop_sphere customization)
- https://developer.valvesoftware.com/wiki/TF2_Glow_Effect_(2013_SDK) (Glow effect)
- https://developer.valvesoftware.com/wiki/CFuncMoveLinear_ParentingFix (func_movelinear parenting fix; Code was improved for Mapbase and the article was later updated with it)
- https://developer.valvesoftware.com/wiki/Viewmodel_Prediction_Fix (Viewmodel prediction fix)
- https://developer.valvesoftware.com/wiki/Owner#Collisions_with_owner (FSOLID_COLLIDE_WITH_OWNER flag)
- https://developer.valvesoftware.com/wiki/Npc_clawscanner#Strider_Scout_Issue (npc_clawscanner strider scout fix)
- https://developer.valvesoftware.com/wiki/Ambient_generic:_stop_and_toggle_fix (Fixes for stopping/toggling ambient_generic)
- https://developer.valvesoftware.com/wiki/Func_clip_vphysics ("Start Disabled" keyvalue fix)
- https://developer.valvesoftware.com/wiki/Importing_CSS_Weapons_Into_HL2 (CS:S viewmodel chirality)

//-------------------------------------------------------------------------------------------------------------------------

Direct contributions:

- https://github.com/mapbase-source/source-sdk-2013/pull/3 ("playvideo" command playback fix from Avanate)
- https://github.com/mapbase-source/source-sdk-2013/pull/5 (Custom VScript implementation by ReDucTor; was placed into feature branch before being merged in a subsequent PR)
- https://github.com/mapbase-source/source-sdk-2013/pull/60 (Adjustment by RoyaleNoir to one of Saul's VDC changes)
- https://github.com/mapbase-source/source-sdk-2013/pull/84 (CS:S viewmodel chirality from 1upD)
- https://github.com/mapbase-source/source-sdk-2013/pull/116 (vgui_movie_display mute keyvalue from Alivebyte/rzkid)
- https://github.com/mapbase-source/source-sdk-2013/pull/140 (logic_substring entity and icon created by moofemp)
- https://github.com/mapbase-source/source-sdk-2013/pull/143 (Propper features for VBSP from Matty-64)
- https://github.com/mapbase-source/source-sdk-2013/pull/174 (Fix for multiply defined symbols in later toolsets from und)
- https://github.com/mapbase-source/source-sdk-2013/issues/201 (env_projectedtexture shadow filter keyvalue from celisej567)
- https://github.com/mapbase-source/source-sdk-2013/pull/193 (RTB:R info_particle_system_coordinate by arbabf and Iridium77)
- https://github.com/mapbase-source/source-sdk-2013/pull/193 (Infinite prop_interactable cooldown by arbabf)
- https://github.com/mapbase-source/source-sdk-2013/pull/229 (Extended point_bugbait functionality by arbabf)
- https://github.com/mapbase-source/source-sdk-2013/pull/236 (Toggleable prop sprinting by Crimson-X1)
- https://github.com/mapbase-source/source-sdk-2013/pull/237 (Commander goal trace fix by Agrimar)
- https://github.com/mapbase-source/source-sdk-2013/pull/245 (ViewPunch random fix by Mr0maks)
- https://github.com/mapbase-source/source-sdk-2013/pull/248 (soundlevel_t conversation warning fix by Mechami)
- https://github.com/mapbase-source/mapbase-game-src/pull/1 (Advanced video options duplicate field name fix by arbabf; This is asset-based and not reflected in the code)
- Demo autorecord code provided by Klems
- cc_emit crash fix provided by 1upD
- Custom HL2 ammo crate models created by Rykah (Textures created by Blixibon; This is asset-based and, aside from the SLAM crate, not reflected in the code)
- Combine lock hardware on door01_left.mdl created by Kralich (This is asset-based and not reflected in the code)
- npc_vehicledriver fixes provided by CrAzY
- npc_combine cover behavior patches provided by iohnnyboy
- logic_playmovie icon created by URAKOLOUY5 (This is asset-based and not reflected in the code)
- Dropship APC save/load fix provided by Cvoxulary

== Contributions from samisalreadytaken:
=-- https://github.com/mapbase-source/source-sdk-2013/pull/47 (VScript utility/consistency changes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/59 (New VScript functions and singletons based on API documentation in later Source/Source 2 games)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/80 (More VScript changes, including support for extremely flexible client/server messaging)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/105 (VScript fixes and optimizations, Vector class extensions, custom convars/commands)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/114 (VScript fixes and extensions)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/122 (Minor VScript-related adjustments)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/148 (Minor fixup)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/167 (Security fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/168 (Squirrel update)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/169 (VScript VGUI)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/171 (VScript documentation sorting)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/173 (VScript fixes and optimizations)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/192 (VScript hook manager and fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/206 (Fix CScriptNetMsgHelper::WriteEntity())
=-- https://github.com/mapbase-source/source-sdk-2013/pull/213 (VScript HUD visibility control, optimizations for 3D skybox angles/fake worldportals)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/229 (VScript VGUI HUD viewport parenting, game_text and vgui_text_display VScript font fallback)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/261 (Misc VScript additions)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/279 (weapon_custom_scripted fixes)

== Contributions from z33ky:
=-- https://github.com/mapbase-source/source-sdk-2013/pull/21 (Various GCC/Linux compilation fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/95 (Additional GCC/Linux compilation fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/117 (Additional GCC/Linux compilation fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/124 (Memory error fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/130 (Memory error fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/131 (env_projectedtexture target shadows fix)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/132 (Console error fix)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/152 (Additional GCC/Linux compilation fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/159 (Additional GCC/Linux compilation fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/162 (VS2019 exception specification fix)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/170 (HL2 non-Episodic build fix)

== Contributions from Petercov:
=-- https://github.com/mapbase-source/source-sdk-2013/pull/182 (NPCs load dynamic interactions from all animation MDLs)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/184 (Projected texture horizontal FOV shadow fix)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/185 (Fix enemyfinders becoming visible when they wake)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/186 (Fix for brightly glowing teeth)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/183 (Enhanced custom weapons support)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/230 (Caption fixes)
=-- https://github.com/mapbase-source/source-sdk-2013/pull/231 (Sentence source bug fix)

//-------------------------------------------------------------------------------------------------------------------------

Other sources:

- Various code from Source SDK 2013 pull requests on the GitHub repository (https://github.com/ValveSoftware/source-sdk-2013/pulls):
-- https://github.com/ValveSoftware/source-sdk-2013/pull/441 (Smooth scrape sound oversight fix)
-- https://github.com/ValveSoftware/source-sdk-2013/pull/436 (VRAD debug counter fix + thread bump)
-- https://github.com/ValveSoftware/source-sdk-2013/pull/416 (Ragdoll null pointer dereference fix)
-- https://github.com/ValveSoftware/source-sdk-2013/pull/401 (func_rot_button "Starts locked" flag fix)
-- https://github.com/ValveSoftware/source-sdk-2013/pull/391 (VBSP func_detail smoothing group fix)
-- https://github.com/ValveSoftware/source-sdk-2013/pull/362 (npc_manhack npc_maker fix; Adjusted for formatting and save/restore in Mapbase)
-- https://github.com/Petercov/Source-PlusPlus/commit/ecdf50c48cd31dec4dbdb7fea2d0780e7f0dd8ec (used as a guide for porting the Alien Swarm SDK response system)
- https://github.com/momentum-mod/game/blob/1d066180b3bf74830c51e6914d46c40b0bea1fc2/mp/src/game/server/player.cpp#L6543 (spec_goto fix)
- Poison zombie barnacle crash fix implemented based on a snippet from HL2: Plus posted by Agent Agrimar on Discord (Mapbase makes the barnacle recognize it as poison just like poison headcrabs)
- https://gamebanana.com/skins/172192 (Airboat handling fix; This is asset-based and not reflected in the code)
- Vortigaunt LOS fix originally created by dky.tehkingd.u for HL2:CE
- https://combineoverwiki.net/wiki/File:Combine_main_symbol.svg ("icon_combine" instructor icon in "materials/vgui/hud/gameinstructor_hl2_1"; This is asset-based and not reflected in the code)

//-------------------------------------------------------------------------------------------------------------------------

If there is anything missing from this list, please contact Blixibon.

//=========================================================================================================================

Aside from the content list above, Mapbase has more descriptive and up-to-date credits on this wiki article:
https://github.com/mapbase-source/source-sdk-2013/wiki/Mapbase-Credits

Other relevant articles:
* https://github.com/mapbase-source/source-sdk-2013/wiki/Mapbase-Disclaimers
* https://github.com/mapbase-source/source-sdk-2013/wiki/Frequently-Asked-Questions-(FAQ)

//-------------------------------------------------------------------------------------------------------------------------

In memory of Holly Liberatore (moofemp)

//=========================================================================================================================

Please see the Source SDK 2013 license below:



               SOURCE 1 SDK LICENSE

Source SDK Copyright(c) Valve Corp.  

THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE 
CORPORATION ("Valve").  PLEASE READ IT BEFORE DOWNLOADING OR USING 
THE SOURCE ENGINE SDK ("SDK"). BY DOWNLOADING AND/OR USING THE 
SOURCE ENGINE SDK YOU ACCEPT THIS LICENSE. IF YOU DO NOT AGREE TO 
THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.  

  You may, free of charge, download and use the SDK to develop a modified Valve game 
running on the Source engine.  You may distribute your modified Valve game in source and 
object code form, but only for free. Terms of use for Valve games are found in the Steam 
Subscriber Agreement located here: http://store.steampowered.com/subscriber_agreement/ 

  You may copy, modify, and distribute the SDK and any modifications you make to the 
SDK in source and object code form, but only for free.  Any distribution of this SDK must 
include this LICENSE file and thirdpartylegalnotices.txt.  
 
  Any distribution of the SDK or a substantial portion of the SDK must include the above 
copyright notice and the following: 

    DISCLAIMER OF WARRANTIES.  THE SOURCE SDK AND ANY 
    OTHER MATERIAL DOWNLOADED BY LICENSEE IS PROVIDED 
    "AS IS".  VALVE AND ITS SUPPLIERS DISCLAIM ALL 
    WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS 
    OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, IMPLIED 
    WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, 
    TITLE AND FITNESS FOR A PARTICULAR PURPOSE.  

    LIMITATION OF LIABILITY.  IN NO EVENT SHALL VALVE OR 
    ITS SUPPLIERS BE LIABLE FOR ANY SPECIAL, INCIDENTAL, 
    INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER 
    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF 
    BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF 
    BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) 
    ARISING OUT OF THE USE OF OR INABILITY TO USE THE 
    ENGINE AND/OR THE SDK, EVEN IF VALVE HAS BEEN 
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  
 
       
If you would like to use the SDK for a commercial purpose, please contact Valve at 
sourceengine@valvesoftware.com.
```

### Source 2013 SDK
https://github.com/ValveSoftware/source-sdk-2013

```text
               SOURCE 1 SDK LICENSE

Source SDK Copyright(c) Valve Corp.  

THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE 
CORPORATION ("Valve").  PLEASE READ IT BEFORE DOWNLOADING OR USING 
THE SOURCE ENGINE SDK ("SDK"). BY DOWNLOADING AND/OR USING THE 
SOURCE ENGINE SDK YOU ACCEPT THIS LICENSE. IF YOU DO NOT AGREE TO 
THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.  

  You may, free of charge, download and use the SDK to develop a modified Valve game 
running on the Source engine.  You may distribute your modified Valve game in source and 
object code form, but only for free. Terms of use for Valve games are found in the Steam 
Subscriber Agreement located here: http://store.steampowered.com/subscriber_agreement/ 

  You may copy, modify, and distribute the SDK and any modifications you make to the 
SDK in source and object code form, but only for free.  Any distribution of this SDK must 
include this LICENSE file and thirdpartylegalnotices.txt.  
 
  Any distribution of the SDK or a substantial portion of the SDK must include the above 
copyright notice and the following: 

    DISCLAIMER OF WARRANTIES.  THE SOURCE SDK AND ANY 
    OTHER MATERIAL DOWNLOADED BY LICENSEE IS PROVIDED 
    "AS IS".  VALVE AND ITS SUPPLIERS DISCLAIM ALL 
    WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS 
    OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, IMPLIED 
    WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, 
    TITLE AND FITNESS FOR A PARTICULAR PURPOSE.  

    LIMITATION OF LIABILITY.  IN NO EVENT SHALL VALVE OR 
    ITS SUPPLIERS BE LIABLE FOR ANY SPECIAL, INCIDENTAL, 
    INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER 
    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF 
    BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF 
    BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) 
    ARISING OUT OF THE USE OF OR INABILITY TO USE THE 
    ENGINE AND/OR THE SDK, EVEN IF VALVE HAS BEEN 
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  
 
       
If you would like to use the SDK for a commercial purpose, please contact Valve at 
sourceengine@valvesoftware.com.

The Source engine and Valve games use Third Party code for certain functions.  The 
required legal notices for using such code are reproduced below in accordance with 
Valve’s obligations to provide such notices:

************************************************************************************
Xzip/Xunzip:
************************************************************************************

	// This is version 2002-Feb-16 of the Info-ZIP copyright and license. The 
	// definitive version of this document should be available at 
	// ftp://ftp.info-zip.org/pub/infozip/license.html indefinitely.
	// 
	// Copyright (c) 1990-2002 Info-ZIP.  All rights reserved.
	//
	// For the purposes of this copyright and license, "Info-ZIP" is defined as
	// the following set of individuals:
	//
	//   Mark Adler, John Bush, Karl Davis, Harald Denker, Jean-Michel Dubois,
	//   Jean-loup Gailly, Hunter Goatley, Ian Gorman, Chris Herborth, Dirk Haase,
	//   Greg Hartwig, Robert Heath, Jonathan Hudson, Paul Kienitz, 
	//   David Kirschbaum, Johnny Lee, Onno van der Linden, Igor Mandrichenko, 
	//   Steve P. Miller, Sergio Monesi, Keith Owens, George Petrov, Greg Roelofs, 
	//   Kai Uwe Rommel, Steve Salisbury, Dave Smith, Christian Spieler, 
	//   Antoine Verheijen, Paul von Behren, Rich Wales, Mike White
	//
	// This software is provided "as is", without warranty of any kind, express
	// or implied.  In no event shall Info-ZIP or its contributors be held liable
	// for any direct, indirect, incidental, special or consequential damages
	// arising out of the use of or inability to use this software.
	//
	// Permission is granted to anyone to use this software for any purpose,
	// including commercial applications, and to alter it and redistribute it
	// freely, subject to the following restrictions:
	//
	//    1. Redistributions of source code must retain the above copyright notice,
	//       definition, disclaimer, and this list of conditions.
	//
	//    2. Redistributions in binary form (compiled executables) must reproduce 
	//       the above copyright notice, definition, disclaimer, and this list of 
	//       conditions in documentation and/or other materials provided with the 
	//       distribution. The sole exception to this condition is redistribution 
	//       of a standard UnZipSFX binary as part of a self-extracting archive; 
	//       that is permitted without inclusion of this license, as long as the 
	//       normal UnZipSFX banner has not been removed from the binary or disabled.
	//
	//    3. Altered versions--including, but not limited to, ports to new 
	//       operating systems, existing ports with new graphical interfaces, and 
	//       dynamic, shared, or static library versions--must be plainly marked 
	//       as such and must not be misrepresented as being the original source.  
	//       Such altered versions also must not be misrepresented as being 
	//       Info-ZIP releases--including, but not limited to, labeling of the 
	//       altered versions with the names "Info-ZIP" (or any variation thereof, 
	//       including, but not limited to, different capitalizations), 
	//       "Pocket UnZip", "WiZ" or "MacZip" without the explicit permission of 
	//       Info-ZIP.  Such altered versions are further prohibited from 
	//       misrepresentative use of the Zip-Bugs or Info-ZIP e-mail addresses or 
	//       of the Info-ZIP URL(s).
	//
	//    4. Info-ZIP retains the right to use the names "Info-ZIP", "Zip", "UnZip",
	//       "UnZipSFX", "WiZ", "Pocket UnZip", "Pocket Zip", and "MacZip" for its 
	//       own source and binary releases.
	//
	///////////////////////////////////////////////////////////////////////////////

************************************************************************************
JPEG image support:
************************************************************************************

	The Source engine and SDK also make use of library functions for working with .jpg 
	files.  Specifically, the Source engine jpeg library is based in part on the work of 
	the Independent JPEG Group (IJG).  The original source code and project files for the IJG's 
	JPEG libraries may be found at:  http://www.ijg.org/files/jpegsrc.v6b.tar.gz

	The following is the README. File from that archive and is produced in accordance with the legal 
	notices required by the library:

	The Independent JPEG Group's JPEG software
	==========================================

	README for release 6b of 27-Mar-1998
	====================================

	This distribution contains the sixth public release of the Independent JPEG
	Group's free JPEG software.  You are welcome to redistribute this software and
	to use it for any purpose, subject to the conditions under LEGAL ISSUES, below.

	Serious users of this software (particularly those incorporating it into
	larger programs) should contact IJG at jpeg-info@uunet.uu.net to be added to
	our electronic mailing list.  Mailing list members are notified of updates
	and have a chance to participate in technical discussions, etc.

	This software is the work of Tom Lane, Philip Gladstone, Jim Boucher,
	Lee Crocker, Julian Minguillon, Luis Ortiz, George Phillips, Davide Rossi,
	Guido Vollbeding, Ge' Weijers, and other members of the Independent JPEG
	Group.

	IJG is not affiliated with the official ISO JPEG standards committee.


	DOCUMENTATION ROADMAP
	=====================

	This file contains the following sections:

	OVERVIEW            General description of JPEG and the IJG software.
	LEGAL ISSUES        Copyright, lack of warranty, terms of distribution.
	REFERENCES          Where to learn more about JPEG.
	ARCHIVE LOCATIONS   Where to find newer versions of this software.
	RELATED SOFTWARE    Other stuff you should get.
	FILE FORMAT WARS    Software *not* to get.
	TO DO               Plans for future IJG releases.

	Other documentation files in the distribution are:

	User documentation:
	  install.doc       How to configure and install the IJG software.
	  usage.doc         Usage instructions for cjpeg, djpeg, jpegtran,
						rdjpgcom, and wrjpgcom.
	  *.1               Unix-style man pages for programs (same info as usage.doc).
	  wizard.doc        Advanced usage instructions for JPEG wizards only.
	  change.log        Version-to-version change highlights.
	Programmer and internal documentation:
	  libjpeg.doc       How to use the JPEG library in your own programs.
	  example.c         Sample code for calling the JPEG library.
	  structure.doc     Overview of the JPEG library's internal structure.
	  filelist.doc      Road map of IJG files.
	  coderules.doc     Coding style rules --- please read if you contribute code.

	Please read at least the files install.doc and usage.doc.  Useful information
	can also be found in the JPEG FAQ (Frequently Asked Questions) article.  See
	ARCHIVE LOCATIONS below to find out where to obtain the FAQ article.

	If you want to understand how the JPEG code works, we suggest reading one or
	more of the REFERENCES, then looking at the documentation files (in roughly
	the order listed) before diving into the code.


	OVERVIEW
	========

	This package contains C software to implement JPEG image compression and
	decompression.  JPEG (pronounced "jay-peg") is a standardized compression
	method for full-color and gray-scale images.  JPEG is intended for compressing
	"real-world" scenes; line drawings, cartoons and other non-realistic images
	are not its strong suit.  JPEG is lossy, meaning that the output image is not
	exactly identical to the input image.  Hence you must not use JPEG if you
	have to have identical output bits.  However, on typical photographic images,
	very good compression levels can be obtained with no visible change, and
	remarkably high compression levels are possible if you can tolerate a
	low-quality image.  For more details, see the references, or just experiment
	with various compression settings.

	This software implements JPEG baseline, extended-sequential, and progressive
	compression processes.  Provision is made for supporting all variants of these
	processes, although some uncommon parameter settings aren't implemented yet.
	For legal reasons, we are not distributing code for the arithmetic-coding
	variants of JPEG; see LEGAL ISSUES.  We have made no provision for supporting
	the hierarchical or lossless processes defined in the standard.

	We provide a set of library routines for reading and writing JPEG image files,
	plus two sample applications "cjpeg" and "djpeg", which use the library to
	perform conversion between JPEG and some other popular image file formats.
	The library is intended to be reused in other applications.

	In order to support file conversion and viewing software, we have included
	considerable functionality beyond the bare JPEG coding/decoding capability;
	for example, the color quantization modules are not strictly part of JPEG
	decoding, but they are essential for output to colormapped file formats or
	colormapped displays.  These extra functions can be compiled out of the
	library if not required for a particular application.  We have also included
	"jpegtran", a utility for lossless transcoding between different JPEG
	processes, and "rdjpgcom" and "wrjpgcom", two simple applications for
	inserting and extracting textual comments in JFIF files.

	The emphasis in designing this software has been on achieving portability and
	flexibility, while also making it fast enough to be useful.  In particular,
	the software is not intended to be read as a tutorial on JPEG.  (See the
	REFERENCES section for introductory material.)  Rather, it is intended to
	be reliable, portable, industrial-strength code.  We do not claim to have
	achieved that goal in every aspect of the software, but we strive for it.

	We welcome the use of this software as a component of commercial products.
	No royalty is required, but we do ask for an acknowledgement in product
	documentation, as described under LEGAL ISSUES.


	LEGAL ISSUES
	============

	In plain English:

	1. We don't promise that this software works.  (But if you find any bugs,
	   please let us know!)
	2. You can use this software for whatever you want.  You don't have to pay us.
	3. You may not pretend that you wrote this software.  If you use it in a
	   program, you must acknowledge somewhere in your documentation that
	   you've used the IJG code.

	In legalese:

	The authors make NO WARRANTY or representation, either express or implied,
	with respect to this software, its quality, accuracy, merchantability, or
	fitness for a particular purpose.  This software is provided "AS IS", and you,
	its user, assume the entire risk as to its quality and accuracy.

	This software is copyright (C) 1991-1998, Thomas G. Lane.
	All Rights Reserved except as specified below.

	Permission is hereby granted to use, copy, modify, and distribute this
	software (or portions thereof) for any purpose, without fee, subject to these
	conditions:
	(1) If any part of the source code for this software is distributed, then this
	README file must be included, with this copyright and no-warranty notice
	unaltered; and any additions, deletions, or changes to the original files
	must be clearly indicated in accompanying documentation.
	(2) If only executable code is distributed, then the accompanying
	documentation must state that "this software is based in part on the work of
	the Independent JPEG Group".
	(3) Permission for use of this software is granted only if the user accepts
	full responsibility for any undesirable consequences; the authors accept
	NO LIABILITY for damages of any kind.

	These conditions apply to any software derived from or based on the IJG code,
	not just to the unmodified library.  If you use our work, you ought to
	acknowledge us.

	Permission is NOT granted for the use of any IJG author's name or company name
	in advertising or publicity relating to this software or products derived from
	it.  This software may be referred to only as "the Independent JPEG Group's
	software".

	We specifically permit and encourage the use of this software as the basis of
	commercial products, provided that all warranty or liability claims are
	assumed by the product vendor.


	ansi2knr.c is included in this distribution by permission of L. Peter Deutsch,
	sole proprietor of its copyright holder, Aladdin Enterprises of Menlo Park, CA.
	ansi2knr.c is NOT covered by the above copyright and conditions, but instead
	by the usual distribution terms of the Free Software Foundation; principally,
	that you must include source code if you redistribute it.  (See the file
	ansi2knr.c for full details.)  However, since ansi2knr.c is not needed as part
	of any program generated from the IJG code, this does not limit you more than
	the foregoing paragraphs do.

	The Unix configuration script "configure" was produced with GNU Autoconf.
	It is copyright by the Free Software Foundation but is freely distributable.
	The same holds for its supporting scripts (config.guess, config.sub,
	ltconfig, ltmain.sh).  Another support script, install-sh, is copyright
	by M.I.T. but is also freely distributable.

	It appears that the arithmetic coding option of the JPEG spec is covered by
	patents owned by IBM, AT&T, and Mitsubishi.  Hence arithmetic coding cannot
	legally be used without obtaining one or more licenses.  For this reason,
	support for arithmetic coding has been removed from the free JPEG software.
	(Since arithmetic coding provides only a marginal gain over the unpatented
	Huffman mode, it is unlikely that very many implementations will support it.)
	So far as we are aware, there are no patent restrictions on the remaining
	code.

	The IJG distribution formerly included code to read and write GIF files.
	To avoid entanglement with the Unisys LZW patent, GIF reading support has
	been removed altogether, and the GIF writer has been simplified to produce
	"uncompressed GIFs".  This technique does not use the LZW algorithm; the
	resulting GIF files are larger than usual, but are readable by all standard
	GIF decoders.

	We are required to state that
		"The Graphics Interchange Format(c) is the Copyright property of
		CompuServe Incorporated.  GIF(sm) is a Service Mark property of
		CompuServe Incorporated."


	REFERENCES
	==========

	We highly recommend reading one or more of these references before trying to
	understand the innards of the JPEG software.

	The best short technical introduction to the JPEG compression algorithm is
		Wallace, Gregory K.  "The JPEG Still Picture Compression Standard",
		Communications of the ACM, April 1991 (vol. 34 no. 4), pp. 30-44.
	(Adjacent articles in that issue discuss MPEG motion picture compression,
	applications of JPEG, and related topics.)  If you don't have the CACM issue
	handy, a PostScript file containing a revised version of Wallace's article is
	available at ftp://ftp.uu.net/graphics/jpeg/wallace.ps.gz.  The file (actually
	a preprint for an article that appeared in IEEE Trans. Consumer Electronics)
	omits the sample images that appeared in CACM, but it includes corrections
	and some added material.  Note: the Wallace article is copyright ACM and IEEE,
	and it may not be used for commercial purposes.

	A somewhat less technical, more leisurely introduction to JPEG can be found in
	"The Data Compression Book" by Mark Nelson and Jean-loup Gailly, published by
	M&T Books (New York), 2nd ed. 1996, ISBN 1-55851-434-1.  This book provides
	good explanations and example C code for a multitude of compression methods
	including JPEG.  It is an excellent source if you are comfortable reading C
	code but don't know much about data compression in general.  The book's JPEG
	sample code is far from industrial-strength, but when you are ready to look
	at a full implementation, you've got one here...

	The best full description of JPEG is the textbook "JPEG Still Image Data
	Compression Standard" by William B. Pennebaker and Joan L. Mitchell, published
	by Van Nostrand Reinhold, 1993, ISBN 0-442-01272-1.  Price US$59.95, 638 pp.
	The book includes the complete text of the ISO JPEG standards (DIS 10918-1
	and draft DIS 10918-2).  This is by far the most complete exposition of JPEG
	in existence, and we highly recommend it.

	The JPEG standard itself is not available electronically; you must order a
	paper copy through ISO or ITU.  (Unless you feel a need to own a certified
	official copy, we recommend buying the Pennebaker and Mitchell book instead;
	it's much cheaper and includes a great deal of useful explanatory material.)
	In the USA, copies of the standard may be ordered from ANSI Sales at (212)
	642-4900, or from Global Engineering Documents at (800) 854-7179.  (ANSI
	doesn't take credit card orders, but Global does.)  It's not cheap: as of
	1992, ANSI was charging $95 for Part 1 and $47 for Part 2, plus 7%
	shipping/handling.  The standard is divided into two parts, Part 1 being the
	actual specification, while Part 2 covers compliance testing methods.  Part 1
	is titled "Digital Compression and Coding of Continuous-tone Still Images,
	Part 1: Requirements and guidelines" and has document numbers ISO/IEC IS
	10918-1, ITU-T T.81.  Part 2 is titled "Digital Compression and Coding of
	Continuous-tone Still Images, Part 2: Compliance testing" and has document
	numbers ISO/IEC IS 10918-2, ITU-T T.83.

	Some extensions to the original JPEG standard are defined in JPEG Part 3,
	a newer ISO standard numbered ISO/IEC IS 10918-3 and ITU-T T.84.  IJG
	currently does not support any Part 3 extensions.

	The JPEG standard does not specify all details of an interchangeable file
	format.  For the omitted details we follow the "JFIF" conventions, revision
	1.02.  A copy of the JFIF spec is available from:
		Literature Department
		C-Cube Microsystems, Inc.
		1778 McCarthy Blvd.
		Milpitas, CA 95035
		phone (408) 944-6300,  fax (408) 944-6314
	A PostScript version of this document is available by FTP at
	ftp://ftp.uu.net/graphics/jpeg/jfif.ps.gz.  There is also a plain text
	version at ftp://ftp.uu.net/graphics/jpeg/jfif.txt.gz, but it is missing
	the figures.

	The TIFF 6.0 file format specification can be obtained by FTP from
	ftp://ftp.sgi.com/graphics/tiff/TIFF6.ps.gz.  The JPEG incorporation scheme
	found in the TIFF 6.0 spec of 3-June-92 has a number of serious problems.
	IJG does not recommend use of the TIFF 6.0 design (TIFF Compression tag 6).
	Instead, we recommend the JPEG design proposed by TIFF Technical Note #2
	(Compression tag 7).  Copies of this Note can be obtained from ftp.sgi.com or
	from ftp://ftp.uu.net/graphics/jpeg/.  It is expected that the next revision
	of the TIFF spec will replace the 6.0 JPEG design with the Note's design.
	Although IJG's own code does not support TIFF/JPEG, the free libtiff library
	uses our library to implement TIFF/JPEG per the Note.  libtiff is available
	from ftp://ftp.sgi.com/graphics/tiff/.


	ARCHIVE LOCATIONS
	=================

	The "official" archive site for this software is ftp.uu.net (Internet
	address 192.48.96.9).  The most recent released version can always be found
	there in directory graphics/jpeg.  This particular version will be archived
	as ftp://ftp.uu.net/graphics/jpeg/jpegsrc.v6b.tar.gz.  If you don't have
	direct Internet access, UUNET's archives are also available via UUCP; contact
	help@uunet.uu.net for information on retrieving files that way.

	Numerous Internet sites maintain copies of the UUNET files.  However, only
	ftp.uu.net is guaranteed to have the latest official version.

	You can also obtain this software in DOS-compatible "zip" archive format from
	the SimTel archives (ftp://ftp.simtel.net/pub/simtelnet/msdos/graphics/), or
	on CompuServe in the Graphics Support forum (GO CIS:GRAPHSUP), library 12
	"JPEG Tools".  Again, these versions may sometimes lag behind the ftp.uu.net
	release.

	The JPEG FAQ (Frequently Asked Questions) article is a useful source of
	general information about JPEG.  It is updated constantly and therefore is
	not included in this distribution.  The FAQ is posted every two weeks to
	Usenet newsgroups comp.graphics.misc, news.answers, and other groups.
	It is available on the World Wide Web at http://www.faqs.org/faqs/jpeg-faq/
	and other news.answers archive sites, including the official news.answers
	archive at rtfm.mit.edu: ftp://rtfm.mit.edu/pub/usenet/news.answers/jpeg-faq/.
	If you don't have Web or FTP access, send e-mail to mail-server@rtfm.mit.edu
	with body
		send usenet/news.answers/jpeg-faq/part1
		send usenet/news.answers/jpeg-faq/part2


	RELATED SOFTWARE
	================

	Numerous viewing and image manipulation programs now support JPEG.  (Quite a
	few of them use this library to do so.)  The JPEG FAQ described above lists
	some of the more popular free and shareware viewers, and tells where to
	obtain them on Internet.

	If you are on a Unix machine, we highly recommend Jef Poskanzer's free
	PBMPLUS software, which provides many useful operations on PPM-format image
	files.  In particular, it can convert PPM images to and from a wide range of
	other formats, thus making cjpeg/djpeg considerably more useful.  The latest
	version is distributed by the NetPBM group, and is available from numerous
	sites, notably ftp://wuarchive.wustl.edu/graphics/graphics/packages/NetPBM/.
	Unfortunately PBMPLUS/NETPBM is not nearly as portable as the IJG software is;
	you are likely to have difficulty making it work on any non-Unix machine.

	A different free JPEG implementation, written by the PVRG group at Stanford,
	is available from ftp://havefun.stanford.edu/pub/jpeg/.  This program
	is designed for research and experimentation rather than production use;
	it is slower, harder to use, and less portable than the IJG code, but it
	is easier to read and modify.  Also, the PVRG code supports lossless JPEG,
	which we do not.  (On the other hand, it doesn't do progressive JPEG.)


	FILE FORMAT WARS
	================

	Some JPEG programs produce files that are not compatible with our library.
	The root of the problem is that the ISO JPEG committee failed to specify a
	concrete file format.  Some vendors "filled in the blanks" on their own,
	creating proprietary formats that no one else could read.  (For example, none
	of the early commercial JPEG implementations for the Macintosh were able to
	exchange compressed files.)

	The file format we have adopted is called JFIF (see REFERENCES).  This format
	has been agreed to by a number of major commercial JPEG vendors, and it has
	become the de facto standard.  JFIF is a minimal or "low end" representation.
	We recommend the use of TIFF/JPEG (TIFF revision 6.0 as modified by TIFF
	Technical Note #2) for "high end" applications that need to record a lot of
	additional data about an image.  TIFF/JPEG is fairly new and not yet widely
	supported, unfortunately.

	The upcoming JPEG Part 3 standard defines a file format called SPIFF.
	SPIFF is interoperable with JFIF, in the sense that most JFIF decoders should
	be able to read the most common variant of SPIFF.  SPIFF has some technical
	advantages over JFIF, but its major claim to fame is simply that it is an
	official standard rather than an informal one.  At this point it is unclear
	whether SPIFF will supersede JFIF or whether JFIF will remain the de-facto
	standard.  IJG intends to support SPIFF once the standard is frozen, but we
	have not decided whether it should become our default output format or not.
	(In any case, our decoder will remain capable of reading JFIF indefinitely.)

	Various proprietary file formats incorporating JPEG compression also exist.
	We have little or no sympathy for the existence of these formats.  Indeed,
	one of the original reasons for developing this free software was to help
	force convergence on common, open format standards for JPEG files.  Don't
	use a proprietary file format!


	TO DO
	=====

	The major thrust for v7 will probably be improvement of visual quality.
	The current method for scaling the quantization tables is known not to be
	very good at low Q values.  We also intend to investigate block boundary
	smoothing, "poor man's variable quantization", and other means of improving
	quality-vs-file-size performance without sacrificing compatibility.

	In future versions, we are considering supporting some of the upcoming JPEG
	Part 3 extensions --- principally, variable quantization and the SPIFF file
	format.

	As always, speeding things up is of great interest.

	Please send bug reports, offers of help, etc. to jpeg-info@uunet.uu.net.

************************************************************************************
Celt Codec:
************************************************************************************

	Copyright 2001-2009 Jean-Marc Valin, Timothy B. Terriberry,
	                    CSIRO, and other contributors

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	- Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	- Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in the
	documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
	EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
	PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
	PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

************************************************************************************
SPEEX Codes:
************************************************************************************
	SPEEX  © 2002-2003, Jean-Marc Valin/Xiph.Org Foundation
	Redistribution and use in source and binary forms, with or without modification, are permitted 
	provided that the following conditions are met: 
	*	Redistributions of source code must retain the above copyright notice, this list of 
	conditions and the following disclaimer. 
	*	Redistributions in binary form must reproduce the above copyright notice, this list of 
	conditions and the following disclaimer in the documentation and/or other materials 
	provided with the distribution. 
	*	Neither the name of the Xiph.org Foundation nor the names of its contributors may be 
	used to endorse or promote products derived from this software without specific prior 
	written permission. 
	This software is provided by the copyright holders and contributors “as is” and any express or 
	implied warranties, including, but not limited to, the implied warranties of merchantability and 
	fitness for a particular purpose are disclaimed. In no event shall the foundation or contributors be 
	liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, 
	but not limited to, procurement of substitute goods or services; loss of use, data, or profits; or 
	business interruption) however caused and on any theory of liability, whether in contract, strict 
	liability, or tort (including negligence or otherwise) arising in any way out of the use of this 
	software, even if advised of the possibility of such damage. 

************************************************************************************
google-perftools:
************************************************************************************

	http://code.google.com/p/gperftools/ 

	Copyright (c) 2012, Google Inc.
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

		* Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above
	copyright notice, this list of conditions and the following disclaimer
	in the documentation and/or other materials provided with the
	distribution.
		* Neither the name of Google Inc. nor the names of its
	contributors may be used to endorse or promote products derived from
	this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	For Google libjingle:
	http://sourceforge.net/projects/libjingle/
	Copyright (c) 2004--2005, Google Inc.
	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

		* Redistributions of source code must retain the above copyright notice,
		  this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright notice,
		  this list of conditions and the following disclaimer in the documentation
		  and/or other materials provided with the distribution.
		* The name of the author may not be used to endorse or promote products
		  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
	INTERRUPTION)
	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
	OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
	DAMAGE.

************************************************************************************
CakePHP:
************************************************************************************

	CakePHP(tm) :  Rapid Development Framework <http://www.cakephp.org/>
	Copyright 2005-2007,	Cake Software Foundation, Inc.
				1785 E. Sahara Avenue, Suite 490-204
				Las Vegas, Nevada 89104

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.

************************************************************************************
LZMA
************************************************************************************

	LZMA SDK 4.40 Copyright (c) 1999-2006 Igor Pavlov (2006-05-01)
	http://www.7-zip.org/
	LZMA SDK is licensed under two licenses:
	1) GNU Lesser General Public License (GNU LGPL)
	2) Common Public License (CPL)
	It means that you can select one of these two licenses and 
	follow rules of that license.
	SPECIAL EXCEPTION:
	Igor Pavlov, as the author of this Code, expressly permits you to 
	statically or dynamically link your Code (or bind by name) to the 
	interfaces of this file without subjecting your linked Code to the 
	terms of the CPL or GNU LGPL. Any modifications or additions 
	to this file, however, are subject to the LGPL or CPL terms.

************************************************************************************
Fast Pow Function
************************************************************************************

	/*
	 * (c) Ian Stephenson
	 *
	 * ian@dctsystems.co.uk
	 *
	 * Fast pow() reference implementation
	 */

	Used with permission from author

	For libantlr3c:
	// [The "BSD licence"]
	// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
	// http://www.temporal-wave.com
	// http://www.linkedin.com/in/jimidle
	//
	// All rights reserved.
	//
	// Redistribution and use in source and binary forms, with or without
	// modification, are permitted provided that the following conditions
	// are met:
	// 1. Redistributions of source code must retain the above copyright
	//    notice, this list of conditions and the following disclaimer.
	// 2. Redistributions in binary form must reproduce the above copyright
	//    notice, this list of conditions and the following disclaimer in the
	//    documentation and/or other materials provided with the distribution.
	// 3. The name of the author may not be used to endorse or promote products
	//    derived from this software without specific prior written permission.
	//
	// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

************************************************************************************
Autodesk® FBX®:
************************************************************************************

	“This software contains Autodesk® FBX® code developed by Autodesk, Inc. Copyright 2012 Autodesk, Inc. 
	All rights, reserved. Such code is provided “as is” and Autodesk, Inc. disclaims any and all warranties, 
	whether express or implied, including without limitation the implied warranties of merchantability, fitness for a 
	particular purpose or non-infringement of third party rights. In no event shall Autodesk, Inc. be liable for any 
	direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, 
	procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however 
	caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence or 
	otherwise) arising in any way out of such code.”

************************************************************************************
OpenSSL:
************************************************************************************

	 * This product includes software developed by the OpenSSL Project
	 * for use in the OpenSSL Toolkit. (http://www.openssl.org/)
	 * This product includes cryptographic software written by Eric Young
	 * (eay@cryptsoft.com).  This product includes software written by Tim
	 * Hudson (tjh@cryptsoft.com).
	/* ====================================================================
	 * Copyright (c) 1998-2008 The OpenSSL Project.  All rights reserved.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 *
	 * 1. Redistributions of source code must retain the above copyright
	 *    notice, this list of conditions and the following disclaimer.
	 *
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in
	 *    the documentation and/or other materials provided with the
	 *    distribution.
	 *
	 * 3. All advertising materials mentioning features or use of this
	 *    software must display the following acknowledgment:
	 *    "This product includes software developed by the OpenSSL Project
	 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
	 *
	 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be 
	used to
	 *    endorse or promote products derived from this software without
	 *    prior written permission. For written permission, please contact
	 *    openssl-core@openssl.org.
	 *
	 * 5. Products derived from this software may not be called "OpenSSL"
	 *    nor may "OpenSSL" appear in their names without prior written
	 *    permission of the OpenSSL Project.
	 *
	 * 6. Redistributions of any form whatsoever must retain the following
	 *    acknowledgment:
	 *    "This product includes software developed by the OpenSSL Project
	 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
	 *
	 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
	 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
	 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
	 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
	 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
	 * OF THE POSSIBILITY OF SUCH DAMAGE.
	 * ====================================================================
	 *
	 *
	 */


	/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
	 * All rights reserved.
	 *
	 * This package is an SSL implementation written
	 * by Eric Young (eay@cryptsoft.com).
	 * The implementation was written so as to conform with Netscapes SSL.
	 *
	 * This library is free for commercial and non-commercial use as long as
	 * the following conditions are aheared to.  The following conditions
	 * apply to all code found in this distribution, be it the RC4, RSA,
	 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
	 * included with this distribution is covered by the same copyright terms
	 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
	 *
	 * Copyright remains Eric Young's, and as such any Copyright notices in
	 * the code are not to be removed.
	 * If this package is used in a product, Eric Young should be given attribution
	 * as the author of the parts of the library used.
	 * This can be in the form of a textual message at program startup or
	 * in documentation (online or textual) provided with the package.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 * 1. Redistributions of source code must retain the copyright
	 *    notice, this list of conditions and the following disclaimer.
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in the
	 *    documentation and/or other materials provided with the distribution.
	 * 3. All advertising materials mentioning features or use of this software
	 *    must display the following acknowledgement:
	 *    "This product includes cryptographic software written by
	 *     Eric Young (eay@cryptsoft.com)"
	 *    The word 'cryptographic' can be left out if the rouines from the library
	 *    being used are not cryptographic related :-).
	 * 4. If you include any Windows specific code (or a derivative thereof) from
	 *    the apps directory (application code) you must include an 
	acknowledgement:
	 *    "This product includes software written by Tim Hudson 
	(tjh@cryptsoft.com)"
	 *
	 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
	 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
	 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	 * SUCH DAMAGE.
	 *
	 * The licence and distribution terms for any publically available version or
	 * derivative of this code cannot be changed.  i.e. this code cannot simply be
	 * copied and put under another distribution licence
	 * [including the GNU Public Licence.]
	 */

************************************************************************************
Google protocol buffers
************************************************************************************

	// Protocol Buffers - Google's data interchange format
	// Copyright 2008 Google Inc.  All rights reserved.
	// http://code.google.com/p/protobuf/
	//
	// Redistribution and use in source and binary forms, with or without
	// modification, are permitted provided that the following conditions are
	// met:
	//
	//     * Redistributions of source code must retain the above copyright
	// notice, this list of conditions and the following disclaimer.
	//     * Redistributions in binary form must reproduce the above
	// copyright notice, this list of conditions and the following disclaimer
	// in the documentation and/or other materials provided with the
	// distribution.
	//     * Neither the name of Google Inc. nor the names of its
	// contributors may be used to endorse or promote products derived from
	// this software without specific prior written permission.
	//
	// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	// Author: kenton@google.com (Kenton Varda)
	//  Based on original Protocol Buffers design by
	//  Sanjay Ghemawat, Jeff Dean, and others.

************************************************************************************
Google Snappy
************************************************************************************

	// Copyright 2005 Google Inc. All Rights Reserved.
	//
	// Redistribution and use in source and binary forms, with or without
	// modification, are permitted provided that the following conditions are
	// met:
	//
	//     * Redistributions of source code must retain the above copyright
	// notice, this list of conditions and the following disclaimer.
	//     * Redistributions in binary form must reproduce the above
	// copyright notice, this list of conditions and the following disclaimer
	// in the documentation and/or other materials provided with the
	// distribution.
	//     * Neither the name of Google Inc. nor the names of its
	// contributors may be used to endorse or promote products derived from
	// this software without specific prior written permission.
	//
	// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
