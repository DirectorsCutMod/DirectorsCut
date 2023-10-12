<p align="center">
  <img width=50% alt="Director's Cut logo" src="https://i.imgur.com/iHJVGEZ.png">
  <br><br>
  <a title="Director's Cut on Discord" href="https://discord.gg/3X3teNecWs"><img alt="Director's Cut on Discord" src="https://img.shields.io/badge/Discord-%235865F2.svg?style=for-the-badge&logo=discord&logoColor=white"/></a><a title="Director's Cut on X (Twitter)" href="https://twitter.com/SFMDirectorsCut"><img alt="Director's Cut on X (Twitter)" src="https://img.shields.io/badge/X%20%28Twitter%29-%23000000.svg?style=for-the-badge&logo=X&logoColor=white"/></a><a title="Director's Cut on Valve Developer Wiki" href="https://developer.valvesoftware.com/wiki/Director's_Cut"><img alt="Director's Cut on Valve Developer Wiki" src="https://img.shields.io/badge/Valve%20Developer%20Wiki-%23262626.svg?style=for-the-badge&logo=wikipedia&logoColor=white"/></a>
</p>

# Director's Cut
An open source 3D animation tool built on top of [Mapbase](https://github.com/mapbase-source/source-sdk-2013) and [Source SDK 2013](https://github.com/ValveSoftware/source-sdk-2013).

This is in early production as development was recently reset.

## Controls
- `Tab` - Open/close the Director's Cut editor.

## Usage
To use Director's Cut, you must have Source SDK Base 2013 Singleplayer installed. You can download it through Steam or by [clicking here](steam://install/243730).

After installing Source SDK Base 2013 Singleplayer, its branch (beta) must be changed to `upcoming` in order to use Director's Cut. To do this, right click on Source SDK Base 2013 Singleplayer in your Steam library, click Properties, go to the Betas tab, and select `upcoming` from the dropdown menu.

Once you have Source SDK Base 2013 Singleplayer installed and its branch changed to `upcoming`, you must [download Mapbase](https://www.moddb.com/mods/mapbase/downloads/mapbase-release-build) and extract it to your `sourcemods` directory, which is located in your Steam library's installation folder. For example, if your Steam library is located at `C:\Program Files (x86)\Steam`, your `sourcemods` directory is located at `C:\Program Files (x86)\Steam\sourcemods`.

After installing Mapbase, you can download the latest development build of Director's Cut from the [Releases](https://github.com/KiwifruitDev/DirectorsCut/releases) page as `directorscut.zip` and extract the containing folder to your `sourcemods` directory.

Once all steps are complete, restart Steam and Director's Cut should now be available in your Steam library.

## Building
Director's Cut requires [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) to build.

To build Director's Cut, you must first clone the repository. To do this, open a command prompt and run the following command:
```bat
git clone https://github.com/KiwifruitDev/DirectorsCut.git
```

After cloning the repository, run `sp/src/createdirectorscutproject.bat` to create the Visual Studio solution. Then, open `sp/src/directorscut.sln` in Visual Studio and build the solution.

Launching the build requires `discord-rpc.dll` to be in the same directory as `client.dll`. This can be found in a Mapbase or Director's Cut release build. Failure to do so will result in the game unable to find `client.dll`.

## Implementation
If you would like to implement the Director's Cut animation system into your own mod, please note the following changes and files required:

### Changes
- `sp/src/vgui2/vgui_controls/PropertySheet.cpp`
    - `void PropertySheet::OnDragFailed(CUtlVector<KeyValues*>& msglist)`
        - Pages can now be dropped out to create new `ToolWindow` instances without requiring a tool factory.
    - `void PropertySheet::OnPanelDropped(CUtlVector<KeyValues*>& msglist)`
        - Pages can now be dropped onto existing `ToolWindow` instances without requiring a tool factory.

### Files
- `sp/src/game/client/directorscut`
    - This folder contains all of the Director's Cut code. You must either include each file through VPC or otherwise add them to your project.
- `sp/game/mod_hl2/resource/directorscut`
    - This folder contains all of the Director's Cut resource files. These files must be included in your mod's game directory.

## Contributing
Any changes are welcome through pull requests, I would really appreciate any help with this project.

Please feel free to submit any issues you find as well.

### Disclaimer
Some parts of the code in Director's Cut is AI-assisted using [GitHub Copilot](https://copilot.github.com/).

## Credits
Director's Cut shares code from the following projects:
- [Mapbase](https://github.com/mapbase-source/source-sdk-2013)
- [Source SDK 2013](https://github.com/ValveSoftware/source-sdk-2013)
- [Source Shader Editor](https://github.com/Biohazard90/source-shader-editor/)
- [directorscut-swarm](https://github.com/KiwifruitDev/directorscut-swarm)

### Mapbase Information
Please view [mapbase-readme.txt](mapbase-readme.txt) for more information.

### Third-Party Legal Notices
Please view [thirdpartylegalnotices.txt](thirdpartylegalnotices.txt) for more information.
