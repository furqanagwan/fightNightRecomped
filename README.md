# fightNightRecomped

Native PC static recompilations of EA's Fight Night games for Xbox 360, built on
[ReXGlue](https://github.com/rexglue/rexglue-sdk). Every game is recompiled from
the player's own disc image; this repository contains no game data, no generated
code and no extracted artwork.

| Game | Folder | Status |
| --- | --- | --- |
| Fight Night Round 4 (USA/Europe, 45410894) | `fightNight4/` | In progress |
| Fight Night Round 3 | `fightNight3/` | Not started |
| Fight Night Champion | `fightNightChampion/` | Not started |

## Repository layout

```
cmake/Recomp.cmake          recomp_add_game(): shared build setup for every game
common/                     recomp_common library shared by all games
  include/recomp/app        GameRecompApp base class, GameDescriptor, GamePaths
  include/recomp/installer  DiscImageInstaller (Xbox 360 ISO extraction)
  include/recomp/input      ControllerMenuWatcher, GuestInputGate, ImGuiGamepadBridge
  include/recomp/platform   NativeFilePicker, GamingRuntimeSession (Xbox PC app)
  include/recomp/settings   UserSettingsStore
  include/recomp/ui         DiscInstallDialog, SystemMenuDialog, SettingsDialog, MonochromeTheme
  include/recomp/debug      GuestImageDump
  src/kernel                Kernel stubs every game shares (Xbox Live Vision camera)
fightNight4/                One folder per game: descriptor, codegen config, settings, GDK and UWP metadata
templates/game/             Starting point for the next game
scripts/                    build, packaging, artwork, new game, analysis tools
thirdparty/rexglue-sdk      ReXGlue fork with the fixes these games need
```

The framework is shared with
[liveRecomped](https://github.com/furqanagwan/liveRecomped) (NBA LIVE) under
neutral names, so both can later move to one common submodule.

## Requirements

- CMake 3.25+, Ninja, Clang 18+ (Clang 20 on Linux)
- ReXGlue SDK: the `thirdparty/rexglue-sdk` submodule (branch `liverecomp-fixes`),
  either installed (`CMAKE_PREFIX_PATH`) or passed as `REXSDK_DIR`
- Windows: Visual Studio build tools and the Windows SDK; optional Microsoft GDK
  for Xbox PC app integration
- Linux / Steam Deck: Vulkan and GTK development packages as listed in the ReXGlue README

```
git clone --recursive https://github.com/furqanagwan/fightNightRecomped.git
```

## Building

Extract your disc into the game's `assets` folder (or let the game's first-run
installer do it), then:

```
.\scripts\build.ps1 -Game fightNight4
./scripts/build.sh fightNight4
```

## First run

If `default.xex` is missing, the game opens a setup window to pick your Xbox 360
ISO; the files are extracted once. Unattended installs:
`RECOMP_INSTALL_ISO=/path/to/game.iso`.

## Controls

- Xbox, PlayStation, Switch and Steam Deck controllers work through SDL; all
  controllers drive player 1 unless `recomp_shared_controllers` is turned off.
- System menu (Resume, Settings, Exit Game): press **View + Menu** together, or
  **Esc**. The Guide button is left to Windows Game Bar and Steam unless
  `guide_button = true`.

## Settings

Defaults live in `<GAME>/settings/<project>.toml` and are copied next to the
executable; the in-game Settings menu saves overrides to `settings.toml` in the
user data folder. New games start from the settings NBA LIVE needed (`rov` /
`fsi` render target paths, no background pipeline creation, 60 Hz vsync).

## Xbox PC app and Xbox Developer Mode

```
.\scripts\package_gdk.ps1 -Game fightNight4 -Pack -Install
.\scripts\build.ps1 -Game fightNight4 -Preset win-amd64-uwp-release
.\scripts\package_uwp.ps1 -Game fightNight4 -Register
.\scripts\package_uwp.ps1 -Game fightNight4 -Pack
```

The UWP preset needs the UWP flavour of the SDK installed at `C:\ReXGlue-UWP`
(`cmake --preset win-amd64-uwp` in the SDK). Package identities are local
stand-ins for personal testing only.

## Adding the next game

```
.\scripts\new_game.ps1 -Folder fightNight3 -ProjectName fight_night_round_3 -DisplayName "Fight Night Round 3" -ReleaseYear 2006
```

1. `python scripts/analysis/stabilize_codegen.py --game <GAME>` runs codegen
   until it is clean, seeding unresolved call targets and disabling seeds that
   split functions (recorded in `config/disabled_function_seeds.txt`).
2. Dump the loaded image with `RECOMP_DUMP_IMAGE=<GAME>/out/image_dump.bin`,
   then `python scripts/analysis/find_missing_functions.py --game <GAME> --write`
   and again with `--gaps`, and repeat step 1.
3. Missing kernel imports at link time become stubs in `common/src/kernel` when
   shared, otherwise in the game's `src/kernel`.
4. Artwork: `rexglue init ... achievements assets\default.xex metadata`, upscale
   `metadata/icons/title.png` to `metadata/gdk_hd/title_1024.png`, then
   `scripts/generate_artwork.ps1`.

Per-game research notes live in `<GAME>/docs/NOTES.md`.

## Legal

Not affiliated with or endorsed by Electronic Arts or Microsoft. Fight Night and
EA SPORTS are trademarks of Electronic Arts. You must own the game; no
copyrighted game content is distributed here.
