# fightNightRecomped

Unofficial native PC versions of EA's Fight Night games for Xbox 360, made by
statically recompiling the original game code with
[ReXGlue](https://github.com/rexglue/rexglue-sdk). Download the game's
executable, point it at your own Xbox 360 disc image, and play.

This repository and its releases contain no game data: no disc images, game
files or extracted assets. You must own the game.

| Game | Supported disc | Status | Download |
| --- | --- | --- | --- |
| [Fight Night Round 4](fightNight4/README.md) | 🇺🇸 🇪🇺 USA, Europe (`45410894`) | Boots and plays; one timing-dependent crash seen once | [Releases](https://github.com/furqanagwan/fightNightRecomped/releases?q=fightNight4) |
| [Fight Night Champion](fightNightChampion/README.md) | 🇺🇸 🇪🇺 USA, Europe (`45410915`) | Boots and runs, not yet played | [Releases](https://github.com/furqanagwan/fightNightRecomped/releases?q=fightNightChampion) |
| Fight Night Round 3 | | Not started | |

## Playing

1. Check the [system requirements](#system-requirements) and install the
   [Microsoft Visual C++ Redistributable (x64)](https://aka.ms/vs/17/release/vc_redist.x64.exe).
2. Download the game's zip from [Releases](https://github.com/furqanagwan/fightNightRecomped/releases)
   and extract it to a folder you can write to (not Program Files).
3. Run the game's `.exe` and choose your Xbox 360 ISO when asked. The files are
   copied next to the executable once; the ISO isn't needed after that.

Check your disc against the game's supported regions first (see its README):
each release is recompiled from one regional executable.

### Controls

- Xbox, PlayStation, Switch and Steam Deck controllers work out of the box; all
  controllers drive player 1 unless *All controllers control player 1* is turned
  off in Settings.
- System menu (Resume, Settings, Exit Game): press **View + Menu** together, or
  **Esc**. The Guide button is left to Windows Game Bar and Steam unless
  `guide_button = true`.

### DLC

Put downloadable content packages (the `CON`, `LIVE` or `PIRS` files from an
Xbox 360 `Content\0000000000000000\<TitleID>\00000002` folder) in the `dlc`
folder next to the executable. Each package is checked against the game's title
ID and installed on the next start. Title updates are skipped: they replace game
code, so they need a new recompilation.

### Saves and settings

Saves, settings and logs go to your user folder; Settings > Game files shows
where. An empty `portable.txt` next to the executable keeps them beside it.

## System requirements

| | Required |
| --- | --- |
| OS | Windows 10 version 2004 (build 19041) or Windows 11, 64-bit |
| Processor | 64-bit x86 CPU with SSE4.1 |
| Graphics | DirectX 12 GPU (feature level 11_0) |
| Memory | 8 GB RAM recommended |
| Storage | Fight Night Round 4: 4.5 GB, Fight Night Champion: 5.5 GB, plus room for the ISO while it is copied |
| Software | [Microsoft Visual C++ Redistributable 2015-2022 (x64)](https://aka.ms/vs/17/release/vc_redist.x64.exe) |
| Game | Your own Xbox 360 disc image of a supported region |

Tested on an Intel Core Ultra 9 275HX, NVIDIA GeForce RTX 5080 Laptop GPU and
32 GB RAM running Windows 11. Lower-end hardware hasn't been tested yet; reports
are welcome. Linux, macOS and Steam Deck builds compile but have no releases and
haven't been play-tested.

## Developing

The shared app framework (installer, menus, input, packaging scripts) lives in
[recomp-framework](https://github.com/furqanagwan/recomp-framework), included here
as the `framework` submodule together with the ReXGlue fork.

```
git clone --recursive https://github.com/furqanagwan/fightNightRecomped.git
cd fightNightRecomped
rexglue extract "<your disc>.iso" fightNight4\assets
.\framework\scripts\build.ps1 -Game fightNight4
```

```
framework/                  recomp-framework submodule (with thirdparty/rexglue-sdk)
fightNight4/                Fight Night Round 4: descriptor, codegen config, settings, GDK/UWP metadata
fightNightChampion/         Fight Night Champion
<GAME>/docs/NOTES.md        Research notes: codegen, crashes and fixes
<GAME>/release.json         Supported disc and system requirements for release packaging
```

See [CONTRIBUTING.md](CONTRIBUTING.md) for setup, adding Fight Night Round 3
and making releases.

## License

The code in this repository is BSD 3-Clause, see [LICENSE](LICENSE).

Not affiliated with or endorsed by Electronic Arts or Microsoft. Fight Night and
EA SPORTS are trademarks of Electronic Arts. Releases contain code recompiled
from the original games but no game data; you must own the game to play.
