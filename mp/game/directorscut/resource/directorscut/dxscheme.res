///////////////////////////////////////////////////////////
// Director's Cut scheme resource file
//
// sections:
//		Colors			- all the colors used by the scheme
//		BaseSettings	- contains settings for app to use to draw controls
//		Fonts			- list of all the fonts used by app
//		Borders			- description of all the borders
//
///////////////////////////////////////////////////////////
Scheme
{
	//////////////////////// COLORS ///////////////////////////
	// color details
	// this is a list of all the colors used by the scheme
	Colors
	{
		// base colors
		"White"				"255 255 255 255"
		"OffWhite"			"182 182 182 255"
		"DullWhite"			"142 142 142 255"
		"WhiteBorder"		"110 110 110 255"

		"Black"				"0 0 0 255"
		"Blank"				"0 0 0 0"

		"Red"               "255 128 128 255"
		"Green"             "128 255 128 255"
		"Blue"              "128 128 255 255"

		"DXMenuDark"       "38 38 39 255"
		"DXMenuDarkAlt1"   "54 54 54 255"
		"DXMenuDarkAlt2"   "44 44 45 255"

		"DXSelection"		"79 82 89 255"
		"DXInactive"		"32 32 31 255"
	}

	///////////////////// BASE SETTINGS ////////////////////////
	//
	// default settings for all panels
	// controls use these to determine their settings
	BaseSettings
	{
		// vgui_controls color specifications
		Border.Bright					"Blank"	// the lit side of a control
		Border.Dark						"Blank"		// the dark/unlit side of a control
		Border.Selection				"Blank"			// the additional border color for displaying the default/selected button

		Button.TextColor				"OffWhite"
		Button.BgColor					"DXMenuDark"
		Button.ArmedTextColor			"White"
		Button.ArmedBgColor				"DXMenuDarkAlt2"
		Button.DepressedTextColor		"White"
		Button.DepressedBgColor			"DXMenuDarkAlt2"
		Button.FocusBorderColor			"Blank"

		DXEditorPanelPage.BgColor			"DXMenuDarkAlt1"
		DXEditorPanelPage.SelectedBgColor	"DXMenuDarkAlt1"

		PageTab.ActiveColor "DXMenuDarkAlt1"
		PageTab.InactiveColor "DXMenuDark"

		CheckButton.TextColor			"OffWhite"
		CheckButton.SelectedTextColor	"White"
		CheckButton.BgColor				"DXMenuDarkAlt1"
		CheckButton.Border1  			"Border.Dark" 		// the left checkbutton border
		CheckButton.Border2  			"Border.Bright"		// the right checkbutton border
		CheckButton.Check				"White"				// color of the check itself
		CheckButton.ArmedBgColor "OffWhite"
		CheckButton.DepressedBgColor "OffWhite"
		CheckButton.HighlightFgColor "OffWhite"

		ComboBoxButton.ArrowColor		"DullWhite"
		ComboBoxButton.ArmedArrowColor	"White"
		ComboBoxButton.BgColor			"Blank"
		ComboBoxButton.DisabledBgColor	"Blank"

		ExpandButton.Color				"DXMenuDark"

		Frame.TitleTextInsetX			16
		Frame.ClientInsetX				8
		Frame.ClientInsetY				6
		Frame.BgColor					"DXMenuDark"
		Frame.OutOfFocusBgColor			"DXMenuDark"
		Frame.FocusTransitionEffectTime	"0.3"	// time it takes for a window to fade in/out on focus/out of focus
		Frame.TransitionEffectTime		"0.3"	// time it takes for a window to fade in/out on open/close
		Frame.AutoSnapRange				"8"
		// Frame.AutoSnapRange				"0"
		Frame.FocusBorderColor			"WhiteBorder"
		FrameGrip.Color1				"200 200 200 196"
		FrameGrip.Color2				"0 0 0 196"
		FrameTitleButton.FgColor		"200 200 200 196"
		FrameTitleButton.BgColor		"Blank"
		FrameTitleButton.DisabledFgColor	"255 255 255 192"
		FrameTitleButton.DisabledBgColor	"Blank"
		FrameSystemButton.FgColor		"Blank"
		FrameSystemButton.BgColor		"Blank"
		FrameSystemButton.Icon			""
		FrameSystemButton.DisabledIcon	""
		FrameTitleBar.Font				"UiBold"
		FrameTitleBar.TextColor			"White"
		FrameTitleBar.BgColor			"Blank"
		FrameTitleBar.DisabledTextColor	"DXMenuDarkAlt1"
		FrameTitleBar.DisabledBgColor	"Blank"
		FrameTitleBar.SmallFont				"UiBoldSmall"

		GraphPanel.FgColor				"White"
		GraphPanel.BgColor				"DXMenuDarkAlt1"

		Label.TextDullColor				"DullWhite"
		Label.TextColor					"OffWhite"
		Label.TextBrightColor			"White"
		Label.SelectedTextColor			"White"
		Label.BgColor					"Blank"
		Label.DisabledFgColor1			"117 117 117 255"
		Label.DisabledFgColor2			"30 30 30 255"

		ListPanel.TextColor					"OffWhite"
		ListPanel.TextBgColor				"Blank"
		ListPanel.BgColor					"DXMenuDarkAlt1"
		ListPanel.SelectedTextColor			"Black"
		ListPanel.SelectedBgColor			"DXSelection"
		ListPanel.SelectedOutOfFocusBgColor	"DXSelection"
		ListPanel.EmptyListInfoTextColor	"OffWhite"
		ListPanel.DisabledTextColor			"Label.DisabledFgColor1"
		ListPanel.DisabledSelectedTextColor			"OffWhite"

		IfmWorkspace.BgColor            "50 70 50 90"

		MenuBar.FgColor					"Blank"
		MenuBar.BgColor					"Blank"

		Menu.TextColor					"OffWhite"
		Menu.BgColor					"DXMenuDarkAlt1"
		Menu.ArmedTextColor				"White"
		Menu.ArmedBgColor				"DXSelection"
		Menu.SeparatorColor				"109 109 109 255"
		Menu.TextInset					"16"
		// Menu.Font                       "UiBoldSmall"

		Panel.FgColor					"DullWhite"
		Panel.BgColor					"Blank"

		ProgressBar.FgColor				"White"
		ProgressBar.BgColor				"DXMenuDarkAlt1"

		PropertySheet.BgColor			"DXMenuDark"
		PropertySheet.TextColor			"OffWhite"
		PropertySheet.SelectedBgColor	"DXMenuDarkAlt1"
		PropertySheet.SelectedTextColor	"White"
		PropertySheet.TransitionEffectTime	"0.25"	// time to change from one tab to another

		RadioButton.TextColor			"DullWhite"
		RadioButton.SelectedTextColor	"White"

		RichText.TextColor				"OffWhite"
		RichText.BgColor				"DXMenuDarkAlt2"
		RichText.SelectedTextColor		"Black"
		RichText.SelectedBgColor		"DXSelection"

		ScrollBar.Wide				14

		ScrollBarNobBorder.Outer "0 0 0 255"
		ScrollBarNobBorder.Inner "115 115 115 255"
		ScrollBarNobBorderHover.Inner "130 130 130 255"
		ScrollBarNobBorderDragging.Inner "80 80 80 255"

		ScrollBarButton.FgColor				"White"
		ScrollBarButton.BgColor				"Blank"
		ScrollBarButton.ArmedFgColor		"White"
		ScrollBarButton.ArmedBgColor		"Blank"
		ScrollBarButton.DepressedFgColor	"White"
		ScrollBarButton.DepressedBgColor	"Blank"

		ScrollBarSlider.Inset				1			// Number of pixels to inset scroll bar nob
		ScrollBarSlider.FgColor				"90 90 90 255"		// nob color
		ScrollBarSlider.BgColor				"Blank"		// slider background color
		ScrollBarSlider.NobFocusColor		"115 115 115 255"		// nob mouseover color
		ScrollBarSlider.NobDragColor		"66 66 66 255"		// nob active drag color

		SectionedListPanel.HeaderTextColor	"White"
		SectionedListPanel.HeaderBgColor	"Blank"
		SectionedListPanel.DividerColor		"Black"
		SectionedListPanel.TextColor		"DullWhite"
		SectionedListPanel.BrightTextColor	"White"
		SectionedListPanel.BgColor			"DXMenuDarkAlt1"
		SectionedListPanel.SelectedTextColor			"Black"
		SectionedListPanel.SelectedBgColor				"DXSelection"
		SectionedListPanel.OutOfFocusSelectedTextColor	"Black"
		SectionedListPanel.OutOfFocusSelectedBgColor	"DXSelection"

		Slider.NobColor				"108 108 108 255"
		Slider.TextColor			"180 180 180 255"
		Slider.TrackColor			"31 31 31 255"
		Slider.DisabledTextColor1	"117 117 117 255"
		Slider.DisabledTextColor2	"30 30 30 255"

		TextEntry.TextColor			"OffWhite"
		TextEntry.BgColor			"DXMenuDarkAlt2"
		TextEntry.CursorColor		"OffWhite"
		TextEntry.DisabledTextColor	"DullWhite"
		TextEntry.DisabledBgColor	"Blank"
		TextEntry.SelectedTextColor	"Black"
		TextEntry.SelectedBgColor	"DXSelection"
		TextEntry.OutOfFocusSelectedBgColor	"DXSelection"
		TextEntry.FocusEdgeColor	"0 0 0 196"

		ToggleButton.SelectedTextColor	"White"

		Tooltip.TextColor			"0 0 0 196"
		Tooltip.BgColor				"DXSelection"

		TreeView.BgColor			"DXInactive"

		WizardSubPanel.BgColor		"Blank"

		// scheme-specific colors
		MainMenu.TextColor			"White"
		MainMenu.ArmedTextColor		"200 200 200 255"
		MainMenu.DepressedTextColor	"192 186 80 255"
		MainMenu.MenuItemHeight		"30"
		MainMenu.Inset				"32"
		MainMenu.Backdrop			"255 0 0 156"

		Console.TextColor			"OffWhite"
		Console.DevTextColor		"White"

		NewGame.TextColor			"White"
		NewGame.FillColor			"0 0 0 255"
		NewGame.SelectionColor		"DXSelection"
		NewGame.DisabledColor		"128 128 128 196"

		DragDrop.DragFrame		"255 255 255 192"
		DragDrop.DropFrame		"150 255 150 255"

		AttributeWidget.DirtyBgColor "100 100 200 63"

		Clip.Selected				"DXSelection"
		Clip.Unselected				"150 150 150 255"

		Clip.BgColor				"Blank"
		Clip.ActiveBgColor			"255 255 255 50"

		Clip.TrackBorder			"0 0 0 255"

		// Color at insert cursor when dropping tracks onto a timeline view
		Clip.DropTimeColor			"255 255 255 255"
		Clip.DropTimeColorBg		"0 0 0 192"
		Clip.DropTimeColorBorder	"255 255 255 192"

		Clip.StartDragColor			"0 255 255 128"

		KeyBoardEditor.AlteredBinding		"100 255 100 255"
		StatusBar.BgColor 			"DXMenuDarkAlt1"

		FilmStrip.FilmBgColor		"75 75 220 128"
		FilmStrip.AudioBgColor		"75 220 75 128"
		FilmStrip.FXBgColor			"220 75 75 128"
		FilmStrip.ChannelsBgColor	"220 200 75 128"
		FilmStrip.FgColor			"31 31 31 128"

		TimeCode.BorderColor		"0 0 0 255"

		TimeCode.SubClipFgColor		"255 0 100 255"
		TimeCode.SubClipBgColor		"255 255 255 63"

		TimeCode.ClipFgColor		"100 100 255 255"
		TimeCode.ClipBgColor		"255 255 255 63"

		AnimSet.GroupColor					"0 128 255 255"
		AnimSet.RootColor					"128 128 128 255"
		AnimSet.ItemColor					"200 200 200 255"
		AnimSet.FullSelectionColor			"128 128 128 128"
		AnimSet.PartialSelectionColor		"128 128 64 64"
		AnimSet.ContextMenuSelectionColor	"DXMenuDark"

		IFM.CurrentTimeScrubber		"100 150 255 192"  // In the timeline views, the grabbable scrubber color
		IFM.CurrentTimeScrubberOutline	"0 0 0 0"  // In the timeline views, the outline around the bar and scrubber
		IFM.CurrentTimeBarColor		"100 150 255 192"

		IFM.ClipTransitionBgColor	"180 180 255 192"

		IFM.TimeLineBgColor			"0 0 0 128"

		IFM.TimeLineTickMajor		"255 255 63 192"
		IFM.TimeLineTickMinor		"255 255 63 127"
		IFM.TimeLineTickLabelColor	"255 255 255 127"

		IFM.TimeLinePreviewColor		"0   200 0 127"
		IFM.TimeLinePreviewModifyColor	"255 153 0 127"

		IFMConsole.TextColor		"216 222 211 255"
		IFMConsole.DevTextColor		"196 181 80 255"

		// It just oscillates between these two
		IFMDrop.BlinkCursor1		"255 255 0 255"
		IFMDrop.BlinkCursor2		"100 100 100 255"

		IFM.CurveOtherLayer			"150 150 150 255"
		IFM.CurveBaseLayer			"0 255 255 255"
		IFM.CurveWriteLayer			"220 200 50 255"

		SFM.TxFormPathTSLeftFalloffFace		"140 140 140 255"
		SFM.TxFormPathTSRightFalloffFace	"140 140 140 255"
		SFM.TxFormPathTSHoldFace			"4 162 0 255"

		SFM.TxFormPathTSLeftFalloffBorder	"255 255 255 255"
		SFM.TxFormPathTSRightFalloffBorder	"255 255 255 255"
		SFM.TxFormPathTSHoldBorder			"18 255 0 255"

		SFM.TxFormPathTSHeadFace			"80 130 235 255"
		SFM.TxFormPathTSHeadBorder			"100 150 255 255"

		SFM.TxFormPathTSPointOfInterestFace		"4 162 0 255"
		SFM.TxFormPathTSPointOfInterestBorder	"18 255 0 255"

		SFM.TxFormPathTSConnectorLineColor	"200 200 200 225"

		SFM.TxFormPathTSLeftFalloffBumperFace	"0 0 0 255"
		SFM.TxFormPathTSRightFalloffBumperFace	"255 255 0 255"
		SFM.TxFormPathTSLeftFalloffBumperBorder "255 255 0 255"
		SFM.TxFormPathTSRightFalloffBumperBorder "0 0 0 255"

		SFM.TxFormPathTSSelectionFace			"192 0 0 255"
		SFM.TxFormPathTSSelectionBorder			"255 64 64 255"
		SFM.TxFormPathTSSelectionBox			"255 255 0 192"
		SFM.TxFormPathTSSelectionBoxBorder		"0 0 0 192"

		SFM.GraphEditorBackgroundColor			"128 128 128 255"
		SFM.GraphEditorTimeBoundsColor			"32  32  32   96"
		SFM.GraphEditorGridColor				"64  64  64  255"
		SFM.GraphEditorFontColor				"255 255 255 255"
		SFM.GraphEditorCurveColor				"32  192 192 255"
		SFM.GraphEditorSegmentColor				"224 224 224 255"
		SFM.GraphEditorSelectionColor			"192 192 192 128"
		SFM.GraphEditorKeyColor					"0   0   0   255"
		SFM.GraphEditorKeySelectedColor			"255 255 32  255"
		SFM.GraphEditorKeyAddColor				"32  255 32  255"
		SFM.GraphEditorKeyRemoveColor			"64  64  255 255"
		SFM.GraphEditorTangentColor				"96  64  64  255"
		SFM.GraphEditorBrokenTangentColor		"64  64  128 255"
		SFM.GraphEditorCurveColorX				"255 0   0   255"
		SFM.GraphEditorCurveColorY				"0   255 0   255"
		SFM.GraphEditorCurveColorZ				"0   0   255 255"
		SFM.GraphEditorCrossHairColor			"0   0   0   255"

		SFM.GraphEditorOutlinerSelectionColor	"128 128 128 255"
		SFM.GraphEditorOutlinerChannelColor		"224 224 224 255"
		SFM.GraphEditorOutlinerChannelColorX	"255  64  64 255"
		SFM.GraphEditorOutlinerChannelColorY	"64  255  64 255"
		SFM.GraphEditorOutlinerChannelColorZ	"64   72 255 255"

		// Used in ComicCreator
		ComicCreator.PillBackgroundColor		"170 170 170 255"
		ComicCreator.PillTextColor					"0 0 0 255"
		ComicCreator.NoImageDashesColor			"170 170 170 255"
		// Not used in ComicCreator yet
		ComicCreator.SelectionColor					"248 139 0 255"
		ComicCreator.PanelBackgroundColor		"255 255 255 255"
		ComicCreator.PanelFrameColor				"0 0 0 255"
		ComicCreator.PanelForegroundColor		"0 0 0 255"
	}

	//
	//////////////////////// FONTS /////////////////////////////
	//
	// describes all the fonts
	Fonts
	{
		// fonts are used in order that they are listed
		// fonts listed later in the order will only be used if they fulfill a range not already filled
		// if a font fails to load then the subsequent fonts will replace
		// fonts are used in order that they are listed
		"DebugFixed"
		{
			"1"
			{
				"name"		"Courier New"
				"tall"		"10"
				"weight"	"500"
				"antialias" "1"
			}
		}
		// fonts are used in order that they are listed
		"DebugFixedSmall"
		{
			"1"
			{
				"name"		"Courier New"
				"tall"		"7"
				"weight"	"500"
				"antialias" "1"
			}
		}
		"DefaultFixedOutline"
		{
			"1"
			{
				"name"		"Lucida Console"
				"tall"		"10"
				"weight"	"0"
				"outline"	"1"
			}
		}
		"Default"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"12"
				"weight"	"800"
				"antialias" "1"
				// "dropshadow" "1"
			}
		}
		"DefaultBold"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"14"
				"weight"	"1000"
				"antialias" "1"
			}
		}
		"DefaultUnderline"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"16"
				"weight"	"500"
				"underline" "1"
			}
		}
		"DefaultSmall"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"12"
				"weight"	"0"
			}
		}
		"DefaultSmallDropShadow"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"13"
				"weight"	"0"
				"dropshadow" "1"
			}
		}
		"DefaultVerySmall"
		{
			"1"
			{
				"name"		"Tahoma"
				//"name"		"Verdana"
				"tall"		"12"
				"weight"	"0"
				"antialias" "1"
			}
		}

		"DefaultLarge"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"18"
				"weight"	"0"
			}
		}
		"DefaultLargeOutline"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"32"
				"weight"	"1000"
				"outline"	"1"
				"antialias" "1"
			}
		}

		"UiBold"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"12"
				"weight"	"1000"
			}
		}
		"UiBoldSmall"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"12"
				"weight"	"1000"
				"antialias" "1"
			}
		}

		"DmePropertyVerySmall"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"12"
				"weight"	"0"
				"antialias" "1"
			}
		}

		"DmePropertySmall"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"13"
				"weight"	"0"
				"antialias" "1"
			}
		}

		"DmeProperty"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"14"
				"weight"	"0"
				"antialias" "1"
			}
		}

		"DmePropertyLarge"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"18"
				"weight"	"0"
				"antialias" "1"
			}
		}

		"DmePropertyVeryLarge"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"22"
				"weight"	"0"
				"antialias" "1"
			}
		}

		"MenuLarge"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"16"
				"weight"	"600"
				"antialias" "1"
			}
		}

		"ConsoleText"
		{
			"1"
			{
				"name"		"Lucida Console"
				"tall"		"10"
				"weight"	"500"
			}
		}

		// this is the symbol font
		"Marlett"
		{
			"1"
			{
				"name"		"Marlett"
				"tall"		"14"
				"weight"	"0"
				"symbol"	"1"
			}
		}
		"MarlettSmall"
		{
			"1"
			{
				"name"		"Marlett"
				"tall"		"10"
				"weight"	"0"
				"symbol"	"1"
			}
		}
		"Trebuchet24"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"24"
				"weight"	"900"
			}
		}


		"Trebuchet20"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"20"
				"weight"	"900"
			}
		}

		"Trebuchet18"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"18"
				"weight"	"900"
			}
		}

		// HUD numbers
		// We use multiple fonts to 'pulse' them in the HUD, hence the need for many of near size
		"HUDNumber"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"40"
				"weight"	"900"
			}
		}
		"HUDNumber1"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"41"
				"weight"	"900"
			}
		}
		"HUDNumber2"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"42"
				"weight"	"900"
			}
		}
		"HUDNumber3"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"43"
				"weight"	"900"
			}
		}
		"HUDNumber4"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"44"
				"weight"	"900"
			}
		}
		"HUDNumber5"
		{
			"1"
			{
				"name"		"Trebuchet MS"
				"tall"		"45"
				"weight"	"900"
			}
		}
		"DefaultFixed"
		{
			"1"
			{
				"name"		"Lucida Console"
				"tall"		"10"
				"weight"	"0"
			}
//			"1"
//			{
//				"name"		"FixedSys"
//				"tall"		"20"
//				"weight"	"0"
//			}
		}

		"DefaultFixedDropShadow"
		{
			"1"
			{
				"name"		"Lucida Console"
				"tall"		"10"
				"weight"	"0"
				"dropshadow" "1"
			}
//			"1"
//			{
//				"name"		"FixedSys"
//				"tall"		"20"
//				"weight"	"0"
//			}
		}

		"CloseCaption_Normal"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"16"
				"weight"	"500"
			}
		}
		"CloseCaption_Italic"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"16"
				"weight"	"500"
				"italic"	"1"
			}
		}
		"CloseCaption_Bold"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"16"
				"weight"	"900"
			}
		}
		"CloseCaption_BoldItalic"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"16"
				"weight"	"900"
				"italic"	"1"
			}
		}

		TitleFont
		{
			"1"
			{
				"name"		"HALFLIFE"
				"tall"		"72"
				"weight"	"400"
				"antialias"	"1"
				"custom"	"1"
			}
		}

		TitleFont2
		{
			"1"
			{
				"name"		"HALFLIFE2"
				"tall"		"120"
				"weight"	"400"
				"antialias"	"1"
				"custom"	"1"
			}
		}

		VCRControls
		{
			"1"
			{
				"name"		"HALFLIFE2"
				"tall"		"32"
				"weight"	"400"
				"antialias"	"1"
				"custom"	"1"
			}
		}
	}

	//
	//////////////////// BORDERS //////////////////////////////
	//
	// describes all the border types
	Borders
	{
		BaseBorder		DepressedBorder
		ButtonBorder	RaisedBorder
		ComboBoxBorder	DepressedBorder
		MenuBorder		RaisedBorder
		BrowserBorder	DepressedBorder
		PropertySheetBorder	RaisedBorder

		FrameBorder
		{
			// rounded corners for frames
			"backgroundtype" "2"
		}

		DepressedBorder
		{
			"backgroundtype" "2"
			"inset" "0 0 1 1"
			Left
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 1"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "1 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}

			Bottom
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 0"
				}
			}
		}
		RaisedBorder
		{
			"backgroundtype" "2"
			"inset" "0 0 1 1"
			Left
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 1"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 1"
				}
			}

			Bottom
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}
		}
		
		TitleButtonBorder
		{
			"backgroundtype" "2"
		}

		TitleButtonDisabledBorder
		{
			"backgroundtype" "2"
		}

		TitleButtonDepressedBorder
		{
			"backgroundtype" "2"
		}

		ScrollBarButtonBorder
		{
			"backgroundtype" "2"
			"inset" "2 2 0 0" [!$OSX]
			"inset" "-3 2 0 0" [$OSX]
			Left
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 1"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "1 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 0"
				}
			}

			Bottom
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}
		}
		
		ScrollBarButtonDepressedBorder
		{
			"backgroundtype" "2"
			"inset" "2 2 0 0" [!$OSX]
			"inset" "-3 2 0 0" [$OSX]
			Left
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 1"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "1 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}

			Bottom
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 0"
				}
			}
		}

		TabBorder
		{
			"backgroundtype" "2"
			"inset" "0 0 1 1"
			Left
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 1"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "1 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 0"
				}
			}

		}

		TabActiveBorder
		{
			"backgroundtype" "2"
			"inset" "0 0 1 0"
			Left
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 0"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "1 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 0"
				}
			}

		}


		ToolTipBorder
		{
			"backgroundtype" "2"
			"inset" "0 0 1 0"
			Left
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "1 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}

			Bottom
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}
		}

		// this is the border used for default buttons (the button that gets pressed when you hit enter)
		ButtonKeyFocusBorder
		{
			"backgroundtype" "2"
			"inset" "0 0 1 1"
			Left
			{
				"1"
				{
					"color" "Border.Selection"
					"offset" "0 0"
				}
				"2"
				{
					"color" "Border.Bright"
					"offset" "0 1"
				}
			}
			Top
			{
				"1"
				{
					"color" "Border.Selection"
					"offset" "0 0"
				}
				"2"
				{
					"color" "Border.Bright"
					"offset" "1 0"
				}
			}
			Right
			{
				"1"
				{
					"color" "Border.Selection"
					"offset" "0 0"
				}
				"2"
				{
					"color" "Border.Dark"
					"offset" "1 0"
				}
			}
			Bottom
			{
				"1"
				{
					"color" "Border.Selection"
					"offset" "0 0"
				}
				"2"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}
		}

		ButtonDepressedBorder
		{
			"backgroundtype" "2"
			"inset" "2 1 1 1"
			Left
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 1"
				}
			}

			Right
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "1 0"
				}
			}

			Top
			{
				"1"
				{
					"color" "Border.Dark"
					"offset" "0 0"
				}
			}

			Bottom
			{
				"1"
				{
					"color" "Border.Bright"
					"offset" "0 0"
				}
			}
		}
	}

	//////////////////////// CUSTOM FONT FILES /////////////////////////////
	//
	// specifies all the custom (non-system) font files that need to be loaded to service the above described fonts
	CustomFontFiles
	{
		"1"		"resource/HALFLIFE2.vfont"
		"2"		"resource/BOXROCKET.vfont"
	}
}
