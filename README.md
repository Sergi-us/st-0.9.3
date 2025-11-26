# st - simple terminal

Suckless Terminal mit praktischen Patches.

## Features

- URL-Handling via dmenu: `alt-l` (öffnen), `alt-y` (kopieren)
- Command-Output kopieren: `alt-o`
- Scrollback: `alt-↑/↓`, `alt-pageup/down` oder `shift`
- Vim-Bindings: `alt-k/j` (Zeile), `alt-u/d` (halbe Seite)
- Zoom: `alt+shift+↑/↓` oder `j/k`, `alt-home` für Reset
- Copy/Paste: `alt-c`, `alt-v` oder `shift-insert`
- Transparenz dynamisch: `alt-a/s`
- Xresources und pywal-Support
- Ligatures und Harfbuzz-Rendering

## Installation

```bash
git clone https://codeberg.org/Sergius/st.git
cd st
sudo make install
```

Abhängigkeiten: `xlib`, `libharfbuzz`, `fontconfig`, `libX11`, `libXft`
Transparenz benötigt einen Composite Manager (z.B. `picom`).

## Konfiguration

Einstellungen in `~/.Xdefaults` oder `~/.Xresources`:

```sh
*.font: JetBrainsMono NF:size=10
*.alpha: 0.8
*.color0: #282828
```

Farbpriorität: `wal` → Xresources → Gruvbox (Fallback)

**Hinweis**: pywal deaktiviert Transparenz bei existierenden Fenstern.

Teil von [SARBS](https://codeberg.org/Sergius/SARBS.git).
