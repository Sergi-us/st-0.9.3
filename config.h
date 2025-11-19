/* Siehe LICENSE-Datei für Urheber- und Lizenzdetails. */

/*
 * Aussehen
 *
 * Schriftart: siehe http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = { "JetBrainsMono NF:style=Light:size=10:antialias=true:autohint=false:hintstyle=hintfull" };
static char *font2[] = { "OpenMoji:size=11:antialias=true:autohint=true" };
static int borderpx = 0;

/*
 * Welches Programm von st ausgeführt wird, hängt von diesen Vorrangregeln ab:
 * 1: Programm übergeben mit -e
 * 2: scroll und/oder utmp
 * 3: SHELL-Umgebungsvariable
 * 4: Wert von shell in /etc/passwd
 * 5: Wert von shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
/* Scroll-Programm: zum Aktivieren einen String wie "scroll" verwenden */
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* Identifikationssequenz, die in DA und DECID zurückgegeben wird */
char *vtiden = "\033[?6c";

/* Kerning / Zeichen-Begrenzungsbox-Multiplikatoren */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * Wort-Trennzeichen
 *
 * Fortgeschritteneres Beispiel: L" `'\"()[]{}"
 */
wchar_t *worddelimiters = L" ";

/* Auswahl-Timeouts (in Millisekunden) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* Alternative Bildschirme */
int allowaltscreen = 1;

/* Erlaube bestimmte nicht-interaktive (unsichere) Fensteroperationen wie:
   Setzen des Zwischenablage-Texts */
int allowwindowops = 0;

/*
 * Zeichen-Latenzbereich in ms - von neuem Inhalt/Tastendruck/etc. bis zum Zeichnen.
 * In diesem Bereich zeichnet st, wenn kein neuer Inhalt mehr ankommt (idle). Meistens liegt
 * es nahe minlatency, aber es wartet länger bei langsamen Updates, um Teilzeichnungen zu vermeiden.
 * Niedrige minlatency führt zu mehr Tearing/Flackern, da es "idle" zu früh erkennen kann.
 */
static double minlatency = 8;
static double maxlatency = 33;

/*
 * Blink-Timeout (auf 0 setzen, um Blinken zu deaktivieren) für das
 * Terminal-Blink-Attribut.
 */
static unsigned int blinktimeout = 800;

/*
 * Dicke von Unterstrich- und Balken-Cursorn
 */
static unsigned int cursorthickness = 2;

/*
 * 1: Rendert die meisten Linien-/Block-Zeichen ohne Schriftart für
 *    perfekte Ausrichtung zwischen Zellen (U2500 - U259F außer Striche/Diagonalen).
 *    Fett beeinflusst Liniendicke, wenn boxdraw_bold nicht 0 ist. Kursiv wird ignoriert.
 * 0: Deaktivieren (alle U25XX-Glyphen normal aus der Schriftart rendern).
 */
const int boxdraw = 0;
const int boxdraw_bold = 0;

/* Braille (U28XX):  1: als benachbarte "Pixel" rendern,  0: Schriftart verwenden */
const int boxdraw_braille = 0;

/*
 * Klingellautstärke. Muss ein Wert zwischen -100 und 100 sein. Verwende 0 zum
 * Deaktivieren.
 */
static int bellvolume = 0;

/* Standard-TERM-Wert */
char *termname = "st-256color";

/*
 * Leerzeichen pro Tab
 *
 * Wenn du diesen Wert änderst, vergiss nicht, den »it«-Wert in der
 * st.info anzupassen und die st.info in der Umgebung, in der du diese
 * st-Version verwendest, entsprechend zu installieren.
 *
 *	it#$tabspaces,
 *
 * Zweitens stelle sicher, dass dein Kernel keine Tabs expandiert. Beim Ausführen
 * von `stty -a` sollte »tab0« erscheinen. Du kannst dem Terminal sagen, Tabs nicht
 * zu expandieren, indem du folgenden Befehl ausführst:
 *
 *	stty tabs
 */
unsigned int tabspaces = 8;

/* Hintergrund-Deckkraft */
float alpha = 0.8;
float alphaOffset = 0.0;
float alphaUnfocus;

/* Terminal-Farben (erste 16 werden in Escape-Sequenzen verwendet) */
static const char *colorname[] = {
	"#282828", /* harter Kontrast: #1d2021 / weicher Kontrast: #32302f */
	"#cc241d",
	"#98971a",
	"#d79921",
	"#458588",
	"#b16286",
	"#689d6a",
	"#a89984",
	"#928374",
	"#fb4934",
	"#b8bb26",
	"#fabd2f",
	"#83a598",
	"#d3869b",
	"#8ec07c",
	"#ebdbb2",
	[255] = 0,
	/* weitere Farben können nach 255 hinzugefügt werden zur Verwendung mit DefaultXX */
	"#add8e6", /* 256 -> Cursor */
	"#555555", /* 257 -> umgekehrter Cursor */
	"#282828", /* 258 -> Hintergrund */
	"#ebdbb2", /* 259 -> Vordergrund */
};


/*
 * Standardfarben (colorname-Index)
 * Vordergrund, Hintergrund, Cursor, umgekehrter Cursor
 */
unsigned int defaultfg = 259;
unsigned int defaultbg = 258;
unsigned int defaultcs = 256;
unsigned int defaultrcs = 257;
unsigned int background = 258;

/*
 * Standardform des Cursors
 * 2: Block ("█")
 * 4: Unterstrich ("_")
 * 6: Balken ("|")
 * 7: Schneemann ("☃")
 */
static unsigned int cursorshape = 2;

/*
 * Standard-Spalten- und Zeilenanzahl
 */

static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Standardfarbe und -form des Maus-Cursors
 */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

/*
 * Farbe zur Anzeige von Schriftartattributen, wenn fontconfig eine Schriftart
 * gewählt hat, die nicht den angeforderten entspricht.
 */
static unsigned int defaultattr = 11;

/*
 * Erzwinge Maus-Auswahl/Shortcuts während Maske aktiv ist (wenn MODE_MOUSE gesetzt ist).
 * Beachte: Wenn du ShiftMask mit selmasks verwenden willst, setze dies auf einen anderen
 * Modifier, setze auf 0, um es nicht zu verwenden.
 */
static uint forcemousemod = ShiftMask;

/*
 * Xresources-Einstellungen, die beim Start geladen werden
 */
ResourcePref resources[] = {
		{ "font",         STRING,  &font },
		{ "fontalt0",     STRING,  &font2[0] },
		{ "color0",       STRING,  &colorname[0] },
		{ "color1",       STRING,  &colorname[1] },
		{ "color2",       STRING,  &colorname[2] },
		{ "color3",       STRING,  &colorname[3] },
		{ "color4",       STRING,  &colorname[4] },
		{ "color5",       STRING,  &colorname[5] },
		{ "color6",       STRING,  &colorname[6] },
		{ "color7",       STRING,  &colorname[7] },
		{ "color8",       STRING,  &colorname[8] },
		{ "color9",       STRING,  &colorname[9] },
		{ "color10",      STRING,  &colorname[10] },
		{ "color11",      STRING,  &colorname[11] },
		{ "color12",      STRING,  &colorname[12] },
		{ "color13",      STRING,  &colorname[13] },
		{ "color14",      STRING,  &colorname[14] },
		{ "color15",      STRING,  &colorname[15] },
		{ "background",   STRING,  &colorname[258] },
		{ "foreground",   STRING,  &colorname[259] },
		{ "cursorColor",  STRING,  &colorname[256] },
		{ "termname",     STRING,  &termname },
		{ "shell",        STRING,  &shell },
		{ "minlatency",   INTEGER, &minlatency },
		{ "maxlatency",   INTEGER, &maxlatency },
		{ "blinktimeout", INTEGER, &blinktimeout },
		{ "bellvolume",   INTEGER, &bellvolume },
		{ "tabspaces",    INTEGER, &tabspaces },
		{ "borderpx",     INTEGER, &borderpx },
		{ "cwscale",      FLOAT,   &cwscale },
		{ "chscale",      FLOAT,   &chscale },
		{ "alpha",        FLOAT,   &alpha },
		{ "alphaOffset",  FLOAT,   &alphaOffset },
};

/*
 * Interne Maus-Shortcuts.
 * Achtung: Das Überladen von Button1 deaktiviert die Auswahl.
 */
static MouseShortcut mshortcuts[] = {
	/* Maske                Taste    Funktion        Argument       Release */
	{ XK_NO_MOD,            Button4, kscrollup,      {.i = 1}           },
	{ XK_NO_MOD,            Button5, kscrolldown,    {.i = 1}           },
	{ XK_ANY_MOD,           Button2, selpaste,       {.i = 0},          1 },
	{ ShiftMask,            Button4, ttysend,        {.s = "\033[5;2~"} },
	{ XK_ANY_MOD,           Button4, ttysend,        {.s = "\031"}      },
	{ ShiftMask,            Button5, ttysend,        {.s = "\033[6;2~"} },
	{ XK_ANY_MOD,           Button5, ttysend,        {.s = "\005"}      },
};

/* Interne Tastatur-Shortcuts. */
#define MODKEY Mod1Mask
#define TERMMOD (Mod1Mask|ShiftMask)

static char *openurlcmd[] = { "/bin/sh", "-c", "st-urlhandler -o", "externalpipe", NULL };
static char *copyurlcmd[] = { "/bin/sh", "-c", "st-urlhandler -c", "externalpipe", NULL };
static char *copyoutput[] = { "/bin/sh", "-c", "st-copyout", "externalpipe", NULL };

static Shortcut shortcuts[] = {
	/* Maske                Keysym          Funktion        Argument */
	{ XK_ANY_MOD,           XK_Break,       sendbreak,      {.i =  0} },
	{ ControlMask,          XK_Print,       toggleprinter,  {.i =  0} },
	{ ShiftMask,            XK_Print,       printscreen,    {.i =  0} },
	{ XK_ANY_MOD,           XK_Print,       printsel,       {.i =  0} },
	{ TERMMOD,              XK_Prior,       zoom,           {.f = +1} },
	{ TERMMOD,              XK_Next,        zoom,           {.f = -1} },
	{ TERMMOD,              XK_Home,        zoomreset,      {.f =  0} },
	{ TERMMOD,              XK_C,           clipcopy,       {.i =  0} },
	{ TERMMOD,              XK_V,           clippaste,      {.i =  0} },
	{ MODKEY,               XK_c,           clipcopy,       {.i =  0} },
	{ ShiftMask,            XK_Insert,      clippaste,      {.i =  0} },
	{ MODKEY,               XK_v,           clippaste,      {.i =  0} },
	{ ShiftMask,            XK_Insert,      selpaste,       {.i =  0} },
	{ TERMMOD,              XK_Num_Lock,    numlock,        {.i =  0} },
	{ ShiftMask,            XK_Page_Up,     kscrollup,      {.i = -1} },
	{ ShiftMask,            XK_Page_Down,   kscrolldown,    {.i = -1} },
	{ MODKEY,               XK_Page_Up,     kscrollup,      {.i = -1} },
	{ MODKEY,               XK_Page_Down,   kscrolldown,    {.i = -1} },
	{ MODKEY,               XK_k,           kscrollup,      {.i =  1} },
	{ MODKEY,               XK_j,           kscrolldown,    {.i =  1} },
	{ MODKEY,               XK_Up,          kscrollup,      {.i =  1} },
	{ MODKEY,               XK_Down,        kscrolldown,    {.i =  1} },
	{ MODKEY,               XK_u,           kscrollup,      {.i = -1} },
	{ MODKEY,               XK_d,           kscrolldown,    {.i = -1} },
	{ MODKEY,               XK_s,           changealpha,    {.f = -0.05} },
	{ MODKEY,               XK_a,           changealpha,    {.f = +0.05} },
	{ TERMMOD,              XK_Up,          zoom,           {.f = +1} },
	{ TERMMOD,              XK_Down,        zoom,           {.f = -1} },
	{ TERMMOD,              XK_K,           zoom,           {.f = +1} },
	{ TERMMOD,              XK_J,           zoom,           {.f = -1} },
	{ TERMMOD,              XK_U,           zoom,           {.f = +2} },
	{ TERMMOD,              XK_D,           zoom,           {.f = -2} },
	{ MODKEY,               XK_l,           externalpipe,   {.v = openurlcmd } },
	{ MODKEY,               XK_y,           externalpipe,   {.v = copyurlcmd } },
	{ MODKEY,               XK_o,           externalpipe,   {.v = copyoutput } },
};

/*
 * Spezialtasten (st.info entsprechend ändern & neu kompilieren)
 *
 * Maskenwert:
 * * Verwende XK_ANY_MOD, um die Taste unabhängig vom Modifier-Status zu matchen
 * * Verwende XK_NO_MOD, um die Taste allein zu matchen (keine Modifier)
 * appkey-Wert:
 * * 0: kein Wert
 * * > 0: Keypad-Anwendungsmodus aktiviert
 * *   = 2: term.numlock = 1
 * * < 0: Keypad-Anwendungsmodus deaktiviert
 * appcursor-Wert:
 * * 0: kein Wert
 * * > 0: Cursor-Anwendungsmodus aktiviert
 * * < 0: Cursor-Anwendungsmodus deaktiviert
 *
 * Sei vorsichtig mit der Reihenfolge der Definitionen, da st diese
 * Tabelle sequenziell durchsucht, also muss XK_ANY_MOD immer an der letzten
 * Position für eine Taste stehen.
 */

/*
 * Wenn du andere Tasten als die X11-Funktionstasten (0xFD00 - 0xFFFF)
 * unten gemappt haben möchtest, füge sie diesem Array hinzu.
 */
static KeySym mappedkeys[] = { -1 };

/*
 * Statusbits, die beim Matchen von Tasten- oder Mausereignissen ignoriert werden.
 * Standardmäßig werden Numlock (Mod2Mask) und Tastaturlayout (XK_SWITCH_MOD) ignoriert.
 */
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

/*
 * Dies ist das große Tasten-Array, das die gesamte Kompatibilität zur Linux-Welt
 * definiert. Bitte entscheide über Änderungen mit Bedacht.
 */
static Key key[] = {
	/* keysym           Maske           String      appkey appcursor */
	{ XK_KP_Home,       ShiftMask,      "\033[2J",       0,   -1},
	{ XK_KP_Home,       ShiftMask,      "\033[1;2H",     0,   +1},
	{ XK_KP_Home,       XK_ANY_MOD,     "\033[H",        0,   -1},
	{ XK_KP_Home,       XK_ANY_MOD,     "\033[1~",       0,   +1},
	{ XK_KP_Up,         XK_ANY_MOD,     "\033Ox",       +1,    0},
	{ XK_KP_Up,         XK_ANY_MOD,     "\033[A",        0,   -1},
	{ XK_KP_Up,         XK_ANY_MOD,     "\033OA",        0,   +1},
	{ XK_KP_Down,       XK_ANY_MOD,     "\033Or",       +1,    0},
	{ XK_KP_Down,       XK_ANY_MOD,     "\033[B",        0,   -1},
	{ XK_KP_Down,       XK_ANY_MOD,     "\033OB",        0,   +1},
	{ XK_KP_Left,       XK_ANY_MOD,     "\033Ot",       +1,    0},
	{ XK_KP_Left,       XK_ANY_MOD,     "\033[D",        0,   -1},
	{ XK_KP_Left,       XK_ANY_MOD,     "\033OD",        0,   +1},
	{ XK_KP_Right,      XK_ANY_MOD,     "\033Ov",       +1,    0},
	{ XK_KP_Right,      XK_ANY_MOD,     "\033[C",        0,   -1},
	{ XK_KP_Right,      XK_ANY_MOD,     "\033OC",        0,   +1},
	{ XK_KP_Prior,      ShiftMask,      "\033[5;2~",     0,    0},
	{ XK_KP_Prior,      XK_ANY_MOD,     "\033[5~",       0,    0},
	{ XK_KP_Begin,      XK_ANY_MOD,     "\033[E",        0,    0},
	{ XK_KP_End,        ControlMask,    "\033[J",       -1,    0},
	{ XK_KP_End,        ControlMask,    "\033[1;5F",    +1,    0},
	{ XK_KP_End,        ShiftMask,      "\033[K",       -1,    0},
	{ XK_KP_End,        ShiftMask,      "\033[1;2F",    +1,    0},
	{ XK_KP_End,        XK_ANY_MOD,     "\033[4~",       0,    0},
	{ XK_KP_Next,       ShiftMask,      "\033[6;2~",     0,    0},
	{ XK_KP_Next,       XK_ANY_MOD,     "\033[6~",       0,    0},
	{ XK_KP_Insert,     ShiftMask,      "\033[2;2~",    +1,    0},
	{ XK_KP_Insert,     ShiftMask,      "\033[4l",      -1,    0},
	{ XK_KP_Insert,     ControlMask,    "\033[L",       -1,    0},
	{ XK_KP_Insert,     ControlMask,    "\033[2;5~",    +1,    0},
	{ XK_KP_Insert,     XK_ANY_MOD,     "\033[4h",      -1,    0},
	{ XK_KP_Insert,     XK_ANY_MOD,     "\033[2~",      +1,    0},
	{ XK_KP_Delete,     ControlMask,    "\033[M",       -1,    0},
	{ XK_KP_Delete,     ControlMask,    "\033[3;5~",    +1,    0},
	{ XK_KP_Delete,     ShiftMask,      "\033[2K",      -1,    0},
	{ XK_KP_Delete,     ShiftMask,      "\033[3;2~",    +1,    0},
	{ XK_KP_Delete,     XK_ANY_MOD,     "\033[P",       -1,    0},
	{ XK_KP_Delete,     XK_ANY_MOD,     "\033[3~",      +1,    0},
	{ XK_KP_Multiply,   XK_ANY_MOD,     "\033Oj",       +2,    0},
	{ XK_KP_Add,        XK_ANY_MOD,     "\033Ok",       +2,    0},
	{ XK_KP_Enter,      XK_ANY_MOD,     "\033OM",       +2,    0},
	{ XK_KP_Enter,      XK_ANY_MOD,     "\r",           -1,    0},
	{ XK_KP_Subtract,   XK_ANY_MOD,     "\033Om",       +2,    0},
	{ XK_KP_Decimal,    XK_ANY_MOD,     "\033On",       +2,    0},
	{ XK_KP_Divide,     XK_ANY_MOD,     "\033Oo",       +2,    0},
	{ XK_KP_0,          XK_ANY_MOD,     "\033Op",       +2,    0},
	{ XK_KP_1,          XK_ANY_MOD,     "\033Oq",       +2,    0},
	{ XK_KP_2,          XK_ANY_MOD,     "\033Or",       +2,    0},
	{ XK_KP_3,          XK_ANY_MOD,     "\033Os",       +2,    0},
	{ XK_KP_4,          XK_ANY_MOD,     "\033Ot",       +2,    0},
	{ XK_KP_5,          XK_ANY_MOD,     "\033Ou",       +2,    0},
	{ XK_KP_6,          XK_ANY_MOD,     "\033Ov",       +2,    0},
	{ XK_KP_7,          XK_ANY_MOD,     "\033Ow",       +2,    0},
	{ XK_KP_8,          XK_ANY_MOD,     "\033Ox",       +2,    0},
	{ XK_KP_9,          XK_ANY_MOD,     "\033Oy",       +2,    0},
	{ XK_Up,            ShiftMask,      "\033[1;2A",     0,    0},
	{ XK_Up,            Mod1Mask,       "\033[1;3A",     0,    0},
	{ XK_Up,         ShiftMask|Mod1Mask,"\033[1;4A",     0,    0},
	{ XK_Up,            ControlMask,    "\033[1;5A",     0,    0},
	{ XK_Up,      ShiftMask|ControlMask,"\033[1;6A",     0,    0},
	{ XK_Up,       ControlMask|Mod1Mask,"\033[1;7A",     0,    0},
	{ XK_Up,ShiftMask|ControlMask|Mod1Mask,"\033[1;8A",  0,    0},
	{ XK_Up,            XK_ANY_MOD,     "\033[A",        0,   -1},
	{ XK_Up,            XK_ANY_MOD,     "\033OA",        0,   +1},
	{ XK_Down,          ShiftMask,      "\033[1;2B",     0,    0},
	{ XK_Down,          Mod1Mask,       "\033[1;3B",     0,    0},
	{ XK_Down,       ShiftMask|Mod1Mask,"\033[1;4B",     0,    0},
	{ XK_Down,          ControlMask,    "\033[1;5B",     0,    0},
	{ XK_Down,    ShiftMask|ControlMask,"\033[1;6B",     0,    0},
	{ XK_Down,     ControlMask|Mod1Mask,"\033[1;7B",     0,    0},
	{ XK_Down,ShiftMask|ControlMask|Mod1Mask,"\033[1;8B",0,    0},
	{ XK_Down,          XK_ANY_MOD,     "\033[B",        0,   -1},
	{ XK_Down,          XK_ANY_MOD,     "\033OB",        0,   +1},
	{ XK_Left,          ShiftMask,      "\033[1;2D",     0,    0},
	{ XK_Left,          Mod1Mask,       "\033[1;3D",     0,    0},
	{ XK_Left,       ShiftMask|Mod1Mask,"\033[1;4D",     0,    0},
	{ XK_Left,          ControlMask,    "\033[1;5D",     0,    0},
	{ XK_Left,    ShiftMask|ControlMask,"\033[1;6D",     0,    0},
	{ XK_Left,     ControlMask|Mod1Mask,"\033[1;7D",     0,    0},
	{ XK_Left,ShiftMask|ControlMask|Mod1Mask,"\033[1;8D",0,    0},
	{ XK_Left,          XK_ANY_MOD,     "\033[D",        0,   -1},
	{ XK_Left,          XK_ANY_MOD,     "\033OD",        0,   +1},
	{ XK_Right,         ShiftMask,      "\033[1;2C",     0,    0},
	{ XK_Right,         Mod1Mask,       "\033[1;3C",     0,    0},
	{ XK_Right,      ShiftMask|Mod1Mask,"\033[1;4C",     0,    0},
	{ XK_Right,         ControlMask,    "\033[1;5C",     0,    0},
	{ XK_Right,   ShiftMask|ControlMask,"\033[1;6C",     0,    0},
	{ XK_Right,    ControlMask|Mod1Mask,"\033[1;7C",     0,    0},
	{ XK_Right,ShiftMask|ControlMask|Mod1Mask,"\033[1;8C",0,   0},
	{ XK_Right,         XK_ANY_MOD,     "\033[C",        0,   -1},
	{ XK_Right,         XK_ANY_MOD,     "\033OC",        0,   +1},
	{ XK_ISO_Left_Tab,  ShiftMask,      "\033[Z",        0,    0},
	{ XK_Return,        Mod1Mask,       "\033\r",        0,    0},
	{ XK_Return,        XK_ANY_MOD,     "\r",            0,    0},
	{ XK_Insert,        ShiftMask,      "\033[4l",      -1,    0},
	{ XK_Insert,        ShiftMask,      "\033[2;2~",    +1,    0},
	{ XK_Insert,        ControlMask,    "\033[L",       -1,    0},
	{ XK_Insert,        ControlMask,    "\033[2;5~",    +1,    0},
	{ XK_Insert,        XK_ANY_MOD,     "\033[4h",      -1,    0},
	{ XK_Insert,        XK_ANY_MOD,     "\033[2~",      +1,    0},
	{ XK_Delete,        ControlMask,    "\033[M",       -1,    0},
	{ XK_Delete,        ControlMask,    "\033[3;5~",    +1,    0},
	{ XK_Delete,        ShiftMask,      "\033[2K",      -1,    0},
	{ XK_Delete,        ShiftMask,      "\033[3;2~",    +1,    0},
	{ XK_Delete,        XK_ANY_MOD,     "\033[P",       -1,    0},
	{ XK_Delete,        XK_ANY_MOD,     "\033[3~",      +1,    0},
	{ XK_BackSpace,     XK_NO_MOD,      "\177",          0,    0},
	{ XK_BackSpace,     Mod1Mask,       "\033\177",      0,    0},
	{ XK_Home,          ShiftMask,      "\033[2J",       0,   -1},
	{ XK_Home,          ShiftMask,      "\033[1;2H",     0,   +1},
	{ XK_Home,          XK_ANY_MOD,     "\033[H",        0,   -1},
	{ XK_Home,          XK_ANY_MOD,     "\033[1~",       0,   +1},
	{ XK_End,           ControlMask,    "\033[J",       -1,    0},
	{ XK_End,           ControlMask,    "\033[1;5F",    +1,    0},
	{ XK_End,           ShiftMask,      "\033[K",       -1,    0},
	{ XK_End,           ShiftMask,      "\033[1;2F",    +1,    0},
	{ XK_End,           XK_ANY_MOD,     "\033[4~",       0,    0},
	{ XK_Prior,         ControlMask,    "\033[5;5~",     0,    0},
	{ XK_Prior,         ShiftMask,      "\033[5;2~",     0,    0},
	{ XK_Prior,         XK_ANY_MOD,     "\033[5~",       0,    0},
	{ XK_Next,          ControlMask,    "\033[6;5~",     0,    0},
	{ XK_Next,          ShiftMask,      "\033[6;2~",     0,    0},
	{ XK_Next,          XK_ANY_MOD,     "\033[6~",       0,    0},
	{ XK_F1,            XK_NO_MOD,      "\033OP" ,       0,    0},
	{ XK_F1, /* F13 */  ShiftMask,      "\033[1;2P",     0,    0},
	{ XK_F1, /* F25 */  ControlMask,    "\033[1;5P",     0,    0},
	{ XK_F1, /* F37 */  Mod4Mask,       "\033[1;6P",     0,    0},
	{ XK_F1, /* F49 */  Mod1Mask,       "\033[1;3P",     0,    0},
	{ XK_F1, /* F61 */  Mod3Mask,       "\033[1;4P",     0,    0},
	{ XK_F2,            XK_NO_MOD,      "\033OQ" ,       0,    0},
	{ XK_F2, /* F14 */  ShiftMask,      "\033[1;2Q",     0,    0},
	{ XK_F2, /* F26 */  ControlMask,    "\033[1;5Q",     0,    0},
	{ XK_F2, /* F38 */  Mod4Mask,       "\033[1;6Q",     0,    0},
	{ XK_F2, /* F50 */  Mod1Mask,       "\033[1;3Q",     0,    0},
	{ XK_F2, /* F62 */  Mod3Mask,       "\033[1;4Q",     0,    0},
	{ XK_F3,            XK_NO_MOD,      "\033OR" ,       0,    0},
	{ XK_F3, /* F15 */  ShiftMask,      "\033[1;2R",     0,    0},
	{ XK_F3, /* F27 */  ControlMask,    "\033[1;5R",     0,    0},
	{ XK_F3, /* F39 */  Mod4Mask,       "\033[1;6R",     0,    0},
	{ XK_F3, /* F51 */  Mod1Mask,       "\033[1;3R",     0,    0},
	{ XK_F3, /* F63 */  Mod3Mask,       "\033[1;4R",     0,    0},
	{ XK_F4,            XK_NO_MOD,      "\033OS" ,       0,    0},
	{ XK_F4, /* F16 */  ShiftMask,      "\033[1;2S",     0,    0},
	{ XK_F4, /* F28 */  ControlMask,    "\033[1;5S",     0,    0},
	{ XK_F4, /* F40 */  Mod4Mask,       "\033[1;6S",     0,    0},
	{ XK_F4, /* F52 */  Mod1Mask,       "\033[1;3S",     0,    0},
	{ XK_F5,            XK_NO_MOD,      "\033[15~",      0,    0},
	{ XK_F5, /* F17 */  ShiftMask,      "\033[15;2~",    0,    0},
	{ XK_F5, /* F29 */  ControlMask,    "\033[15;5~",    0,    0},
	{ XK_F5, /* F41 */  Mod4Mask,       "\033[15;6~",    0,    0},
	{ XK_F5, /* F53 */  Mod1Mask,       "\033[15;3~",    0,    0},
	{ XK_F6,            XK_NO_MOD,      "\033[17~",      0,    0},
	{ XK_F6, /* F18 */  ShiftMask,      "\033[17;2~",    0,    0},
	{ XK_F6, /* F30 */  ControlMask,    "\033[17;5~",    0,    0},
	{ XK_F6, /* F42 */  Mod4Mask,       "\033[17;6~",    0,    0},
	{ XK_F6, /* F54 */  Mod1Mask,       "\033[17;3~",    0,    0},
	{ XK_F7,            XK_NO_MOD,      "\033[18~",      0,    0},
	{ XK_F7, /* F19 */  ShiftMask,      "\033[18;2~",    0,    0},
	{ XK_F7, /* F31 */  ControlMask,    "\033[18;5~",    0,    0},
	{ XK_F7, /* F43 */  Mod4Mask,       "\033[18;6~",    0,    0},
	{ XK_F7, /* F55 */  Mod1Mask,       "\033[18;3~",    0,    0},
	{ XK_F8,            XK_NO_MOD,      "\033[19~",      0,    0},
	{ XK_F8, /* F20 */  ShiftMask,      "\033[19;2~",    0,    0},
	{ XK_F8, /* F32 */  ControlMask,    "\033[19;5~",    0,    0},
	{ XK_F8, /* F44 */  Mod4Mask,       "\033[19;6~",    0,    0},
	{ XK_F8, /* F56 */  Mod1Mask,       "\033[19;3~",    0,    0},
	{ XK_F9,            XK_NO_MOD,      "\033[20~",      0,    0},
	{ XK_F9, /* F21 */  ShiftMask,      "\033[20;2~",    0,    0},
	{ XK_F9, /* F33 */  ControlMask,    "\033[20;5~",    0,    0},
	{ XK_F9, /* F45 */  Mod4Mask,       "\033[20;6~",    0,    0},
	{ XK_F9, /* F57 */  Mod1Mask,       "\033[20;3~",    0,    0},
	{ XK_F10,           XK_NO_MOD,      "\033[21~",      0,    0},
	{ XK_F10, /* F22 */ ShiftMask,      "\033[21;2~",    0,    0},
	{ XK_F10, /* F34 */ ControlMask,    "\033[21;5~",    0,    0},
	{ XK_F10, /* F46 */ Mod4Mask,       "\033[21;6~",    0,    0},
	{ XK_F10, /* F58 */ Mod1Mask,       "\033[21;3~",    0,    0},
	{ XK_F11,           XK_NO_MOD,      "\033[23~",      0,    0},
	{ XK_F11, /* F23 */ ShiftMask,      "\033[23;2~",    0,    0},
	{ XK_F11, /* F35 */ ControlMask,    "\033[23;5~",    0,    0},
	{ XK_F11, /* F47 */ Mod4Mask,       "\033[23;6~",    0,    0},
	{ XK_F11, /* F59 */ Mod1Mask,       "\033[23;3~",    0,    0},
	{ XK_F12,           XK_NO_MOD,      "\033[24~",      0,    0},
	{ XK_F12, /* F24 */ ShiftMask,      "\033[24;2~",    0,    0},
	{ XK_F12, /* F36 */ ControlMask,    "\033[24;5~",    0,    0},
	{ XK_F12, /* F48 */ Mod4Mask,       "\033[24;6~",    0,    0},
	{ XK_F12, /* F60 */ Mod1Mask,       "\033[24;3~",    0,    0},
	{ XK_F13,           XK_NO_MOD,      "\033[1;2P",     0,    0},
	{ XK_F14,           XK_NO_MOD,      "\033[1;2Q",     0,    0},
	{ XK_F15,           XK_NO_MOD,      "\033[1;2R",     0,    0},
	{ XK_F16,           XK_NO_MOD,      "\033[1;2S",     0,    0},
	{ XK_F17,           XK_NO_MOD,      "\033[15;2~",    0,    0},
	{ XK_F18,           XK_NO_MOD,      "\033[17;2~",    0,    0},
	{ XK_F19,           XK_NO_MOD,      "\033[18;2~",    0,    0},
	{ XK_F20,           XK_NO_MOD,      "\033[19;2~",    0,    0},
	{ XK_F21,           XK_NO_MOD,      "\033[20;2~",    0,    0},
	{ XK_F22,           XK_NO_MOD,      "\033[21;2~",    0,    0},
	{ XK_F23,           XK_NO_MOD,      "\033[23;2~",    0,    0},
	{ XK_F24,           XK_NO_MOD,      "\033[24;2~",    0,    0},
	{ XK_F25,           XK_NO_MOD,      "\033[1;5P",     0,    0},
	{ XK_F26,           XK_NO_MOD,      "\033[1;5Q",     0,    0},
	{ XK_F27,           XK_NO_MOD,      "\033[1;5R",     0,    0},
	{ XK_F28,           XK_NO_MOD,      "\033[1;5S",     0,    0},
	{ XK_F29,           XK_NO_MOD,      "\033[15;5~",    0,    0},
	{ XK_F30,           XK_NO_MOD,      "\033[17;5~",    0,    0},
	{ XK_F31,           XK_NO_MOD,      "\033[18;5~",    0,    0},
	{ XK_F32,           XK_NO_MOD,      "\033[19;5~",    0,    0},
	{ XK_F33,           XK_NO_MOD,      "\033[20;5~",    0,    0},
	{ XK_F34,           XK_NO_MOD,      "\033[21;5~",    0,    0},
	{ XK_F35,           XK_NO_MOD,      "\033[23;5~",    0,    0},
};

/*
 * Masken für Auswahltypen.
 * Verwende die gleichen Masken wie üblich.
 * Button1Mask ist immer nicht gesetzt, damit Masken zwischen ButtonPress,
 * ButtonRelease und MotionNotify übereinstimmen.
 * Wenn keine Übereinstimmung gefunden wird, wird reguläre Auswahl verwendet.
 */
static uint selmasks[] = {
	[SEL_RECTANGULAR] = Mod1Mask,
};

/*
 * Druckbare Zeichen in ASCII, verwendet um die Vorschubbreite
 * von einfach breiten Zeichen zu schätzen.
 */

static char ascii_printable[] =
    " !\"#$%&'()*+,-./0123456789:;<=>?"
    "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmnopqrstuvwxyz{|}~";
