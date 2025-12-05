# 💻 st - Simple Terminal

**Suckless Terminal Emulator für SARBS**

> **🔄 Umzug zu Codeberg**: Die aktive Entwicklung und Kollaboration findet jetzt auf [Codeberg](https://codeberg.org/Sergius/st) statt. GitHub dient nur als Mirror.
> 
> **📦 Hauptprojekt**: [SARBS](https://codeberg.org/Sergius/SARBS) - [Homepage](https://sarbs.xyz/sarbs/)

Minimalistischer Terminal Emulator mit praktischen Patches und voller Tastatursteuerung.

## ✨ Features

### URL-Handling & Zwischenablage
- **URL-Handling** via dmenu:
  - `alt-l` - URLs öffnen
  - `alt-y` - URLs in Zwischenablage kopieren
- **Command-Output** kopieren: `alt-o`
- **Copy/Paste**: `alt-c` (kopieren), `alt-v` oder `shift-insert` (einfügen)

### Navigation & Scrollback
- **Scrollback**: `alt-↑/↓`, `alt-pageup/down` oder `shift` beim Scrollen
- **Vim-Bindings**:
  - `alt-k/j` - Zeile für Zeile
  - `alt-u/d` - Halbe Seite

### Darstellung
- **Zoom**: `alt+shift+↑/↓` oder `j/k`, `alt-home` für Reset
- **Transparenz** dynamisch anpassbar: `alt-a` (erhöhen), `alt-s` (verringern)
- **Xresources** und **pywal**-Support für dynamische Farben
- **Ligatures** - Font-Ligaturen Support
- **Harfbuzz** - Verbesserte Font-Rendering-Engine

## ⚡ Installation

### Automatisch mit SARBS (empfohlen)
Wird durch das [SARBS-Installationsskript](https://codeberg.org/Sergius/SARBS) automatisch eingerichtet.

### Manuell
```bash
git clone https://codeberg.org/Sergius/st.git
cd st
sudo make install
```

### Abhängigkeiten
- `xlib` - X11 Library
- `libharfbuzz` - Font-Rendering
- `fontconfig` - Font-Konfiguration
- `libX11` - X11 Client Library
- `libXft` - X FreeType Library
- **Für Transparenz**: Composite Manager (z.B. `picom`, `xcompmgr`)

## 🛠️ Konfiguration

### Via Xresources

st liest Einstellungen aus `~/.Xdefaults` oder `~/.Xresources`:

```sh
*.font: JetBrainsMono NF:size=10:antialias=true:autohint=true
*.alpha: 0.8
*.color0: #282828
*.color1: #cc241d
*.color2: #98971a
...
```

Nach Änderungen neu laden:
```bash
xrdb ~/.Xresources
```

### Transparenz einstellen

`alpha`-Wert zwischen `0` (transparent) und `1` (opak):
```sh
*.alpha: 0.8
```

### Farbpriorität

1. **pywal** Farben (wenn aktiv)
2. **Xresources** Farben
3. **Gruvbox** (Fallback in config.h)

> **Hinweis**: pywal deaktiviert Transparenz bei existierenden Fenstern. Neu geöffnete Fenster nutzen die definierte Transparenz.

## 🎨 Integration mit pywal

st funktioniert automatisch mit [pywal](https://github.com/dylanaraps/pywal):

```bash
wal -i /pfad/zum/bild.jpg
```

Farben werden sofort übernommen!

## 📁 Anpassungen in config.h

Für erweiterte Konfiguration siehe [config.h](config.h):
- Schriftart und -größe
- Standard-Farben
- Shell-Pfad
- Scroll-Verhalten
- Und mehr...

Nach Änderungen:
```bash
sudo make clean install
```

## 📚 Weitere SARBS-Komponenten

- **[SARBS Hauptprojekt](https://codeberg.org/Sergius/SARBS)** - Auto-Rice Bootstrapping
- **[dotfiles](https://codeberg.org/Sergius/dotfiles)** - Konfigurationsdateien
- **[dwm](https://codeberg.org/Sergius/dwm)** - Window Manager
- **[dmenu](https://codeberg.org/Sergius/dmenu)** - Application Launcher
- **[dwmblocks-async](https://codeberg.org/Sergius/dwmblocks-async)** - Statusbar
- **[surf](https://codeberg.org/Sergius/surf)** - Web Browser

## 🤝 Credits

- **[suckless.org](https://st.suckless.org/)** - Original st
- **[Luke Smith](https://github.com/LukeSmithxyz/st)** - Patch-Inspiration
- **Aurélien APTEL** - Original bt Source Code

## 📄 Lizenz

Siehe [LICENSE](LICENSE) Datei.

---

**📧 Kontakt**:
- [Codeberg Issues](https://codeberg.org/Sergius/st/issues)
- [GitHub Issues](https://github.com/Sergi-us/st/issues) (Mirror)
- [SARBS Homepage](https://sarbs.xyz/kontakt/)
