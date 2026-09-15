<p align="center">
  <img src="docs/icon.png" alt="Fight Night Champion" width="320">
</p>

<h1 align="center">Fight Night Champion</h1>

<p align="center">
  Native PC static recompilation of the Xbox 360 version, built on the
  <a href="../README.md">fightNightRecomped</a> framework and ReXGlue.
</p>

## Game

| | |
| --- | --- |
| Developer | EA Canada |
| Publisher | Electronic Arts (EA SPORTS) |
| Series | Fight Night |
| Platform recompiled | Xbox 360 |
| Released | March 2011 |
| Genre | Sports, boxing |
| Achievements | 44 |

## Regions

| Region | Serial | Status |
| --- | --- | --- |
| 🇺🇸 🇪🇺 USA, Europe | `EA-2325` | ✅ Tested (the disc below) |

Only the tested disc's `default.xex` has been recompiled. Other regional
executables are likely to differ and may need their own codegen pass.
Region list from [Redump](http://redump.org/discs/system/xbox360/).

## Disc

| | |
| --- | --- |
| Region | 🇺🇸 🇪🇺 USA, Europe |
| Title ID | `45410915` |
| Languages | English, French, German |
| Contents | 187 files, 5,720,903,576 bytes |
| Executable | `default.xex`, 16,887,808 bytes |
| DLL modules | None |

## Status

| Area | State |
| --- | --- |
| Boot, audio, shader compilation | Working |
| Idle stability | Running and responsive after a minute, no fatal errors |
| Gameplay | Not yet played |
| Audio | `XMA: Write to unknown register (0601)` repeats at debug level; no audible problem seen yet |
| Controllers | Working through SDL |
| DLC | Installer in place (see the [root README](../README.md#dlc)); no packages tested |
| Xbox PC app, UWP builds | Configured, not yet tested |
| Linux, macOS, Steam Deck | Builds expected, not play-tested |

## Play

1. Download `FightNightChampion-v<version>-windows-x64.zip` from
   [Releases](https://github.com/furqanagwan/fightNightRecomped/releases?q=fightNightChampion)
   and extract it to a folder you can write to.
2. Run `Fight Night Champion.exe` and choose your Xbox 360 ISO (USA/Europe disc,
   see [Regions](#regions)); the files are copied once.
3. Open the system menu with **View + Menu** (or **Esc**) for Settings and Exit.

## System requirements

| | Required |
| --- | --- |
| OS | Windows 10 version 2004 (build 19041) or Windows 11, 64-bit |
| Processor | 64-bit x86 CPU with SSE4.1 |
| Graphics | DirectX 12 GPU (feature level 11_0) |
| Memory | 8 GB RAM recommended |
| Storage | 5.5 GB, plus room for the ISO while it is copied |
| Software | [Microsoft Visual C++ Redistributable 2015-2022 (x64)](https://aka.ms/vs/17/release/vc_redist.x64.exe) |
| Game | Your own Fight Night Champion (USA, Europe) Xbox 360 disc image |

Tested on an Intel Core Ultra 9 275HX, GeForce RTX 5080 Laptop GPU and 32 GB RAM
(Windows 11).

## Build from source

```
rexglue extract "<your disc>.iso" fightNightChampion\assets
.\framework\scripts\build.ps1 -Game fightNightChampion
```

Setup is described in [CONTRIBUTING.md](../CONTRIBUTING.md).

## Default settings

`settings/fight_night_champion.toml` starts from the NBA LIVE settings (`rov` /
`fsi` render target paths, no background pipeline creation, 60 Hz vsync).
Whether this game needs each of them has not been tested separately.

## Recompilation notes

| | |
| --- | --- |
| Function seeds | 1,367 in `config/functions.toml` |
| Disabled seeds | 5 in `config/disabled_function_seeds.txt` (they split functions) |
| Kernel stubs | Xbox Live Vision camera, shared from `framework/common/src/kernel` |
| Known codegen warnings | One function exceeds `max_file_size_bytes`; it compiles |

The full log of what was found and fixed is in [docs/NOTES.md](docs/NOTES.md).

## Xbox Developer Mode (UWP)

```powershell
.\framework\scripts\build.ps1 -Game fightNightChampion -Preset win-amd64-uwp-release
.\framework\scripts\package_uwp.ps1 -Game fightNightChampion -Register
.\framework\scripts\package_uwp.ps1 -Game fightNightChampion -Pack
```

## Artwork

The 64x64 title image in `default.xex` is too small to upscale legibly (the
"CHAMPION" lettering is about five pixels tall), so `docs/icon.png` rebuilds it
at 1024x1024: the EA SPORTS badge and title lettering are taken from the game's
1080x1080 Microsoft Store box art and placed on the tile's spotlight background.
To regenerate the exe icon and Xbox app images locally:

1. `rexglue init --project-name fight_night_champion --xex-path assets\default.xex achievements assets\default.xex metadata`
2. Copy `docs/icon.png` to `metadata/gdk_hd/title_1024.png`.
3. `.\framework\scripts\generate_artwork.ps1 -Game fightNightChampion -ProjectName fight_night_champion`

## Legal

Not affiliated with or endorsed by Electronic Arts or Microsoft. Fight Night and
EA SPORTS are trademarks of Electronic Arts. You must own the game.
