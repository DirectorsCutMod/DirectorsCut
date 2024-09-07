#pragma once

#include <QMainWindow>
#include <QWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QComboBox>

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

#include "viewportwindow.h"
#include "keyboardshortcutsdialog.h"

class CMainWindow : public QMainWindow
{
	Q_OBJECT;
public:
	CMainWindow(QWidget* pParent);

    // qt overrides
    virtual void closeEvent(QCloseEvent* event);

    void redraw();
protected:
    CKeyboardShortcutsDialog* keyboardShortcutsDialog;
    QMenuBar* menubar;
        QMenu* menuFile;
            QAction* actionNew;
            QAction* actionOpen;
            QAction* actionSave;
            QAction* actionSave_As;
            QAction* actionClose;
            
            QMenu* menuPerforce;
                QAction* actionAdd;
                QAction* actionCheckout;
                QAction* actionRevert;
                QAction* actionSubmit;

                QAction* actionList_Open_Files;

                QAction* actionView_In_P4Win;
                QAction* actionView_In_P4V;

                QAction* actionCheck_For_Perforce;
            QMenu* menuRecent;
                QAction* actionClear_Recent;

            QAction* actionLoad_Map;

            QMenu* menuImport;
                QAction* actionRender_Settings;
                QAction* actionMovie_Settings;
            QMenu* menuExport;
                QAction* actionMovie;
                QAction* actionPoster;
                QAction* actionImage;

                QAction* actionImage_To_Clipboard;

                QAction* actionRender_Settings2;
                QAction* actionMovie_Settings2;
            QMenu* menuCommunity;
                QAction* actionPublish_Video_To_YouTube_And_Steam;
                QAction* actionPublish_Image_To_Steam;
                QMenu* menuPublish_To_Steam_Workshop;
                    QAction* actionSounds;
                    QAction* actionModels;
                    QAction* actionMaps;
                    QAction* actionParticles;
                    QAction* actionScripts;
                    QAction* actionMaterials;
                    QAction* actionTextures;
                    QAction* actionSessions;
                    QAction* actionShots;
                    QAction* actionAnimations;

                QMenu* menuUpdate_Published_Item;
                    QAction* actionRefresh_Published_Item_List;

                QMenu* menuBrowse_To_Your_Published_Items;
                    QAction* actionVideos;
                    QAction* actionImages;
                    QAction* actionWorkshop;
                QMenu* menuBrowse_To_All_Published_Items;
                    QAction* actionVideos2;
                    QAction* actionImages2;
                    QAction* actionWorkshop2;
                
                QAction* actionShow_Used_Workshop_Items;
            QMenu* menuDownloadable_Content;
                QAction* actionInstall_Day_Of_Defeat_Content_Pack;
                QAction* actionInstall_Portal_Content_Pack;
                QAction* actionInstall_Blade_Symphony_Content_Pack;
                QAction* actionInstall_Black_Mesa_Content_Pack;
                QAction* actionInstall_Left_4_Dead_Content_Pack;
                QAction* actionInstall_Dino_D_Day_Content_Pack;
                QAction* actionInstall_The_Stanley_Parable_Content_Pack;

            QAction* actionQuit;
        QMenu* menuEdit;
            QAction* actionUndo;
            QAction* actionRedo;

            QAction* actionCut;
            QAction* actionCopy;
            QAction* actionPaste;
            QAction* actionDelete;
        QMenu* menuWindows;
            QAction* actionElement_Viewer;

            QAction* actionClip_Editor;
            QAction* actionMotion_Editor;
            QAction* actionGraph_Editor;
            QAction* actionAnimation_Set_Editor;

            QAction* actionPrimary_Viewport;
            QAction* actionSecondary_Viewport;

            QAction* actionConsole;
            QAction* actionScript_Editor;
            QAction* actionHistory;

            QAction* actionParticle_Editor_Tool;
            QAction* actionEnter_Game_Mode;
            QMenu* menuEngine_Window;
                QAction* actionAuto_Hide_Engine_Window;

            QAction* actionShow_All_Windows;

            QMenu* menuLayout;
                QAction* actionReturn_To_Default_Layout;
                QAction* actionSave_Layout;

                QAction* actionDefault;
                QAction* actionClip_Editing;
                QAction* actionMotion_Editing;
                QAction* actionKeyframing;
                QAction* actionSound_Editing;
                QAction* actionCustom_Layout_5;
                QAction* actionCustom_Layout_6;
                QAction* actionCustom_Layout_7;
                QAction* actionCustom_Layout_8;
                QAction* actionCustom_Layout_9;

                QAction* actionRename_Layout;
                QAction* actionReset_Layouts;

                QAction* actionImport_Layout;
                QAction* actionExport_Layout;
        QMenu* menuView;
            QAction* actionShow_Fullscreen;
            QAction* actionShow_Primary_Viewport_Controls;
            QAction* actionShow_Secondary_Viewport_Controls;
        QMenu* menuScripts;
            QMenu* menuExamples;
                QAction* actionExport_Shot_List;
                QAction* actionRemove_Color_From_Selected_FilmClips;
                QAction* actionRemove_FilmClips_With_Duration_0;
                QAction* actionRemove_Text_From_Selected_FilmClips;
            QAction* actionShow_In_Explorer;
        QMenu* menuHelp;
            QAction* actionHelp;
            QAction* actionKeyboard_Shortcuts;

            QAction* actionScreencast;
            QAction* actionScreencast_Slides;

            QAction* actionResetSettings;

            QAction* actionVisit_Forums;
            QAction* actionVisit_Steam_Community;
            QAction* actionContact_Us;
            QAction* actionReport_Bug;

            QAction* actionDirectors_Cut_Subscription_Terms;
            QAction* actionSteam_Subscriber_Agreement;

            QAction* actionAbout_Directors_Cut;
            QAction* actionAbout_Qt;
    QWidget* centralwidget;
        QTabWidget* tabWidget;
            QWidget* animationSetEditor;
            QWidget* elementViewer;
        QTabWidget* tabWidget_2;
            QWidget* container;
                CViewportWindow* primaryViewport;
            QWidget* console;
        QTabWidget* tabWidget_3;
            QWidget* timeline;
    QStatusBar* statusbar;
};
