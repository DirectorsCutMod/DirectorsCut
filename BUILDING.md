# Building and Debugging
Read this section to learn how to install the prerequisites, build **Director's Cut**, and run and debug the tool.

## Prerequisites
Director's Cut requires the following software in order to build:
- **Windows 11**
  - At the moment, Linux is not supported.
- **Source SDK Base 2013 Multiplayer**
  - This can be installed through your **Steam** library under the **Tools** section.
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/)
- [Git for Windows](https://git-scm.com/download/win)
- [Qt Community Edition 5.15.2](https://www.qt.io/download-open-source)

If you meet these requirements, it may still be useful to read the following instructions for reference. Proceed to [Building Director's Cut](#building-directors-cut) for the build instructions.

### Git Installation
If you don't have **Git for Windows** installed, follow these steps to install it:
- Download the **64-bit Git for Windows Setup** installer from the Git website linked above and run it.
- Read the license agreement and **ONLY** click **Next** if **YOU** agree to the terms and conditions.
- For each of these screens, set the following options and click **Next**:
  - Select components:
    - [ ] Additional icons
      - [ ] On the Desktop
    - [ ] *Windows Explorer integration*
      - [ ] *Open Git Bash Here*
      - [ ] *Open Git GUI Here*
    - [x] *Git LFS (Large File Support)*
    - [ ] *Associate .git* configuration files with the default text editor
    - [ ] *Associate .sh files to be run with Bash*
    - [ ] *Check daily for Git for Windows updates*
    - [ ] *(NEW!) Add a Git Bash Profile to Windows Terminal*
    - [ ] *(NEW!) Scalar (Git add-on to manage large-scale repositories)*
  - Choosing the default editor used by Git:
    - *Use Notepad as Git's default editor*
  - Adjusting the name of the initial branch in new repositories:
    - [ ] *Let Git decide*
    - [x] *Overwrite the default branch name for new repositories*
      - `main`
  - Adjusting your PATH environment:
    - [ ] *Use Git from Bash only*
    - [x] *Use Git from the command line and also from 3rd-party software*
    - [ ] *Use Git and optional Unix tools from the Command Prompt*
  - Choosing the SSH executable:
    - [x] *Use bundled OpenSSH*
    - [ ] *Use (Tortoise)Plink*
    - [ ] *Use external OpenSSH*
  - Choosing HTTPS transport backend:
    - [x] *Use the OpenSSL library*
    - [ ] *Use the native Windows Secure Channel library*
  - Configuring the line ending conversions:
    - [x] *Checkout Windows-style, commit Unix-style line endings*
    - [ ] *Checkout as-is, commit Unix-style line endings*
    - [ ] *Checkout as-is, commit as-is*
  - Configuring the terminal emulator to use with Git Bash:
    - [ ] *Use MinTTY (the default terminal of MSYS2)*
    - [x] *Use Windows' default console window*
  - Choose the default behavior of \`git pull\`:
    - [x] *Fast-forward or merge*
    - [ ] *Rebase*
    - [ ] *Only ever fast-forward*
  - Choose a credential helper:
    - [x] *Git Credential Manager*
    - [ ] *None*
  - Configuring extra options:
    - [x] *Enable file system caching*
    - [x] *Enable symbolic links*
  - Configuring experimental options:
    - [ ] *Enable experimental support for pseudo consoles.*
    - [ ] *Built-in file system monitor*
- Click **Install** to begin the installation.

### Qt Installation
If you don't have **Open Source Qt 5.15.2** installed, follow these steps to install it:
- Download the **Qt Online Installer** from the Qt website linked above and run it.
- Log in or create a Qt account through the installer.
- Please read the terms and conditions and **ONLY** select the following options if they apply to **YOU**, then click **Next**:
  - *I have read and agree to the terms and conditions of using Open Source Qt*
  - *I'm an individual and do not use Qt for any company*
- Click **Next**, select one of the following usage data options, and click **Next**:
  - *Help us to improve by sending psuedoaonymous usage statistics in Qt Creator*
  - *Disable sending psuedoaonymous usage statistics in Qt Creator*
- Ensure these settings are correct and click **Next**:
  - *Please specify the directory where Qt will be installed.*
    - `C:\Qt` **(Qt is required to be installed to this location!)**
  - [x] *Custom Installation*
  - [ ] *Associate common file types with Qt Creator.*
- Select the following filters and click **Filter**:
  - [x] *Archive*
  - [ ] *Latest supported releases*
  - [ ] *Preview*
- Click on the *Select* dropdown and select *Deselect All*.
- Navigate through *Qt* > *Qt 5.15.2* and select *MSVC 2019 32-bit* and click **Next**.
- Read the license agreements and **ONLY** select the following option if it applies to **YOU**, then click **Next**:
  - *I have read and agree to the terms contained in the license agreements*
- Click **Next** and then **Install** to begin the installation.
- Once the installation is complete, follow [Configuring the Qt Environment](#configuring-the-qt-environment) once the repository is cloned.

## Building Director's Cut
Please ensure that you have met the prerequisites before building.

Follow these steps to build Director's Cut:

### Cloning the Repository
Open a **Command Prompt** or **Terminal** window and run the following commands to clone the repository and navigate to the `DirectorsCut` folder:
```bat
git clone https://github.com/DirectorsCutMod/DirectorsCut.git
cd DirectorsCut
```

### Configuring the Qt Environment
The following batch files are available in the `mp/src` folder in order to configure the Qt environment:
- `qt_set_junction.bat`
  - This is the first batch file to run after installing Qt.
  - Creates a junction from `mp/src/tools/directorscut/qt` to `C:\Qt\5.15.2\msvc2019`
  - This is required as the repository does not include Qt binaries, libraries, and headers.
  - This folder is ignored when committing changes to the repository.
- `qt_copy_binaries.bat`
  - This only needs to be run if you are running a build of Director's Cut.
  - Copies the required Qt DLLs to the `mp/game/bin/tools/dxfm` folder.
  - Allows selecting between copying the Debug or Release variants of the DLLs.
    - At the moment, only the Debug variant is supported.
  - Without copying the DLLs, Director's Cut will not run.
- `qt_moc.bat`
  - This batch file is used to run the Qt Meta-Object Compiler (`.moc`) on Director's Cut-specific Qt header files.
  - This is required because the `.moc` files are not included in the repository.
  - This batch file is automatically run from `createtoolprojects.bat` if the Qt junction is set up.

For first-time setup, run these required batch files in the following order:
```bat
cd mp\src
.\qt_set_junction.bat
.\qt_copy_binaries.bat
```

You may be prompted to select options when running `qt_copy_binaries.bat`. Select the appropriate option and press **Enter**.

### Creating and building the Visual Studio Solutions
Run the following Batch files to create the Visual Studio solutions for Director's Cut:
```bat
cd mp\src
.\creategameprojects.bat
.\createtoolprojects.bat
```

This will also run `qt_moc.bat`, which may not have any effect if you have not made any changes to the header files.

Follow these steps to build Director's Cut afterwards:
- Open the `mp/src/games.sln` solution file in Visual Studio 2022.
- Select the **Debug** configuration and **x86** platform from the toolbar.
- Click **Build** > **Build Solution** to build the game DLLs (`client.dll` and `server.dll`).
- Switch to the `mp/src/tools.sln` solution file.
- Right click on the `DXFM` project in the Solution Explorer and select **Set as Startup Project**.
- Select the **Debug** configuration and **x86** platform from the toolbar.
- Press **F7** or click **Build** > **Build Solution** to build Director's Cut (`dxfm.dll`).

## Debugging
- Right click on the `DXFM` project in the Solution Explorer and select **Properties**.
- In the **Configuration Properties** > **Debugging** section, set the following properties and click **OK**:
  - ```
    Debugger to launch: Local Windows Debugger
    Command: C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer\hl2.exe
    Command Arguments: -game "C:\Users\KiwifruitDev\DirectorsCut\mp\game\directorscut" -windowed -w 1280 -h 720 -multirun -tools -nop4 -sw -allowdebug -console
    Working Directory: C:\Program Files (x86)\Steam\steamapps\common\Source SDK Base 2013 Multiplayer
    Attach: No
    Debugger Type: Auto
    Environment:
    Merge Environment: Yes
    SQL Debugging: No
    Amp Default Accelerator: WARP software accelerator
    ```
  - You will need to change the location of the **DirectorsCut** repository.
  - **Source SDK Base 2013 Multiplayer** is required to be installed to the default location.
- Run the following Batch files to copy the required Qt DLLs, set up the necessary `bin/tools/dxfm` junction, and add `tools/dxfm/dxfm.dll` as an engine tool:
  ```bat
  cd mp\src
  .\qt_copy_binaries.bat
  .\sdk_set_tools_junction.bat
  .\sdk_set_tools_txt.bat
  ```
- Press **F5** or click **Debug** > **Start Debugging** to run Director's Cut.

## Running
See [USAGE.md](USAGE.md) for instructions on running Director's Cut through **Steam** or as an engine tool for your own **Source SDK 2013 Multiplayer** mod.
