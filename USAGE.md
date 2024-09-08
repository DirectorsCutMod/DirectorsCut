# Usage
Director's Cut does not yet provide releases for users to download and install.

This guide is intended for Director's Cut upstream developers, Source SDK 2013 mod developers who wish to utilize Director's Cut in their own projects, and curious users with technical knowledge and a lot of patience.

Director's Cut is not in a usable state for animation at the moment.

Follow the instructions in [BUILDING.md](BUILDING.md) in order to obtain binaries, set up the necessary junctions, and familiarize yourself.

## Running through Steam
To run the `DirectorsCut` mod through **Steam**, follow these steps:

- Run the following Batch files to set up the necessary `sourcemods` junction and ensure additonal dependencies are met (see [BUILDING.md](BUILDING.md)):
  ```bat
  cd mp\src
  .\sdk_set_sourcemod_junction.bat
  .\sdk_set_tools_junction.bat
  .\sdk_set_tools_txt.bat
  ```
- Restart **Steam** if it is running.
- Navigate to the **Library** tab.
- Right click on the new **Director's Cut** entry and click **Properties**.
- Set the following launch options:
  ```
  -windowed -w 1280 -h 720 -multirun -tools -nop4
  ```
- Close the **Properties** window and click **Play** to run the Director's Cut mod.
- Press F11 and/or F10 to access the currently visible engine tool.
- Click `Tools` > `Director's Cut` to access the Director's Cut tool.

## Running as a tool
Director's Cut can be run from any **Source SDK Base 2013 Multiplayer** mod as a tool.

Included in this repository is the base `directorscut` mod (Half-Life 2: Deathmatch) alongside the tool `dxfm`.

Assuming the correct structure (see [BUILDING.md](BUILDING.md)) has been set up, you can use `dxfm` within any **SDK 2013 MP** game by using the `-tools` parameter:

- Run the following Batch files to set up the tool in **Source SDK Base 2013 Multiplayer** (see [BUILDING.md](BUILDING.md)):
  ```bat
  cd mp\src
  .\sdk_set_tools_junction.bat
  .\sdk_set_tools_txt.bat
  ```
- Navigate to the **Library** tab in **Steam**.
- Right click on your mod or **Source SDK Base 2013 Multiplayer** and click **Properties**.
- Add the following to your existing launch options:
  ```bat
  -tools -nop4
  ```
- Close the **Properties** window and click **Play** to run your mod with Director's Cut as a tool.
- Press F11 and/or F10 to access the currently visible engine tool.
- Click `Tools` > `Director's Cut` to access the Director's Cut tool.

