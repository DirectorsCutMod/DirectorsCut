<p>
  <a href="https://github.com/KiwifruitDev/DirectorsCut">
    <img width=50% alt="Director's Cut logo" src="https://i.imgur.com/iHJVGEZ.png">
  </a>
  <br><br>
  <a title="Director's Cut on GitHub" href="https://github.com/KiwifruitDev/DirectorsCut"><img alt="Director's Cut on GitHub" src="https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white"/></a>
  <a title="Director's Cut on Discord" href="https://discord.gg/3X3teNecWs"><img alt="Director's Cut on Discord" src="https://img.shields.io/badge/Discord-%235865F2.svg?style=for-the-badge&logo=discord&logoColor=white"/></a>
  <a title="Director's Cut on X (Twitter)" href="https://twitter.com/SFMDirectorsCut"><img alt="Director's Cut on X (Twitter)" src="https://img.shields.io/badge/X%20%28Twitter%29-%23000000.svg?style=for-the-badge&logo=X&logoColor=white"/></a>
  <a title="Director's Cut on Valve Developer Wiki" href="https://developer.valvesoftware.com/wiki/Director's_Cut"><img alt="Director's Cut on Valve Developer Wiki" src="https://img.shields.io/badge/Valve%20Developer%20Wiki-%23262626.svg?style=for-the-badge&logo=wikipedia&logoColor=white"/></a>
  <a title="Sponsor KiwifruitDev on GitHub" href="https://github.com/sponsors/KiwifruitDev"><img alt="Sponsor KiwifruitDev on GitHub" src="https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA"/></a>
  <a title="Sponsor KiwifruitDev on Ko-fi" href="https://ko-fi.com/kiwifruitdev"><img alt="Sponsor KiwifruitDev on Ko-fi" src="https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white"/></a>
  <br>
</p>

# Director's Cut
An open source 3D animation tool built on top of [Mapbase](https://github.com/mapbase-source/source-sdk-2013) and [Source SDK 2013](https://github.com/ValveSoftware/source-sdk-2013).

This is in early production as development was recently reset.

## Controls
- `Tab` - Open/close the Director's Cut editor.

## Usage
- **Prerequisites:**
  - Install Source SDK Base 2013 Singleplayer. You can download it through Steam.

- **Setting up Source SDK Base 2013 Singleplayer:**
  - Change its branch to "upcoming":
    - Right-click on Source SDK Base 2013 Singleplayer in your Steam library.
    - Click on Properties.
    - Go to the Betas tab.
    - Select "upcoming" from the dropdown menu.

- **Installing Mapbase:**
  - Download [Mapbase](https://www.moddb.com/mods/mapbase/downloads/mapbase-release-build) and extract it to your `sourcemods` directory. This directory is typically located in your Steam library's installation folder. For example, if your Steam library is at `C:\Program Files (x86)\Steam`, your `sourcemods` directory will be at `C:\Program Files (x86)\Steam\sourcemods`.

- **Installing Director's Cut:**
  - Download the latest development build of Director's Cut from the [Releases](https://github.com/KiwifruitDev/DirectorsCut/releases) page as `directorscut.zip`.
  - Extract the containing folder to your `sourcemods` directory.

- **Finalizing Setup:**
  - Restart Steam.
  - Director's Cut should now be available in your Steam library.

## Building
- **Prerequisites:**
  - Director's Cut requires [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) to build.

- **Building Director's Cut:**
  - **Cloning the Repository:**
    - Open a command prompt and run the following command:
      ```bat
      git clone https://github.com/KiwifruitDev/DirectorsCut.git
      ```

  - **Creating Visual Studio Solution:**
    - After cloning the repository, run `sp/src/createdirectorscutproject.bat` to create the Visual Studio solution.

  - **Building the Solution:**
    - Open `sp/src/directorscut.sln` in Visual Studio and build the solution.

  - **Launching the Build:**
    - Ensure `discord-rpc.dll` is in the same directory as `client.dll`. You can find this in a Mapbase or Director's Cut release build. Failure to do so will result in the game being unable to find `client.dll`.

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
