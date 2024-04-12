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

This software is in early production as development was recently reset.

## Links
- [Director's Cut Github](https://github.com/KiwifruitDev/DirectorsCut)
- [Director's Cut Discord](https://discord.gg/3X3teNecWs)
- [Director's Cut YouTube](https://youtube.com/@DirectorsCutMod)
- [r/DirectorsCut](https://www.reddit.com/r/DirectorsCut/)
- [Director's Cut on X (Twitter)](https://x.com/DirectorsCutMod)
- [Director's Cut on Bluesky](https://bsky.app/profile/directorscut.bsky.social)
- [Director's Cut on Valve Developer Wiki](https://developer.valvesoftware.com/wiki/Director's_Cut)

## Usage
- **Prerequisites:**
  - Director's Cut requires **Source SDK Base 2013 Multiplayer** to be installed on Steam.
  - Director's Cut is currently only available for Windows.

- **Installation:**
  - Download the latest release from the [releases page](https://github.com/KiwifruitDev/DirectorsCut/releases/latest).
  - Extract the `directorscut` directory to your `sourcemods` directory.
    - For example, `C:\Program Files (x86)\Steam\steamapps\sourcemods\directorscut`.
  - Restart Steam and launch Director's Cut from your library.

- **Testing:**
  - When in-game, open the Director's Cut editor by pressing `Tab`.
  - Open sessions by clicking `File` > `Open`.
    - SFM sessions must be converted using the following command:
      ```bat
      dmxconvert -i session.dmx -oe keyvalues2 -o session_kv2.dmx
      ```
    - Test sessions are located in the following directory:
      ```
      C:\Program Files (x86)\Steam\steamapps\sourcemods\directorscut\elements\sessions
      ```

- **Information:**
  - Director's Cut is in early development and may contain bugs.
  - Please report any issues you find on the [GitHub issues page](https://github.com/KiwifruitDev/DirectorsCut/issues)
  - The timeline does not have any mouse controls yet, please use the keyboard controls below.
  - Right clicking does not work for any context menus yet.
  - The element viewer and inspector windows are unstable and may crash the game.
  - Loading a map must be performed through the console using the `map` command.
  - Saving a session may result in SFM no longer being able to open the file.
  - Keyboard controls are not locked on a per-window basis yet.

- **Team Fortress 2 Content:**
  - While Director's Cut is compatible with Team Fortress 2, content does not work out of the box.
  - Only the 2007 retail versions of the maps are supported.
  - SFM-exclusive models (such as in `tf_movies`) are not supported.
  - TF2 character models may have issues with their materials.
  - See `gameinfo.txt` for a rundown on how support was added.

## Controls
- **Director's Cut**:
  - `Tab` to toggle the Director's Cut editor.
- **Timeline**:
  - `Space` to play/pause the playback.
    - `Ctrl` + `Space` to play in x2 speed.
    - `Shift` + `Space` to play in reverse.
    - `Alt` + `Space` to play from the start.
  - `Left` and `Right` arrow keys to move the playhead by one frame.
  - `Up` and `Down` arrow keys to move the playhead to the start or end of the current shot.
  - `P` to lock the timeline view to the playhead.
  - `=` and `-` to zoom in and out.
- **Primary Viewport**:
  - `W`, `A`, `S`, and `D` to move the camera.
  - `Z` and `X` to move the camera up and down.
  - `Shift` to move the camera faster.
  - `Ctrl` to move the camera slower.

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
    - After cloning the repository, run `mp/src/creategameprojects.bat` to create the Visual Studio solution.

  - **Building the Solution:**
    - Open `mp/src/games.sln` in Visual Studio and build the solution.

## Implementation
If you would like to implement the Director's Cut animation system into your own mod, please note the following changes and files required:

### Changes
- `mp/src/vgui2/vgui_controls/PropertySheet.cpp`
    - `void PropertySheet::OnDragFailed(CUtlVector<KeyValues*>& msglist)`
        - Pages can now be dropped out to create new `ToolWindow` instances without requiring a tool factory.
    - `void PropertySheet::OnPanelDropped(CUtlVector<KeyValues*>& msglist)`
        - Pages can now be dropped onto existing `ToolWindow` instances without requiring a tool factory.
- `mp/src/game/client/c_baseanimating.cpp`
  - `CStudioHdr *C_BaseAnimating::OnNewModel()`
  - `void C_BaseAnimating::BuildTransformations(CStudioHdr* hdr, Vector* pos, Quaternion* q, const matrix3x4_t& cameraTransform, int boneMask, CBoneBitList& boneComputed)`
  - `bool C_BaseAnimating::SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)`
### Files
- `mp/src/game/client/directorscut`
    - This folder contains all of the Director's Cut code. You must either include each file through VPC or otherwise add them to your project.
- `mp/game/directorscut/materials/vgui/directorscut`
    - This folder contains all of the Director's Cut VGUI materials. These files must be included in your mod's game directory.
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

### Third-Party Legal Notices
Please view [thirdpartylegalnotices.txt](thirdpartylegalnotices.txt) for more information.
