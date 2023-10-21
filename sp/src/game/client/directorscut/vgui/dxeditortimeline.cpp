//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "../directorscut.h"
#include "dxeditortimeline.h"
#include "vgui/ISurface.h"
#include "vgui/ILocalize.h"

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

DXEditorTimeline::DXEditorTimeline(Panel* pParent)
	: BaseClass(pParent, "Timeline")
{
}

void DXEditorTimeline::OnThink()
{
}

void DXEditorTimeline::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
	m_hFont = pScheme->GetFont("DefaultVerySmall");
}

void DXEditorTimeline::Paint()
{
	// TODO: store as member variables
	float startTime = -1; // seconds
	int zoomLevel = 100; // pixels per second

	int offset = 4;
	int w, h;
	GetSize(w, h);

	int x = offset;
	int y = offset;
	int offsetW = w - offset * 2;
	int offsetH = h - offset * 2;
	
	float playhead = DirectorsCutGameSystem().GetPlayhead();

	// background
	surface()->DrawSetColor(54, 54, 54, 255);
	surface()->DrawFilledRect(x, y, x + offsetW, y + offsetH);

	// top tick bar (black bar beneath)
	surface()->DrawSetColor(80, 80, 80, 255);
	surface()->DrawFilledRect(x, y, x + offsetW, y + 19);
	surface()->DrawSetColor(0, 0, 0, 255);
	surface()->DrawFilledRect(x, y + 19, x + offsetW, y + 20);

	// bottom tick bar (black bar above)
	surface()->DrawSetColor(80, 80, 80, 255);
	surface()->DrawFilledRect(x, y + offsetH - 19, x + offsetW, y + offsetH);
	surface()->DrawSetColor(0, 0, 0, 255);
	surface()->DrawFilledRect(x, y + offsetH - 20, x + offsetW, y + offsetH - 19);

	// tick marks
	for (float i = startTime; i < offsetW / zoomLevel; i += 0.1f)
	{
		// Round to nearest 0.1
		i = floor(i * 10 + 0.5f) / 10;

		// for in-between intervals, draw 2 px tick
		int hTick = 2;
		int yOffset = 17;
		// for half/full second intervals, draw 4 px tick
		if (i == (int)i || i == (int)i + 0.5f)
		{
			hTick += 2;
			yOffset -= 2;
		}

		surface()->DrawFilledRect(x + (i - startTime) * zoomLevel, y + yOffset, x + (i - startTime) * zoomLevel + 1, y + yOffset + hTick);
		surface()->DrawFilledRect(x + (i - startTime) * zoomLevel, y + offsetH - yOffset - hTick, x + (i - startTime) * zoomLevel + 1, y + offsetH - yOffset);

		// draw text above tick
		if (i == (int)i)
		{
			wchar_t text[32];
			V_swprintf_safe(text, L"%.0f", i);
			surface()->DrawSetTextColor(0, 0, 0, 255);
			surface()->DrawSetTextFont(m_hFont);

			surface()->DrawSetTextPos(x + (i - startTime) * zoomLevel, y + 2);
			surface()->DrawPrintText(text, wcslen(text));

			surface()->DrawSetTextPos(x + (i - startTime) * zoomLevel, y + offsetH - 16);
			surface()->DrawPrintText(text, wcslen(text));
		}
	}

	// document data
	int trackGroupHeaderBarHeight = 19;
	int trackGroupFooterBarHeight = 4;
	int trackGroupTextX = 36;
	int trackGroupCurOffset = 19;
	int trackOffsetX = 0;
	int clipHeight = 46;
	CDmxElement* pRoot = DirectorsCutGameSystem().GetDocument();
	
	// TODO: trackGroups attribute
	if( pRoot != NULL )
	{
		CDmxElement* pClip = pRoot->GetValue<CDmxElement*>( "activeClip" );
		if( pClip != NULL )
		{
			CDmxElement* pTimeFrame = pClip->GetValue<CDmxElement*>( "timeFrame" );
			if( pTimeFrame != NULL )
			{
				trackOffsetX = (pTimeFrame->GetValue<float>( "start" ) - startTime) * zoomLevel;
			}
			CDmxElement* pSubClipTrackGroup = pClip->GetValue<CDmxElement*>( "subClipTrackGroup" );
			if( pSubClipTrackGroup != NULL )
			{
				// Create "Picture" track group
				surface()->DrawSetColor(40, 40, 45, 255);
				surface()->DrawFilledRect(x, y + trackGroupCurOffset, x + offsetW, y + trackGroupCurOffset + trackGroupHeaderBarHeight);
				surface()->DrawSetTextColor(182, 182, 182, 255);
				surface()->DrawSetTextFont(m_hFont);
				surface()->DrawSetTextPos(x + trackGroupTextX, y + trackGroupCurOffset + 2);
				surface()->DrawPrintText(L"Picture", wcslen(L"Picture"));
				trackGroupCurOffset += trackGroupHeaderBarHeight;

				if(pSubClipTrackGroup->GetValue<bool>("minimized") == false)
				{
					const CUtlVector<CDmxElement*>& pTracks = pSubClipTrackGroup->GetArray<CDmxElement*>( "tracks" );
					if( pTracks.Count() != 0 )
					{
						for( int i = 0; i < pTracks.Count(); i++ )
						{
							CDmxElement* pTrack = pTracks[i];
							if( pTrack != NULL )
							{
								// Create track at current offset
								surface()->DrawSetColor(62, 62, 107, 255);
								surface()->DrawFilledRect(x, y + trackGroupCurOffset, x + offsetW, y + trackGroupCurOffset + trackGroupHeaderBarHeight);
								if( pTrack->GetValueString( "name" ) != NULL )
								{
									const char* name = pTrack->GetValueString( "name" );
									wchar_t wname[256];
									V_swprintf_safe(wname, L"%hs", name);
									surface()->DrawSetTextColor(182, 182, 182, 255);
									surface()->DrawSetTextFont(m_hFont);
									surface()->DrawSetTextPos(x + trackGroupTextX, y + trackGroupCurOffset + 2);
									surface()->DrawPrintText(wname, wcslen(wname));
								}
								trackGroupCurOffset += trackGroupHeaderBarHeight;
								if(pTrack->GetValue<bool>("minimized") == false)
								{
									const CUtlVector<CDmxElement*>& pChildren = pTrack->GetArray<CDmxElement*>( "children" );
									if( pChildren.Count() != 0 )
									{
										// Draw background
										surface()->DrawSetColor(46, 46, 54, 255);
										surface()->DrawFilledRect(x, y + trackGroupCurOffset, x + offsetW, y + trackGroupCurOffset + clipHeight);
										for( int j = 0; j < pChildren.Count(); j++ )
										{
											CDmxElement* pChild = pChildren[j];
											if( pChild != NULL )
											{
												// Create clip
												CDmxElement* pTimeFrameChild = pChild->GetValue<CDmxElement*>( "timeFrame" );
												float start = 0;
												float duration = 0; //, offset; , scale;
												if( pTimeFrameChild != NULL )
												{
													start = pTimeFrameChild->GetValue<float>( "start" );
													duration = pTimeFrameChild->GetValue<float>( "duration" );
													//offset = pTimeFrameChild->GetValue<float>( "offset" );
													//scale = pTimeFrameChild->GetValue<float>( "scale" );
												}
												surface()->DrawSetColor(63, 61, 128, 255);
												int minX = x + start * zoomLevel + trackOffsetX;
												int maxX = x + (start + duration) * zoomLevel + trackOffsetX;
												// make sure when drawing rect, maxX doesn't reach outside of offsetW
												if (maxX > x + offsetW)
													maxX = x + offsetW;
												surface()->DrawFilledRect(minX, y + trackGroupCurOffset, maxX, y + trackGroupCurOffset + clipHeight);
												if( pChild->GetValueString( "name" ) != NULL )
												{
													const char* name = pChild->GetValueString( "name" );
													wchar_t wname[256];
													V_swprintf_safe(wname, L"%hs", name);
													surface()->DrawSetTextColor(182, 182, 182, 255);
													surface()->DrawSetTextFont(m_hFont);
													surface()->DrawSetTextPos(x + start * zoomLevel + trackOffsetX + 2, y + trackGroupCurOffset + 2);
													surface()->DrawPrintText(wname, wcslen(wname));
												}
											}
										}
										trackGroupCurOffset += clipHeight;
									}
								}
								// Create footer bar
								surface()->DrawSetColor(40, 40, 45, 255);
								surface()->DrawFilledRect(x, y + trackGroupCurOffset, x + offsetW, y + trackGroupCurOffset + trackGroupFooterBarHeight);
								trackGroupCurOffset += trackGroupFooterBarHeight + 2;
							}
						}
					}
				}
			}
		}
	}

	// playhead
	surface()->DrawSetColor(129, 150, 173, 255);
	surface()->DrawFilledRect(x + (playhead - startTime) * zoomLevel, y, x + (playhead - startTime) * zoomLevel + 1, offsetH);
}
