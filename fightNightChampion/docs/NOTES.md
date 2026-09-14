# Research notes

## Title info
- Title: Fight Night Champion (USA, Europe), English, French, German
- Title ID: 45410915
- Achievements: 44
- Guest DLL modules: none (`--scan-dll` found 0)
- Disc: 187 files, 5,720,903,576 bytes; `default.xex` is 16,887,808 bytes

## Codegen

### 2026-09-14: first pass
`stabilize_codegen.py` seeded 3 unresolved call targets and codegen was clean.
One function exceeds `max_file_size_bytes`; it compiles. The first build
linked without new kernel stubs: the shared camera stubs added for Fight Night
Round 4 already cover every import.

### 2026-09-14: discovery before the first launch
With the image dumped after the first build: 672 functions referenced from data
and 697 from code gaps. `prune_bad_seeds.py --image` disabled 2 seeds on local
branch targets, but codegen then reported both as unresolved `b` targets: they
are tail-call entry points, not loop labels. `stabilize_codegen.py` now
re-enables a seed disabled as a branch target when codegen proves it must be a
function. After that, 6 split branches disabled 5 seeds.

Result: 1,367 seeds, 5 disabled, clean codegen and a clean build.

## Runtime

### 2026-09-14: first launch
- With `--log_level=debug`: boots, compiles shaders and starts audio; running
  and responsive after a minute with no fatal errors.
- `XMA: Write to unknown register (0601)` repeats at debug level, alternating
  values 2 and 3. Not an error so far; note it if audio misbehaves.
