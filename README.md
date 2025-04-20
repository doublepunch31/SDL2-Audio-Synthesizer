# Assignment02 — SDL2 Audio Synthesizer

This project is a command-line audio synthesizer written in C++ using the SDL2 library. It allows real-time control of frequency, amplitude, smoothing (low-pass filter), and timing for up to 4 audio voices.

## Features

- Generates simple square waves.
- Up to 4 simultaneous audio voices.
- Interactive command-line control.
- Low-pass filtering to smooth signal output.
- Real-time audio playback using SDL2.

## Requirements

- **C++ compiler** with C++11 support or higher
- **CMake** ≥ 3.0
- **SDL2** development libraries
- **Linux** or compatible environment with SDL2 support

## Build Instructions

```bash
# Clone or download this project, then:
mkdir build
cd build
cmake ..
make
```

## Usage

Run the program:

```bash
./a02
```

Then enter commands in the terminal to control playback:

### Commands

- `freq <v> <f>` — Set frequency of voice `v` (0–3) to `f` Hz  
  Example: `freq 0 440`

- `ampl <v> <a>` — Set amplitude of voice `v` (0–3) to `a` (e.g., 0.5)  
  Example: `ampl 0 0.8`

- `lowpass <v> <s>` — Set smoothing parameter for voice `v` (0–3). `s` should be between `0.0` (no smoothing) and `1.0` (full smoothing).  
  Example: `lowpass 0 0.1`

- `delay <ms>` — Wait for `<ms>` milliseconds  
  Example: `delay 500`

- `quit` — Exit the program

## Example Session

```
freq 0 440
ampl 0 0.8
delay 1000
ampl 0 0.0
quit
```

## Debugging Tools

The build includes:

- `-Wall` — Enable compiler warnings
- `-g` — Enable debugging info
- `-fsanitize=address` — Enable AddressSanitizer for memory error detection

## Notes

Make sure SDL2 is installed and discoverable by CMake:
```bash
sudo apt install libsdl2-dev  # for Debian/Ubuntu
```
