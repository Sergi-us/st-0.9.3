# st - simple terminal (v0.9.3)

Der [suckless terminal (st)](https://st.suckless.org/) mit zusätzlichen Patches und Anpassungen für SARBS.

## Features

+ **URL-Handling** via dmenu: `alt-l` (öffnen), `alt-y` (kopieren)
+ **Command-Output kopieren** mit `alt-o`
+ **Scrollback** mit `alt-↑/↓`, `alt-pageup/down` oder `shift` beim Scrollen
+ **Vim-Bindings**: `alt-k`/`alt-j` (zeile), `alt-u`/`alt-d` (halbe seite)
+ **Zoom**: wie Scrollback, aber mit `shift` gedrückt. `alt-home` für Reset
+ **Copy/Paste**: `alt-c` (kopieren), `alt-v` oder `shift-insert` (einfügen)
+ **Transparenz** mit `alt-a`/`alt-s` dynamisch anpassbar
+ **Xresources** und `pywal` Unterstützung für dynamische Farben
+ Standard [gruvbox](https://github.com/morhetz/gruvbox) Farbschema
+ **Boxdraw** - bessere Darstellung von Linienzeichen
+ **Ligatures** - Font-Ligaturen Support
+ **Harfbuzz** - verbesserte Font-Rendering

## Installation

Abhängigkeiten: `xlib` Header-Dateien und `libharfbuzz`

```sh
git clone https://codeberg.org/Sergi-us/st
cd st
sudo make install
```

Build-Abhängigkeiten: `make`, `fontconfig`, `libX11`, `libXft`

Für Transparenz wird ein Composite Manager benötigt (`picom`, `xcompmgr`, etc.)

## Konfiguration via Xresources

`st` liest Einstellungen aus `~/.Xdefaults` oder `~/.Xresources`. Nach Änderungen `xrdb` ausführen:

```sh
*.font: JetBrainsMono NF:size=10:antialias=true:autohint=true
*.alpha: 0.8
*.color0: #282828
...
```

`alpha`: `0` (transparent) bis `1` (opak)

### Farbpriorität

1. `wal` Farben (wenn aktiv)
2. Xresources Farben
3. Gruvbox (Fallback)

**Hinweis**: `wal` deaktiviert Transparenz bei bestehenden Fenstern, neue Fenster nutzen weiterhin die definierte Transparenz.

## SARBS Integration

Diese st-Konfiguration ist Teil von [SARBS](https://codeberg.org/Sergius/SARBS.git) und funktioniert am besten im Zusammenspiel mit:
- [dwm](https://github.com/Sergi-us/dwm.git)
- [dmenu](https://github.com/Sergi-us/dmenu.git)
- [dwmblocks](https://github.com/Sergi-us/dwmblocks.git)
- [dotfiles](https://codeberg.org/Sergius/dotfiles.git)

---

## Original README (suckless.org)

st - simple terminal
--------------------
st is a simple terminal emulator for X which sucks less.

### Requirements

In order to build st you need the Xlib header files.

### Installation

Edit config.mk to match your local setup (st is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install st (if
necessary as root):

    make clean install

### Running st

If you did not install st with make clean install, you must compile
the st terminfo entry with the following command:

    tic -sx st.info

See the man page for additional details.

### Credits

Based on Aurélien APTEL <aurelien dot aptel at gmail dot com> bt source code.
