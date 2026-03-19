# Gallery Algorithms Framework

A small cross-platform C++ starter project for experimenting with algorithms that place artworks into gallery zones.

This repository is intentionally simple. It is designed for an applied algorithms course, not as a production gallery planner. The code already runs, reads input files, evaluates layouts, and supports pluggable algorithms. Students can then extend the model, scoring, and search methods over the rest of the semester.

## What the starter project already does

- reads a simplified YAML-like gallery file
- reads a simplified YAML-like show file
- reads an optional scoring configuration file
- builds internal C++ data structures
- runs one of two baseline algorithms:
  - `greedy`
  - `random`
- evaluates the resulting layout
- prints a score breakdown and placement summary

## Why the parser is "YAML-like"

To keep the starter package easy to build on macOS, Linux, and Windows without external dependencies, this version uses a very small hand-written parser for a restricted subset of YAML.

That means:

- indentation is for readability only
- the files should follow the examples in `data/`
- nested lists and advanced YAML features are not supported yet

This is deliberate. One of the early assignments can be to improve or replace the parser.

## Project layout

```text
gallery-algorithms-framework/
├─ Makefile
├─ README.md
├─ data/
│  ├─ gallery.yaml
│  ├─ show.yaml
│  └─ scoring.yaml
├─ include/
│  ├─ Algorithm.h
│  ├─ Artwork.h
│  ├─ Evaluator.h
│  ├─ Gallery.h
│  ├─ LayoutState.h
│  ├─ Parser.h
│  ├─ ScoringConfig.h
│  ├─ Show.h
│  ├─ Types.h
│  ├─ Util.h
│  └─ Zone.h
├─ src/
│  ├─ Evaluator.cpp
│  ├─ GreedyAlgorithm.cpp
│  ├─ Parser.cpp
│  ├─ Util.cpp
│  └─ main.cpp
└─ algorithms/
   └─ RandomAlgorithm.cpp
```

## Requirements

You need a C++17 compiler and `make`.

### macOS

Usually works with either:

- Apple Clang from Xcode Command Line Tools
- Homebrew GCC

To install Apple's command-line tools:

```bash
xcode-select --install
```

### Linux

Install `g++` and `make` using your package manager.

Ubuntu / Debian:

```bash
sudo apt update
sudo apt install build-essential
```

Fedora:

```bash
sudo dnf install gcc-c++ make
```

### Windows

The easiest approach is **MSYS2 + MinGW-w64**.

Install MSYS2, then in the MSYS2 MinGW terminal:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc make
```

Then build with either:

```bash
make
```

or, on some setups:

```bash
mingw32-make
```

If `make` is not recognized in PowerShell or Command Prompt, use the MSYS2 MinGW shell instead.

## Build

From the project root:

```bash
make
```

This creates:

- `planner` on macOS/Linux
- `planner.exe` on Windows

## Clean

```bash
make clean
```

## Run

macOS / Linux:

```bash
./planner data/gallery.yaml data/show.yaml greedy data/scoring.yaml
./planner data/gallery.yaml data/show.yaml random data/scoring.yaml
```

Windows (MSYS2 shell):

```bash
./planner.exe data/gallery.yaml data/show.yaml greedy data/scoring.yaml
```

You can also omit the scoring file to use built-in defaults:

```bash
./planner data/gallery.yaml data/show.yaml greedy
```

## Sample output

```text
Gallery Planner
===============
Gallery:   Kenyon Teaching Gallery
Show:      Light, Motion, and Structure
Algorithm: greedy

Score Breakdown
---------------
Compatibility:   75.00
Capacity:        0.00
Lighting:        -5.00
Room Preference: 40.00
Unplaced:        0.00
Duplicate Use:   0.00
TOTAL:           110.00
```

Your exact score may vary for `random`.

## Input file format

This starter accepts a limited subset of YAML. Follow the examples closely.

### Gallery file

```yaml
gallery:
  name: "Kenyon Teaching Gallery"
  zones:
    - id: "W1"
      room: "North Entry"
      type: "wall"
      capacity: 6
      light: 0.75
      supports_video: false
```

Fields:

- `id`: zone identifier
- `room`: room name
- `type`: `wall`, `floor`, `ceiling`, or `video`
- `capacity`: how large a work the zone can accept
- `light`: value from `0.0` to `1.0`
- `supports_video`: currently stored for future extension

### Show file

```yaml
show:
  title: "Light, Motion, and Structure"
  artworks:
    - id: "A1"
      title: "Striped Suspension"
      type: "ceiling"
      size: 2.5
      light_sensitivity: 0.60
      preferred_room: "Central Hall"
```

Fields:

- `id`: artwork identifier
- `title`: artwork title
- `type`: `wall`, `floor`, `ceiling`, or `video`
- `size`: abstract size for matching against zone capacity
- `light_sensitivity`: preferred maximum light level from `0.0` to `1.0`
- `preferred_room`: optional room preference

### Scoring file

```yaml
scoring:
  type_match_reward: 15
  type_mismatch_penalty: -50
  capacity_overflow_penalty: -80
  unplaced_penalty: -120
  room_preference_reward: 10
  duplicate_zone_penalty: -100
  light_penalty_multiplier: 40
```

## Current algorithms

### `greedy`
Places artworks one at a time into the zone that gives the best immediate score.

### `random`
Assigns each artwork to a random zone. Useful as a baseline for comparison.

## Possible uses

1. replace the parser with a fuller YAML library
2. add more realistic gallery fields such as room adjacency, skylights, or temporary ceilings
3. separate hard constraints from soft preferences
4. improve the greedy heuristic
5. add hill climbing
6. add local repair or backtracking
7. add simulated annealing
8. add hashing or visited-state tracking
9. export results in JSON or a visualization-friendly format

## Notes on portability

The code uses only the C++ standard library and a plain `Makefile`, so it should compile cleanly on all three major platforms as long as a C++17 compiler is available.

## License

This starter package is intended for educational use. Add your preferred license before publishing it broadly.
# gallery-algorithms-framework
