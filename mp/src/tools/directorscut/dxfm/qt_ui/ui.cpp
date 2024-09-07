#include <QPixmap>
#include <QSlider>
#include <QDialog>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopWidget>

#include <materialsystem/imesh.h>
#include <materialsystem/itexture.h>
#include <tier2/camerautils.h>
#include <istudiorender.h>
#include <KeyValues.h>

#include "ui.h"
#include "aboutdialog.h"
#include "welcomewizarddialog.h"

#include "dxfm.h"

CMainWindow::CMainWindow(QWidget* pParent) : QMainWindow(pParent)
{
	// Set up this window's properties
	QIcon icon;
	icon.addFile("tools:/images/dxfm/dxfm_app.png", QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);
	setWindowTitle(DXFM_PRODUCT_NAME_FULL);
	resize(1344, 801);

	keyboardShortcutsDialog = new CKeyboardShortcutsDialog(this);
	
	// center the window
	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	// FIXME: hardcoded values from Windows 11
	int taskbarHeight = 48;
	int borderOffsetX = 1;
	int borderOffsetY = 31;
	int desktopWidth = screenGeometry.width();
	int desktopHeight = screenGeometry.height() - taskbarHeight;
	int x = (desktopWidth - width()) / 2;
	int y = (desktopHeight - height()) / 2;
	move(x - borderOffsetX, y - borderOffsetY);

	// Add menu bar and populate it
	menubar = new QMenuBar(this);
	menubar->setGeometry(QRect(0, 0, 1344, 27));
	setMenuBar(menubar);

	// File menu
	menuFile = new QMenu("File", menubar);
	menubar->addAction(menuFile->menuAction());

		actionNew = new QAction("New", this);
		actionNew->setShortcut(QKeySequence::fromString("Ctrl+N"));
		actionNew->setDisabled(true);
		menuFile->addAction(actionNew);

		actionOpen = new QAction("Open...", this);
		actionOpen->setShortcut(QKeySequence::fromString("Ctrl+O"));
		actionOpen->setDisabled(true);
		menuFile->addAction(actionOpen);

		actionSave = new QAction("Save", this);
		actionSave->setShortcut(QKeySequence::fromString("Ctrl+S"));
		actionSave->setDisabled(true);
		menuFile->addAction(actionSave);

		actionSave_As = new QAction("Save As...", this);
		actionSave_As->setDisabled(true);
		menuFile->addAction(actionSave_As);

		actionClose = new QAction("Close", this);
		actionClose->setDisabled(true);
		menuFile->addAction(actionClose);

		menuFile->addSeparator();

		menuPerforce = new QMenu("Perforce", menuFile);
		menuPerforce->setDisabled(true);
		menuFile->addMenu(menuPerforce);

			actionAdd = new QAction("Add", this);
			actionAdd->setDisabled(true);
			menuPerforce->addAction(actionAdd);

			actionCheckout = new QAction("Checkout", this);
			actionCheckout->setDisabled(true);
			menuPerforce->addAction(actionCheckout);

			actionRevert = new QAction("Revert", this);
			actionRevert->setDisabled(true);
			menuPerforce->addAction(actionRevert);

			actionSubmit = new QAction("Submit", this);
			actionSubmit->setDisabled(true);
			menuPerforce->addAction(actionSubmit);

			menuPerforce->addSeparator();

			actionList_Open_Files = new QAction("List Open Files", this);
			actionList_Open_Files->setDisabled(true);
			menuPerforce->addAction(actionList_Open_Files);

			menuPerforce->addSeparator();

			actionView_In_P4Win = new QAction("View in P4Win", this);
			actionView_In_P4Win->setDisabled(true);
			menuPerforce->addAction(actionView_In_P4Win);

			actionView_In_P4V = new QAction("View in P4V", this);
			actionView_In_P4V->setDisabled(true);
			menuPerforce->addAction(actionView_In_P4V);

			menuPerforce->addSeparator();

			actionCheck_For_Perforce = new QAction("Check for Perforce", this);
			actionCheck_For_Perforce->setDisabled(true);
			menuPerforce->addAction(actionCheck_For_Perforce);

		menuRecent = new QMenu("Recent", menuFile);
		menuRecent->setDisabled(true);
		menuFile->addMenu(menuRecent);

			menuRecent->addSeparator();

			actionClear_Recent = new QAction("Clear Recent", this);
			actionClear_Recent->setDisabled(true);
			menuRecent->addAction(actionClear_Recent);

		menuFile->addSeparator();

		actionLoad_Map = new QAction("Load Map", this);
		actionLoad_Map->setShortcut(QKeySequence::fromString("Ctrl+L"));
		actionLoad_Map->setDisabled(true);
		menuFile->addAction(actionLoad_Map);

		menuFile->addSeparator();

		menuImport = new QMenu("Import", menuFile);
		menuImport->setDisabled(true);
		menuFile->addMenu(menuImport);

			actionRender_Settings = new QAction("Render Settings", this);
			actionRender_Settings->setDisabled(true);
			menuImport->addAction(actionRender_Settings);

			actionMovie_Settings = new QAction("Movie Settings", this);
			actionMovie_Settings->setDisabled(true);
			menuImport->addAction(actionMovie_Settings);

		menuExport = new QMenu("Export", menuFile);
		menuExport->setDisabled(true);
		menuFile->addMenu(menuExport);

			actionMovie = new QAction("Movie", this);
			actionMovie->setDisabled(true);
			menuExport->addAction(actionMovie);

			actionPoster = new QAction("Poster", this);
			actionPoster->setDisabled(true);
			menuExport->addAction(actionPoster);

			actionImage = new QAction("Image", this);
			actionImage->setDisabled(true);
			menuExport->addAction(actionImage);

			menuExport->addSeparator();

			actionImage_To_Clipboard = new QAction("Image to Clipboard", this);
			actionImage_To_Clipboard->setDisabled(true);
			menuExport->addAction(actionImage_To_Clipboard);

			menuExport->addSeparator();

			actionRender_Settings2 = new QAction("Render Settings", this);
			actionRender_Settings2->setDisabled(true);
			menuExport->addAction(actionRender_Settings2);

			actionMovie_Settings2 = new QAction("Movie Settings", this);
			actionMovie_Settings2->setDisabled(true);
			menuExport->addAction(actionMovie_Settings2);

		menuCommunity = new QMenu("Community", menuFile);
		menuCommunity->setDisabled(true);
		menuFile->addMenu(menuCommunity);

			actionPublish_Video_To_YouTube_And_Steam = new QAction("Publish Video to YouTube and Steam", this);
			actionPublish_Video_To_YouTube_And_Steam->setDisabled(true);
			menuCommunity->addAction(actionPublish_Video_To_YouTube_And_Steam);

			actionPublish_Image_To_Steam = new QAction("Publish Image to Steam", this);
			actionPublish_Image_To_Steam->setDisabled(true);
			menuCommunity->addAction(actionPublish_Image_To_Steam);

			menuPublish_To_Steam_Workshop = new QMenu("Publish to Steam Workshop", menuCommunity);
			menuPublish_To_Steam_Workshop->setDisabled(true);
			menuCommunity->addMenu(menuPublish_To_Steam_Workshop);

				actionSounds = new QAction("Sounds", this);
				actionSounds->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionSounds);

				actionModels = new QAction("Models", this);
				actionModels->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionModels);

				actionMaps = new QAction("Maps", this);
				actionMaps->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionMaps);

				actionParticles = new QAction("Particles", this);
				actionParticles->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionParticles);

				actionScripts = new QAction("Scripts", this);
				actionScripts->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionScripts);

				actionMaterials = new QAction("Materials", this);
				actionMaterials->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionMaterials);

				actionTextures = new QAction("Textures", this);
				actionTextures->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionTextures);

				actionSessions = new QAction("Sessions", this);
				actionSessions->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionSessions);

				actionShots = new QAction("Shots", this);
				actionShots->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionShots);

				actionAnimations = new QAction("Animations", this);
				actionAnimations->setDisabled(true);
				menuPublish_To_Steam_Workshop->addAction(actionAnimations);

			menuUpdate_Published_Item = new QMenu("Update Published Item", menuCommunity);
			menuUpdate_Published_Item->setDisabled(true);
			menuCommunity->addMenu(menuUpdate_Published_Item);

				menuUpdate_Published_Item->addSeparator();

				actionRefresh_Published_Item_List = new QAction("Refresh Published Item List", this);
				actionRefresh_Published_Item_List->setDisabled(true);
				menuUpdate_Published_Item->addAction(actionRefresh_Published_Item_List);

			menuBrowse_To_Your_Published_Items = new QMenu("Browse To Your Published Items", menuCommunity);
			menuBrowse_To_Your_Published_Items->setDisabled(true);
			menuCommunity->addMenu(menuBrowse_To_Your_Published_Items);

				actionVideos = new QAction("Videos", this);
				actionVideos->setDisabled(true);
				menuBrowse_To_Your_Published_Items->addAction(actionVideos);

				actionImages = new QAction("Images", this);
				actionImages->setDisabled(true);
				menuBrowse_To_Your_Published_Items->addAction(actionImages);

				actionWorkshop = new QAction("Workshop", this);
				actionWorkshop->setDisabled(true);
				menuBrowse_To_Your_Published_Items->addAction(actionWorkshop);

			menuBrowse_To_All_Published_Items = new QMenu("Browse To All Published Items", menuCommunity);
			menuBrowse_To_All_Published_Items->setDisabled(true);
			menuCommunity->addMenu(menuBrowse_To_All_Published_Items);

				actionVideos2 = new QAction("Videos", this);
				actionVideos2->setDisabled(true);
				menuBrowse_To_All_Published_Items->addAction(actionVideos2);

				actionImages2 = new QAction("Images", this);
				actionImages2->setDisabled(true);
				menuBrowse_To_All_Published_Items->addAction(actionImages2);

				actionWorkshop2 = new QAction("Workshop", this);
				actionWorkshop2->setDisabled(true);
				menuBrowse_To_All_Published_Items->addAction(actionWorkshop2);

			menuCommunity->addSeparator();

			actionShow_Used_Workshop_Items = new QAction("Show Used Workshop Items", this);
			actionShow_Used_Workshop_Items->setDisabled(true);
			menuCommunity->addAction(actionShow_Used_Workshop_Items);

		menuDownloadable_Content = new QMenu("Downloadable Content", menuFile);
		menuDownloadable_Content->setDisabled(true);
		menuFile->addMenu(menuDownloadable_Content);

			actionInstall_Day_Of_Defeat_Content_Pack = new QAction("Install Day Of Defeat Content Pack", this);
			actionInstall_Day_Of_Defeat_Content_Pack->setDisabled(true);
			menuDownloadable_Content->addAction(actionInstall_Day_Of_Defeat_Content_Pack);

			actionInstall_Portal_Content_Pack = new QAction("Install Portal Content Pack", this);
			actionInstall_Portal_Content_Pack->setDisabled(true);
			menuDownloadable_Content->addAction(actionInstall_Portal_Content_Pack);

			actionInstall_Blade_Symphony_Content_Pack = new QAction("Install Blade Symphony Content Pack", this);
			actionInstall_Blade_Symphony_Content_Pack->setDisabled(true);
			menuDownloadable_Content->addAction(actionInstall_Blade_Symphony_Content_Pack);

			actionInstall_Black_Mesa_Content_Pack = new QAction("Install Black Mesa Content Pack", this);
			actionInstall_Black_Mesa_Content_Pack->setDisabled(true);
			menuDownloadable_Content->addAction(actionInstall_Black_Mesa_Content_Pack);

			actionInstall_Left_4_Dead_Content_Pack = new QAction("Install Left 4 Dead Content Pack", this);
			actionInstall_Left_4_Dead_Content_Pack->setDisabled(true);
			menuDownloadable_Content->addAction(actionInstall_Left_4_Dead_Content_Pack);

			actionInstall_Dino_D_Day_Content_Pack = new QAction("Install Dino D-Day Content Pack", this);
			actionInstall_Dino_D_Day_Content_Pack->setDisabled(true);
			menuDownloadable_Content->addAction(actionInstall_Dino_D_Day_Content_Pack);

			actionInstall_The_Stanley_Parable_Content_Pack = new QAction("Install The Stanley Parable Content Pack", this);
			actionInstall_The_Stanley_Parable_Content_Pack->setDisabled(true);
			menuDownloadable_Content->addAction(actionInstall_The_Stanley_Parable_Content_Pack);
		
		menuFile->addSeparator();

		actionQuit = new QAction("Quit", this);
		connect(actionQuit, &QAction::triggered, this, [this]() {
			// TODO: ask user to save document
			engine->ClientCmd_Unrestricted("quit prompt");
			g_pDXFM->SetToolActive(false);
		});
    	menuFile->addAction(actionQuit);

	// Edit menu
	menuEdit = new QMenu("Edit", menubar);
	menuEdit->setDisabled(true);
	menubar->addAction(menuEdit->menuAction());

		actionUndo = new QAction("Undo", this);
		actionUndo->setShortcut(QKeySequence::fromString("Ctrl+Z"));
		actionUndo->setDisabled(true);
		menuEdit->addAction(actionUndo);
		
		actionRedo = new QAction("Redo", this);
		actionRedo->setShortcut(QKeySequence::fromString("Ctrl+Shift+Z"));
		actionRedo->setDisabled(true);
		menuEdit->addAction(actionRedo);

		menuEdit->addSeparator();

		actionCut = new QAction("Cut", this);
		actionCut->setShortcut(QKeySequence::fromString("Ctrl+X"));
		actionCut->setDisabled(true);
		menuEdit->addAction(actionCut);

		actionCopy = new QAction("Copy", this);
		actionCopy->setShortcut(QKeySequence::fromString("Ctrl+C"));
		actionCopy->setDisabled(true);
		menuEdit->addAction(actionCopy);

		actionPaste = new QAction("Paste", this);
		actionPaste->setShortcut(QKeySequence::fromString("Ctrl+V"));
		actionPaste->setDisabled(true);
		menuEdit->addAction(actionPaste);

		actionDelete = new QAction("Delete", this);
		actionDelete->setShortcut(QKeySequence::fromString("Del"));
		actionDelete->setDisabled(true);
		menuEdit->addAction(actionDelete);

	// Windows menu
	menuWindows = new QMenu("Windows", menubar);
	menubar->addAction(menuWindows->menuAction());

		actionElement_Viewer = new QAction("Element Viewer", this);
		actionElement_Viewer->setShortcut(QKeySequence::fromString("F9"));
		connect(actionElement_Viewer, &QAction::triggered, this, [this]() {
			tabWidget->setCurrentIndex(1);
		});
		menuWindows->addAction(actionElement_Viewer);

		menuWindows->addSeparator();

		actionClip_Editor = new QAction("Clip Editor", this);
		actionClip_Editor->setShortcut(QKeySequence::fromString("F2"));
		actionClip_Editor->setDisabled(true);
		menuWindows->addAction(actionClip_Editor);

		actionMotion_Editor = new QAction("Motion Editor", this);
		actionMotion_Editor->setShortcut(QKeySequence::fromString("F3"));
		actionMotion_Editor->setDisabled(true);
		menuWindows->addAction(actionMotion_Editor);

		actionGraph_Editor = new QAction("Graph Editor", this);
		actionGraph_Editor->setShortcut(QKeySequence::fromString("F4"));
		actionGraph_Editor->setDisabled(true);
		menuWindows->addAction(actionGraph_Editor);

		actionAnimation_Set_Editor = new QAction("Animation Set Editor", this);
		connect(actionAnimation_Set_Editor, &QAction::triggered, this, [this]() {
			tabWidget->setCurrentIndex(0);
		});
		menuWindows->addAction(actionAnimation_Set_Editor);

		menuWindows->addSeparator();

		actionPrimary_Viewport = new QAction("Primary Viewport", this);
		connect(actionPrimary_Viewport, &QAction::triggered, this, [this]() {
			tabWidget_2->setCurrentIndex(0);
		});
		menuWindows->addAction(actionPrimary_Viewport);

		actionSecondary_Viewport = new QAction("Secondary Viewport", this);
		actionSecondary_Viewport->setDisabled(true);
		menuWindows->addAction(actionSecondary_Viewport);

		menuWindows->addSeparator();

		actionConsole = new QAction("Console", this);
		connect(actionConsole, &QAction::triggered, this, [this]() {
			tabWidget_2->setCurrentIndex(1);
		});
		menuWindows->addAction(actionConsole);

		actionScript_Editor = new QAction("Script Editor", this);
		actionScript_Editor->setDisabled(true);
		menuWindows->addAction(actionScript_Editor);

		actionHistory = new QAction("History", this);
		actionHistory->setDisabled(true);
		menuWindows->addAction(actionHistory);

		menuWindows->addSeparator();

		actionParticle_Editor_Tool = new QAction("Particle Editor Tool", this);
		connect(actionParticle_Editor_Tool, &QAction::triggered, this, [this]() {
			int toolCount = enginetools->GetToolCount();
			for (int i = 0; i < toolCount; i++)
			{
				if (!Q_stricmp("Particle Editor", enginetools->GetToolName(i)))
				{
					enginetools->SwitchToTool(i);
					return;
				}
			}
		});
		menuWindows->addAction(actionParticle_Editor_Tool);

		actionEnter_Game_Mode = new QAction("Enter Game Mode", this);
		actionEnter_Game_Mode->setShortcut(QKeySequence::fromString("F11"));
		connect(actionEnter_Game_Mode, &QAction::triggered, this, [this]() {
			g_pDXFM->ToggleTool();
		});
		menuWindows->addAction(actionEnter_Game_Mode);

		menuEngine_Window = new QMenu("Engine Window", menuWindows);
		menuWindows->addAction(menuEngine_Window->menuAction());

			actionAuto_Hide_Engine_Window = new QAction("Auto Hide Engine Window", this);
			actionAuto_Hide_Engine_Window->setCheckable(true);
			actionAuto_Hide_Engine_Window->setChecked(true);
			connect(actionAuto_Hide_Engine_Window, &QAction::triggered, this, [this]() {
				bool hide = actionAuto_Hide_Engine_Window->isChecked();
				g_pDXFM->SetShouldHideEngineWindow(hide);
				g_pDXFM->HideOrShowEngineWindow(hide);
			});
			menuEngine_Window->addAction(actionAuto_Hide_Engine_Window);

		menuWindows->addSeparator();

		actionShow_All_Windows = new QAction("Show All Windows", this);
		actionShow_All_Windows->setDisabled(true);
		menuWindows->addAction(actionShow_All_Windows);

		menuWindows->addSeparator();

		menuLayout = new QMenu("Layout", menuWindows);
		menuLayout->setDisabled(true);
		menuWindows->addMenu(menuLayout);

			actionReturn_To_Default_Layout = new QAction("Return to Default Layout", this);
			actionReturn_To_Default_Layout->setDisabled(true);
			menuLayout->addAction(actionReturn_To_Default_Layout);

			actionSave_Layout = new QAction("Save Layout", this);
			actionSave_Layout->setDisabled(true);
			menuLayout->addAction(actionSave_Layout);

			menuLayout->addSeparator();

			actionDefault = new QAction("Default", this);
			actionDefault->setCheckable(true);
			actionDefault->setChecked(true);
			actionDefault->setDisabled(true);
			menuLayout->addAction(actionDefault);

			actionClip_Editing = new QAction("Clip Editing", this);
			actionClip_Editing->setCheckable(true);
			actionClip_Editing->setDisabled(true);
			menuLayout->addAction(actionClip_Editing);

			actionMotion_Editing = new QAction("Motion Editing", this);
			actionMotion_Editing->setCheckable(true);
			actionMotion_Editing->setDisabled(true);
			menuLayout->addAction(actionMotion_Editing);

			actionKeyframing = new QAction("Keyframing", this);
			actionKeyframing->setCheckable(true);
			actionKeyframing->setDisabled(true);
			menuLayout->addAction(actionKeyframing);

			actionSound_Editing = new QAction("Sound Editing", this);
			actionSound_Editing->setCheckable(true);
			actionSound_Editing->setDisabled(true);
			menuLayout->addAction(actionSound_Editing);

			actionCustom_Layout_5 = new QAction("Custom Layout 5", this);
			actionCustom_Layout_5->setCheckable(true);
			actionCustom_Layout_5->setDisabled(true);
			menuLayout->addAction(actionCustom_Layout_5);

			actionCustom_Layout_6 = new QAction("Custom Layout 6", this);
			actionCustom_Layout_6->setCheckable(true);
			actionCustom_Layout_6->setDisabled(true);
			menuLayout->addAction(actionCustom_Layout_6);

			actionCustom_Layout_7 = new QAction("Custom Layout 7", this);
			actionCustom_Layout_7->setCheckable(true);
			actionCustom_Layout_7->setDisabled(true);		
			menuLayout->addAction(actionCustom_Layout_7);

			actionCustom_Layout_8 = new QAction("Custom Layout 8", this);
			actionCustom_Layout_8->setCheckable(true);	
			actionCustom_Layout_8->setDisabled(true);
			menuLayout->addAction(actionCustom_Layout_8);

			actionCustom_Layout_9 = new QAction("Custom Layout 9", this);
			actionCustom_Layout_9->setCheckable(true);
			actionCustom_Layout_9->setDisabled(true);
			menuLayout->addAction(actionCustom_Layout_9);

			menuLayout->addSeparator();

			actionRename_Layout = new QAction("Rename Layout...", this);
			actionRename_Layout->setDisabled(true);
			menuLayout->addAction(actionRename_Layout);

			actionReset_Layouts = new QAction("Reset Layouts", this);
			actionReset_Layouts->setDisabled(true);
			menuLayout->addAction(actionReset_Layouts);

			menuLayout->addSeparator();

			actionImport_Layout = new QAction("Import Layout...", this);
			actionImport_Layout->setDisabled(true);
			menuLayout->addAction(actionImport_Layout);

			actionExport_Layout = new QAction("Export Layout...", this);
			actionExport_Layout->setDisabled(true);
			menuLayout->addAction(actionExport_Layout);

	// View menu
	menuView = new QMenu("View", menubar);
	menubar->addAction(menuView->menuAction());

		actionShow_Fullscreen = new QAction("Show Fullscreen", this);
		actionShow_Fullscreen->setShortcut(QKeySequence::fromString("Ctrl+Shift+F"));
		connect(actionShow_Fullscreen, &QAction::triggered, this, [this]() {
			// get windowstate
			if (windowState() & Qt::WindowFullScreen)
			{
				actionShow_Fullscreen->setText("Show Fullscreen");
				setWindowState(windowState() & ~Qt::WindowFullScreen);
			}
			else
			{
				actionShow_Fullscreen->setText("Show Normal");
				setWindowState(windowState() | Qt::WindowFullScreen);
			}
		});
		menuView->addAction(actionShow_Fullscreen);

		actionShow_Primary_Viewport_Controls = new QAction("Show Primary Viewport Controls", this);
		actionShow_Primary_Viewport_Controls->setShortcut(QKeySequence::fromString("Ctrl+Alt+E"));
		actionShow_Primary_Viewport_Controls->setCheckable(true);
		actionShow_Primary_Viewport_Controls->setChecked(true);
		actionShow_Primary_Viewport_Controls->setDisabled(true);
		menuView->addAction(actionShow_Primary_Viewport_Controls);

		actionShow_Secondary_Viewport_Controls = new QAction("Show Secondary Viewport Controls", this);
		actionShow_Secondary_Viewport_Controls->setCheckable(true);
		actionShow_Secondary_Viewport_Controls->setChecked(true);
		actionShow_Secondary_Viewport_Controls->setDisabled(true);
		menuView->addAction(actionShow_Secondary_Viewport_Controls);

	// Scripts menu
	menuScripts = new QMenu("Scripts", menubar);
	menuScripts->setDisabled(true);
	menubar->addAction(menuScripts->menuAction());

		menuExamples = new QMenu("Examples", menuScripts);
		menuExamples->setDisabled(true);
		menuScripts->addMenu(menuExamples);

			actionExport_Shot_List = new QAction("Export Shot List", this);
			actionExport_Shot_List->setDisabled(true);
			menuExamples->addAction(actionExport_Shot_List);

			actionRemove_Color_From_Selected_FilmClips = new QAction("Remove Color From Selected FilmClips", this);
			actionRemove_Color_From_Selected_FilmClips->setDisabled(true);
			menuExamples->addAction(actionRemove_Color_From_Selected_FilmClips);

			actionRemove_FilmClips_With_Duration_0 = new QAction("Remove FilmClips With Duration 0", this);
			actionRemove_FilmClips_With_Duration_0->setDisabled(true);
			menuExamples->addAction(actionRemove_FilmClips_With_Duration_0);

			actionRemove_Text_From_Selected_FilmClips = new QAction("Remove Text From Selected FilmClips", this);
			actionRemove_Text_From_Selected_FilmClips->setDisabled(true);
			menuExamples->addAction(actionRemove_Text_From_Selected_FilmClips);

		menuScripts->addSeparator();

		actionShow_In_Explorer = new QAction("Show in Explorer", this);
		actionShow_In_Explorer->setDisabled(true);
		menuScripts->addAction(actionShow_In_Explorer);

	// Help menu
	menuHelp = new QMenu("Help", menubar);
	menubar->addAction(menuHelp->menuAction());

		actionHelp = new QAction("Help...", this);
		actionHelp->setShortcut(QKeySequence::fromString("F1"));
		actionHelp->setDisabled(true);
		menuHelp->addAction(actionHelp);

		actionKeyboard_Shortcuts = new QAction("Keyboard Shortcuts", this);
		actionKeyboard_Shortcuts->setShortcut(QKeySequence::fromString("Ctrl+Alt+Shift+E"));
		connect(actionKeyboard_Shortcuts, &QAction::triggered, this, [this]() {
			keyboardShortcutsDialog->show();
			keyboardShortcutsDialog->activateWindow();
		});
		menuHelp->addAction(actionKeyboard_Shortcuts);

		menuHelp->addSeparator();

		actionScreencast = new QAction("Screencast", this);
		actionScreencast->setDisabled(true);
		menuHelp->addAction(actionScreencast);

		actionScreencast_Slides = new QAction("Screencast Slides", this);
		actionScreencast_Slides->setDisabled(true);
		menuHelp->addAction(actionScreencast_Slides);

		menuHelp->addSeparator();

		actionResetSettings = new QAction("Reset Settings", this);
		actionResetSettings->setDisabled(true);
		menuHelp->addAction(actionResetSettings);

		menuHelp->addSeparator();

		actionVisit_Forums = new QAction("Visit Forums", this);
		actionVisit_Forums->setDisabled(true);
		menuHelp->addAction(actionVisit_Forums);

		actionVisit_Steam_Community = new QAction("Visit Steam Community", this);
		actionVisit_Steam_Community->setDisabled(true);
		menuHelp->addAction(actionVisit_Steam_Community);

		actionContact_Us = new QAction("Contact Us", this);
		actionContact_Us->setDisabled(true);
		menuHelp->addAction(actionContact_Us);

		actionReport_Bug = new QAction("Report Bug", this);
		actionReport_Bug->setDisabled(true);
		menuHelp->addAction(actionReport_Bug);

		menuHelp->addSeparator();

		actionDirectors_Cut_Subscription_Terms = new QAction(DXFM_PRODUCT_NAME " Subscription Terms", this);
		actionDirectors_Cut_Subscription_Terms->setDisabled(true);
		menuHelp->addAction(actionDirectors_Cut_Subscription_Terms);

		actionSteam_Subscriber_Agreement = new QAction("Steam Subscriber Agreement", this);
		actionSteam_Subscriber_Agreement->setDisabled(true);
		menuHelp->addAction(actionSteam_Subscriber_Agreement);

		menuHelp->addSeparator();

		actionAbout_Directors_Cut = new QAction("About " DXFM_PRODUCT_NAME_FULL, this);
		connect(actionAbout_Directors_Cut, &QAction::triggered, this, [this]() {
			CAboutDialog* dialog = new CAboutDialog(this);
			dialog->show();
        	dialog->activateWindow();
		});
		menuHelp->addAction(actionAbout_Directors_Cut);

		actionAbout_Qt = new QAction("About Qt", this);
		connect(actionAbout_Qt, &QAction::triggered, this, [this]() {
			QApplication::aboutQt();
		});
		menuHelp->addAction(actionAbout_Qt);

	// Main desktop widget
	centralwidget = new QWidget(this);
	setCentralWidget(centralwidget);

		// Tabs
		tabWidget = new QTabWidget(centralwidget);
		tabWidget->setGeometry(QRect(0, 0, 323, 754));

			animationSetEditor = new QWidget();
			tabWidget->addTab(animationSetEditor, "Animation Set Editor");

			elementViewer = new QWidget();
			tabWidget->addTab(elementViewer, "Element Viewer");

		tabWidget->setCurrentIndex(0);

		tabWidget_2 = new QTabWidget(centralwidget);
		tabWidget_2->setGeometry(QRect(323, 0, 1021, 505));

			// primary viewport is a window so it needs to be in a container
			primaryViewport = new CViewportWindow(0);
			container = QWidget::createWindowContainer(primaryViewport, this);
			container->setMinimumSize(256, 256);
			container->setFocusPolicy(Qt::TabFocus);
			tabWidget_2->addTab(container, "Primary Viewport");

			console = new QWidget();
			tabWidget_2->addTab(console, "Console");

		tabWidget_3 = new QTabWidget(centralwidget);
		tabWidget_3->setGeometry(QRect(323, 505, 1021, 249));

			timeline = new QWidget();
			tabWidget_3->addTab(timeline, "Timeline");

		tabWidget_3->setCurrentIndex(0);

	// Status bar
	statusbar = new QStatusBar(this);
	setStatusBar(statusbar);

	// if not -nostartwizard then show the welcome wizard
	if (!CommandLine()->FindParm("-nostartwizard"))
	{
		CWelcomeWizardDialog* dialog = new CWelcomeWizardDialog(this);
		dialog->show();
		dialog->activateWindow();
	}
}

void CMainWindow::redraw()
{
	// Draw frames
	primaryViewport->redraw();
}

void CMainWindow::closeEvent(QCloseEvent *event)
{
	// concommand "quit prompt"
	engine->ClientCmd_Unrestricted("quit prompt");
	g_pDXFM->SetToolActive(false);
	// don't close the window
	event->ignore();
}

#include "ui.h.moc"