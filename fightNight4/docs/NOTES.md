# Research notes

## Title info
- Title: Fight Night Round 4 (USA, Europe), English, French, German
- Title ID: 45410894
- Achievements: 33
- Guest DLL modules: none (`--scan-dll` found 0)
- Disc: 63 files, 4,479,852,378 bytes; `default.xex` is 16,723,968 bytes

## Codegen

### 2026-09-14: first pass
`stabilize_codegen.py` seeded one unresolved call target and codegen was clean.
Four functions exceed `max_file_size_bytes`; they compile.

### 2026-09-14: discovery before the first crash
The image was dumped straight after the first successful build and both scans
ran up front: 170 functions referenced from data and 435 more from code gaps.
Codegen flagged 190 split branches and 53 seeds were disabled.

The build then failed with `use of undeclared label` in four files
(`loc_82939EC4`, `loc_8292B228`, `loc_8293AE20`, `loc_8293ACB8`). Gap seeds had
landed on targets of plain backward `b` jumps inside loops, splitting the loop
across two functions; codegen does not warn about that case. The gap scan now
skips every local branch target, and
`prune_bad_seeds.py --image <dump>` disabled 32 existing seeds that sat on one
(seeds referenced from data are kept). Result: 521 seeds, 85 disabled, clean
codegen and a clean build.

## Kernel
- Xbox Live Vision camera: `XUsbcamCreate`, `XUsbcamDestroy`, `XUsbcamSetView`,
  `XUsbcamSetCaptureMode` and `XUsbcamReadFrame` are imported on top of the
  two NBA LIVE uses. All camera stubs live in `common/src/kernel` and report
  the device as not connected.

## Runtime

### 2026-09-14: first launches
- Boots, starts audio and compiles shaders.
- First launch: `Unhandled guest access violation: read of guest 0x00000020`
  about 35 seconds in, on the thread that initialised audio.
- Second launch with `--log_level=debug` ran past that point without crashing,
  so the fault may depend on timing. Next step: reproduce and capture the guest
  call stack around the faulting read.
