//========= Director's Cut - https://github.com/KiwifruitDev/DirectorsCut =========//
//
// Purpose: Editor window controls for Director's Cut.
// Contributors:
// - KiwifruitDev
//
// $NoKeywords: $
//=================================================================================//

#include "cbase.h"

#include "../directorscut.h"
#include "dxeditortimeline.h"
#include "vgui/ISurface.h"
#include "vgui/ILocalize.h"
#include "../data/dxe_track.h"

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
	float startTime = DirectorsCutGameSystem().GetTimelineStart(); // seconds
	int zoomLevel = DirectorsCutGameSystem().GetZoomLevel(); // pixels per second
	bool locked = DirectorsCutGameSystem().GetLockPlayhead();

	int offset = 4;
	int w, h;
	GetSize(w, h);

	int x = offset;
	int y = offset;
	int offsetW = w - offset * 2;
	int offsetH = h - offset * 2;
	
	float playhead = DirectorsCutGameSystem().GetPlayhead();

	// if locked, lock view to center on playhead
	if (locked)
	{
		startTime = playhead - offsetW / zoomLevel / 2;
		DirectorsCutGameSystem().SetTimelineStart(startTime);
	}

	// catch up with the playhead
	if (playhead > startTime + (offsetW / zoomLevel))
	{
		// shift the view by what's visible on screen
		startTime += (offsetW / zoomLevel);
		DirectorsCutGameSystem().SetTimelineStart(startTime);
	}
	else if (playhead < startTime)
	{
		// shift the view by what's visible on screen
		startTime -= (offsetW / zoomLevel);
		DirectorsCutGameSystem().SetTimelineStart(startTime);
	}

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
	for (float i = startTime; i < startTime + (offsetW / zoomLevel) + 1; i += 0.1f)
	{
		// Round to nearest 0.1
		i = floor(i * 10 + 0.5f) / 10;

		// if x + (i - startTime) * zoomLevel is outside of offsetW, stop drawing ticks
		if (x + (i - startTime) * zoomLevel > x + offsetW)
			break;

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

	if(!DirectorsCutGameSystem().GetFileOpen())
		return;

	// document data
	int trackGroupHeaderBarHeight = 19;
	int trackGroupFooterBarHeight = 4;
	int trackGroupTextX = 36;
	int trackGroupCurOffset = 19;
	int trackOffsetX = 0;
	int clipHeight = 46;
	DxeFilmClip* pMovie = DirectorsCutGameSystem().GetMovie();
	DxeTimeFrame* pTimeFrame = pMovie->GetTimeFrame();
	if( pTimeFrame != NULL )
	{
		trackOffsetX = (pTimeFrame->GetStart() - startTime) * zoomLevel;
	}
	DxeTrackGroup* pSubClipTrackGroup = pMovie->GetSubClipTrackGroup();
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

		if(pSubClipTrackGroup->GetMinimized() == false)
		{
			for( int i = 0; i < pSubClipTrackGroup->GetTracks()->GetSize(); i++)
			{
				DxeTrack* pTrack = (DxeTrack*)pSubClipTrackGroup->GetTracks()->GetElement(i);
				if( pTrack != NULL )
				{
					// Create track at current offset
					surface()->DrawSetColor(62, 62, 107, 255);
					surface()->DrawFilledRect(x, y + trackGroupCurOffset, x + offsetW, y + trackGroupCurOffset + trackGroupHeaderBarHeight);

					// Draw name
					const char* name = pTrack->GetElementName();
					wchar_t wname[256];
					V_swprintf_safe(wname, L"%hs", name);
					surface()->DrawSetTextColor(182, 182, 182, 255);
					surface()->DrawSetTextFont(m_hFont);
					surface()->DrawSetTextPos(x + trackGroupTextX, y + trackGroupCurOffset + 2);
					surface()->DrawPrintText(wname, wcslen(wname));

					// Draw clips
					trackGroupCurOffset += trackGroupHeaderBarHeight;
					if(pTrack->GetCollapsed() == false)
					{
						if(pTrack->GetChildren()->GetSize() > 0)
						{
							// Draw background
							surface()->DrawSetColor(46, 46, 54, 255);
							surface()->DrawFilledRect(x, y + trackGroupCurOffset, x + offsetW, y + trackGroupCurOffset + clipHeight);
							for( int j = 0; j < pTrack->GetChildren()->GetSize(); j++)
							{
								DxeFilmClip* pChild = (DxeFilmClip*)pTrack->GetChildren()->GetElement(j);
								if(pChild == NULL)
									continue;
								// Create clip
								DxeTimeFrame* pTimeFrameChild = pChild->GetTimeFrame();
								float start = 0;
								float duration = 0; //, offset; , scale;
								start = pTimeFrameChild->GetStart();
								duration = pTimeFrameChild->GetDuration();
								//offset = pTimeFrameChild->GetValue<float>( "offset" );
								//scale = pTimeFrameChild->GetValue<float>( "scale" );
								surface()->DrawSetColor(63, 61, 128, 255);
								int minX = x + start * zoomLevel + trackOffsetX;
								int maxX = x + (start + duration) * zoomLevel + trackOffsetX;
								// make sure when drawing rect, maxX doesn't reach outside of offsetW
								if (maxX > x + offsetW)
									maxX = x + offsetW;
								surface()->DrawFilledRect(minX, y + trackGroupCurOffset, maxX, y + trackGroupCurOffset + clipHeight);

								// Draw name
								const char* name = pChild->GetElementName();
								wchar_t wname[256];
								V_swprintf_safe(wname, L"%hs", name);
								surface()->DrawSetTextColor(182, 182, 182, 255);
								surface()->DrawSetTextFont(m_hFont);
								surface()->DrawSetTextPos(x + start * zoomLevel + trackOffsetX + 2, y + trackGroupCurOffset + 2);
								surface()->DrawPrintText(wname, wcslen(wname));
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

	// playhead
	if(!locked) // blue
		surface()->DrawSetColor(129, 150, 173, 255);
	else // magenta
		surface()->DrawSetColor(173, 129, 150, 255);
	surface()->DrawFilledRect(x + (playhead - startTime) * zoomLevel, y, x + (playhead - startTime) * zoomLevel + 1, offsetH);
}
