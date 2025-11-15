# Agent Guidelines for st (suckless terminal)

## Project Overview
Luke's build of st - the suckless terminal emulator with patches for scrollback, transparency, ligatures, boxdraw, and harfbuzz. This is a C project for X11/Xlib.

## Build/Test Commands
- **Build**: `make` or `make clean && make` (in root or `st/` subdirectory)
- **Install**: `sudo make install` (installs to `/usr/local/bin` by default)
- **Clean**: `make clean`
- **No automated tests** - manual testing required by running `./st`
- **Configuration**: Edit `config.h` (generated from `config.def.h` on first build)

## Code Style

### C Style (suckless philosophy)
- **Headers**: Standard library first, then system headers, then local headers (`st.h`, `win.h`)
- **Includes**: Use `<>` for system, `""` for local headers
- **Macros**: ALL_CAPS with underscores (e.g., `IS_SET`, `BETWEEN`)
- **Types**: Lowercase with capital first letter (e.g., `Glyph`, `TCursor`, `Arg`)
- **Functions**: Lowercase, no underscores (e.g., `die()`, `redraw()`, `ttyread()`)
- **Variables**: Lowercase, descriptive names; static for file scope
- **Indentation**: Tabs, K&R brace style
- **Line length**: Keep reasonable (~80 chars when possible)
- **Comments**: `/* C89 style */`, brief and meaningful
- **Error handling**: Use `die()` for fatal errors; check returns explicitly

### File Organization
- `st.c` - terminal emulation logic
- `x.c` - X11/GUI implementation
- `config.h` - user configuration (NOT version controlled in customized builds)
- `st.h`, `win.h` - header files with function declarations
- `arg.h` - suckless-style argument parsing macros
- `hb.c`, `boxdraw.c` - patch-specific code

## Language & Documentation
- **Preferred Language**: German (Deutsch) for all comments and documentation
- **Comments**: Write new or updated comments in German

## Notes
- This is a suckless-style project: simple, minimal, hackable
- Configuration is done by editing `config.h` directly, not runtime options
- Both root directory and `st/` subdirectory contain buildable versions (st/ is Luke's customized version)
