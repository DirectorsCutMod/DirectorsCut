<p align="center">
  <a href="https://github.com/KiwifruitDev/DirectorsCut">
    <img width=75% alt="Director's Cut logo" src="https://i.imgur.com/iHJVGEZ.png">
  </a>
  <br><br>
  <a title="Sponsor KiwifruitDev on GitHub" href="https://github.com/sponsors/KiwifruitDev"><img alt="Sponsor KiwifruitDev on GitHub" src="https://img.shields.io/badge/sponsor-30363D?style=for-the-badge&logo=GitHub-Sponsors&logoColor=#EA4AAA"/></a>
  <a title="Sponsor KiwifruitDev on Ko-fi" href="https://ko-fi.com/kiwifruitdev"><img alt="Sponsor KiwifruitDev on Ko-fi" src="https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white"/></a>
  <br>
</p>

# Director's Cut
A community-driven filmmaking mod for the Source engine.

Based upon [Source SDK 2013](https://github.com/ValveSoftware/source-sdk-2013).

This software is in early production as development was recently reset.

## Links
- [Director's Cut Github](https://github.com/KiwifruitDev/DirectorsCut)
- [Director's Cut Discord](https://discord.gg/3X3teNecWs)
- [Director's Cut YouTube](https://youtube.com/@DirectorsCutMod)
- [Director's Cut on X (Twitter)](https://x.com/DirectorsCutMod)
- [Director's Cut on Bluesky](https://bsky.app/profile/directorscut.bsky.social)
- [Director's Cut on Valve Developer Wiki](https://developer.valvesoftware.com/wiki/Director's_Cut)

## Usage
- **Prerequisites:**
  - Install *Source SDK Base 2013 Multiplayer* through Steam.

- **Installing Director's Cut:**
  - Delete any previous Director's Cut installations from your `sourcemods` directory.
    - `sourcemods` is usually located in `C:\Program Files (x86)\Steam\steamapps`.
  - Download the latest development build of Director's Cut from the [Releases](https://github.com/KiwifruitDev/DirectorsCut/releases) page as `directorscut.zip`.
  - Extract the containing folder to your `sourcemods` directory.

- **Finalizing Setup:**
  - Restart Steam.
  - Director's Cut should now be available in your Steam library.
  - Use `Tab` to toggle the Director's Cut editor while in-app.

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
    - After cloning the repository, run `mp/src/createdirectorscutproject.bat` to create the Visual Studio solution.

  - **Building the Solution:**
    - Open `mp/src/directorscut.sln` in Visual Studio and build the solution.

## Implementation
If you would like to implement the Director's Cut animation system into your own mod, please note the following changes and files required:

### Changes
- `mp/src/vgui2/vgui_controls/PropertySheet.cpp`
    - `void PropertySheet::OnDragFailed(CUtlVector<KeyValues*>& msglist)`
        - Pages can now be dropped out to create new `ToolWindow` instances without requiring a tool factory.
    - `void PropertySheet::OnPanelDropped(CUtlVector<KeyValues*>& msglist)`
        - Pages can now be dropped onto existing `ToolWindow` instances without requiring a tool factory.

### Files
- `mp/src/game/client/directorscut`
    - This folder contains all of the Director's Cut code. You must either include each file through VPC or otherwise add them to your project.
- `mp/game/directorscut/resource/directorscut`
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
