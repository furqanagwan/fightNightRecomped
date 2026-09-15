<p align="center">
  <img src="docs/icon.png" alt="Fight Night Round 4" width="320">
</p>

<h1 align="center">Fight Night Round 4</h1>

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
| Released | June 2009 |
| Genre | Sports, boxing |
| Achievements | 33 |

## Regions

| Region | Serial | Status |
| --- | --- | --- |
| 🇺🇸 🇪🇺 USA, Europe | `EA-2196` | ✅ Tested (the disc below) |
| 🇯🇵 Japan | `EA-2196` | ⬜ Not tested |

Only the tested disc's `default.xex` has been recompiled. Other regional
executables are likely to differ and may need their own codegen pass.
Region list from [Redump](http://redump.org/discs/system/xbox360/).

## Disc

| | |
| --- | --- |
| Region | 🇺🇸 🇪🇺 USA, Europe |
| Title ID | `45410894` |
| Languages | English, French, German |
| Contents | 63 files, 4,479,852,378 bytes |
| Executable | `default.xex`, 16,723,968 bytes |
| DLL modules | None |

## Status

| Area | State |
| --- | --- |
| Boot, audio, shader compilation | Working |
| Gameplay | Plays |
| Stability | One access violation (read of guest `0x00000020`) seen once about 35 seconds in; not reproduced since |
| Controllers | Working through SDL |
| DLC | Installer in place (see the [root README](../README.md#dlc)); no packages tested |
| Xbox PC app, UWP builds | Configured, not yet tested |
| Linux, macOS, Steam Deck | Builds expected, not play-tested |

## Play

1. Download `FightNightRound4-v<version>-windows-x64.zip` from
   [Releases](https://github.com/furqanagwan/fightNightRecomped/releases?q=fightNight4)
   and extract it to a folder you can write to.
2. Run `Fight Night Round 4.exe` and choose your Xbox 360 ISO (USA/Europe disc,
   see [Regions](#regions)); the files are copied once.
3. Open the system menu with **View + Menu** (or **Esc**) for Settings and Exit.

## System requirements

| | Required |
| --- | --- |
| OS | Windows 10 version 2004 (build 19041) or Windows 11, 64-bit |
| Processor | 64-bit x86 CPU with SSE4.1 |
| Graphics | DirectX 12 GPU (feature level 11_0) |
| Memory | 8 GB RAM recommended |
| Storage | 4.5 GB, plus room for the ISO while it is copied |
| Software | [Microsoft Visual C++ Redistributable 2015-2022 (x64)](https://aka.ms/vs/17/release/vc_redist.x64.exe) |
| Game | Your own Fight Night Round 4 (USA, Europe) Xbox 360 disc image |

Tested on an Intel Core Ultra 9 275HX, GeForce RTX 5080 Laptop GPU and 32 GB RAM
(Windows 11).

## Build from source

```
rexglue extract "<your disc>.iso" fightNight4\assets
.\framework\scripts\build.ps1 -Game fightNight4
```

Setup is described in [CONTRIBUTING.md](../CONTRIBUTING.md).

## Default settings

`settings/fight_night_round_4.toml` starts from the NBA LIVE settings (`rov` /
`fsi` render target paths, no background pipeline creation, 60 Hz vsync).
Whether this game needs each of them has not been tested separately.

## Recompilation notes

| | |
| --- | --- |
| Function seeds | 521 in `config/functions.toml` |
| Disabled seeds | 85 in `config/disabled_function_seeds.txt` (they split functions or loops) |
| Kernel stubs | Xbox Live Vision camera, shared from `framework/common/src/kernel` |
| Known codegen warnings | Four functions exceed `max_file_size_bytes`; they compile |

The full log of what was found and fixed is in [docs/NOTES.md](docs/NOTES.md).

## Xbox Developer Mode (UWP)

```powershell
.\framework\scripts\build.ps1 -Game fightNight4 -Preset win-amd64-uwp-release
.\framework\scripts\package_uwp.ps1 -Game fightNight4 -Register
.\framework\scripts\package_uwp.ps1 -Game fightNight4 -Pack
```

## Artwork

`docs/icon.png` is the title image from `default.xex`, upscaled to 1024x1024.
To regenerate the exe icon and Xbox app images locally:

1. `rexglue init --project-name fight_night_round_4 --xex-path assets\default.xex achievements assets\default.xex metadata`
2. Upscale `metadata/icons/title.png` 4x twice with Real-ESRGAN
   (`realesrgan-x4plus`) to `metadata/gdk_hd/title_1024.png`, or copy
   `docs/icon.png` there.
3. `.\framework\scripts\generate_artwork.ps1 -Game fightNight4 -ProjectName fight_night_round_4`

## Legal

Not affiliated with or endorsed by Electronic Arts or Microsoft. Fight Night and
EA SPORTS are trademarks of Electronic Arts. You must own the game.
