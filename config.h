/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "monospace:size=10" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#333333";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#9d2121";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance                     title             tags mask  switchtotag   isfloating isfreesize monitor */
	{ "firefox",             NULL,                        NULL,             1 << 2,    1,            0,         0,         -1 },
	{ "Chromium-browser",    NULL,                        NULL,             1 << 2,    1,            0,         0,         -1 },
	{ "VirtualBox Manager",  NULL,                        NULL,             1 << 3,    1,            0,         0,         -1 },
	{ "Gimp",                NULL,                        NULL,             1 << 3,    1,            0,         0,         -1 },
	{ "Audacity",            NULL,                        NULL,             1 << 3,    1,            0,         0,         -1 },
	{ NULL,                  "org.inkscape.Inkscape",     NULL,             1 << 3,    1,            0,         0,         -1 },
	{ "xterm-256color",      NULL,                        NULL,             0,         0,            0,         0,         -1 },
	{ "mpv",                 NULL,                        NULL,             0,         0,            0,         0,         -1 },
	{ "Alacritty",           NULL,                        NULL,             0,         0,            0,         0,         -1 },
	{ NULL,                  NULL,                        "Event Tester",   0,         0,            0,         0,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "nmaster.c"
#include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "-|=",      ntile },
	{ "-|-",      nbstack },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "[\\]",     dwindle },
 	{ "[@]",      spiral },
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define METAKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                          KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,                KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,    KEY,      tagprevmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY,                  KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY|ControlMask,      KEY,      toggleview,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/dash", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]     = { "/usr/local/bin/st", NULL };
static const char *dmenucmd[]    = { "/usr/local/bin/dmenu_run", "-i", "-m", "0", NULL };
static const char *dmpccmd[]     = { "/home/jozan/.local/bin/dmpc", NULL };
static const char *dmkillcmd[]   = { "/home/jozan/.local/bin/dmkill", NULL };
static const char *dmsearchcmd[] = { "/home/jozan/.local/bin/dmsearch", NULL };
static const char *dmscrotcmd[]  = { "/home/jozan/.local/bin/dmscrot", NULL };
static const char *dmlogcmd[]    = { "/home/jozan/.local/bin/dmlog", NULL };
static const char *filecmd[]     = { "/usr/local/bin/st", "-e", "/usr/local/bin/lf", NULL };
static const char *editcmd[]     = { "/usr/local/bin/emacsclient", "-c", NULL };
static const char *browsercmd[]  = { "/usr/local/bin/firefox", "--kiosk", "https://start.duckduckgo.com/", NULL };
static const char *torbrocmd[]   = { "/usr/local/bin/torify", "/usr/local/bin/firefox", "--kiosk", "https://start.duckduckgo.com/", NULL };
static const char *w3mcmd[]      = { "/usr/local/bin/st", "-e", "/usr/local/bin/w3m", "https://start.duckduckgo.com/", NULL };
static const char *nbcmd[]       = { "/usr/local/bin/st", "-e", "/usr/local/bin/newsboat", NULL };
static const char *ncmpccmd[]    = { "/usr/local/bin/st", "-e", "/usr/local/bin/ncmpc", NULL };
static const char *calcmd[]      = { "/usr/local/bin/st", "-e", "/usr/local/bin/calcurse", "-C", "/home/jozan/.config/calcurse", "-D", "/home/jozan/.local/share/calcurse", NULL };
static const char *sclicmd[]     = { "/usr/local/bin/st", "-e", "/usr/local/bin/scli", NULL };
static const char *muttcmd[]     = { "/usr/local/bin/st", "-e", "/usr/local/bin/neomutt", NULL };
static const char *gotopcmd[]    = { "/usr/local/bin/st", "-e", "/usr/local/bin/gotop", NULL };
static const char *htopcmd[]     = { "/usr/local/bin/st", "-e", "/usr/local/bin/htop", NULL };
static const char *topcmd[]      = { "/usr/local/bin/st", "-e", "/usr/bin/top", NULL };
static const char *blinccmd[]    = { "/usr/local/bin/xbacklight", "-inc", "10", NULL };
static const char *bldeccmd[]    = { "/usr/local/bin/xbacklight", "-dec", "10", NULL };
static const char *voltogcmd[]   = { "/home/jozan/.local/bin/mixer-set", "toggle", NULL };
static const char *voldeccmd[]   = { "/home/jozan/.local/bin/mixer-set", "lower", NULL };
static const char *volinccmd[]   = { "/home/jozan/.local/bin/mixer-set", "raise", NULL };
static const char *mpcprevcmd[]  = { "/usr/local/bin/mpc", "prev", NULL };
static const char *mpcnextcmd[]  = { "/usr/local/bin/mpc", "next", NULL };
static const char *mpctogcmd[]   = { "/usr/local/bin/mpc", "toggle", NULL };
static const char *mpcstopcmd[]  = { "/usr/local/bin/mpc", "stop", NULL };
static const char *killespeak[]  = { "/bin/pkill", "espeak", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key                       function        argument */
	{ MODKEY,                       XK_p,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_F1,                    spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_F2,                    spawn,          {.v = editcmd } },
	{ MODKEY,                       XK_F3,                    spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_F3,                    spawn,          {.v = torbrocmd } },
	{ MODKEY,                       XK_F4,                    spawn,          {.v = w3mcmd } },
	{ MODKEY,                       XK_F5,                    spawn,          {.v = nbcmd } },
	{ MODKEY,                       XK_F6,                    spawn,          {.v = ncmpccmd } },
	{ MODKEY,                       XK_F7,                    spawn,          {.v = calcmd } },
	{ MODKEY,                       XK_F8,                    spawn,          {.v = sclicmd } },
	{ MODKEY,                       XK_F9,                    spawn,          {.v = muttcmd } },
	{ MODKEY,                       XK_F10,                   spawn,          {.v = gotopcmd } },
	{ MODKEY,                       XK_F11,                   spawn,          {.v = htopcmd } },
	{ MODKEY,                       XK_F12,                   spawn,          {.v = topcmd } },
	{ MODKEY|ShiftMask,             XK_F6,                    spawn,          {.v = mpcprevcmd } },
	{ MODKEY|ShiftMask,             XK_F7,                    spawn,          {.v = mpctogcmd } },
	{ MODKEY|ShiftMask,             XK_F8,                    spawn,          {.v = mpcnextcmd } },
	{ MODKEY|ShiftMask,             XK_F9,                    spawn,          {.v = mpcstopcmd } },
	{ MODKEY|ShiftMask,             XK_F10,                   spawn,          {.v = voltogcmd } },
	{ MODKEY|ShiftMask,             XK_F11,                   spawn,          {.v = voldeccmd } },
	{ MODKEY|ShiftMask,             XK_F12,                   spawn,          {.v = volinccmd } },
	{ MODKEY|ControlMask,           XK_F9,                    spawn,          {.v = dmkillcmd } },
	{ MODKEY|ControlMask,           XK_F10,                   spawn,          {.v = dmscrotcmd } },
	{ MODKEY|ControlMask,           XK_F11,                   spawn,          {.v = dmsearchcmd } },
	{ MODKEY|ControlMask,           XK_F12,                   spawn,          {.v = dmlogcmd } },
	{ MODKEY,                       XK_BackSpace,             spawn,          {.v = dmpccmd } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = blinccmd } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = bldeccmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = volinccmd } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = voldeccmd } },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = voltogcmd } },
	{ 0,                            XK_Pause,                 spawn,          {.v = killespeak } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_a,                     incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_x,                     incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,                     setmfact,       {.f = -0.025} },
	{ MODKEY|ShiftMask,             XK_l,                     setmfact,       {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_j,                     movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                     movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return,                zoom,           {0} },
	{ METAKEY,                      XK_Escape,                view,           {0} },
	{ MODKEY,                       XK_q,                     killclient,     {0} },
	{ MODKEY,                       XK_s,                     setlayout,      {.v = &layouts[0]} }, /* nbtile */
	{ MODKEY|ShiftMask,             XK_s,                     setlayout,      {.v = &layouts[1]} }, /* nbstack */
	{ MODKEY,                       XK_c,                     setlayout,      {.v = &layouts[2]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,             XK_c,                     setlayout,      {.v = &layouts[3]} }, /* centeredfloatingmaster */
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[4]} }, /* dwindle */
	{ MODKEY|ShiftMask,             XK_t,                     setlayout,      {.v = &layouts[5]} }, /* spiral */
	{ MODKEY,                       XK_v,                     setlayout,      {.v = &layouts[6]} }, /* tile */   
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[7]} }, /* monocle */
	{ MODKEY,                       XK_n,                     setlayout,      {.v = &layouts[8]} }, /* floating */
	{ MODKEY|ShiftMask,             XK_space,                 setlayout,      {0} },
	{ MODKEY,                       XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_f,                     togglefullscr,  {0} },
	{ MODKEY,                       XK_Down,                  moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,                    moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,                 moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,                  moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,                  moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,                    moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,                 moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,                  moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,                    moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,                  moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,                  moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,                 moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,                    moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,                  moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,                  moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,                 moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_bracketleft,           focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_bracketright,          focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,           tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright,          tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_h,                     focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_l,                     focusmon,       {.i = -1 } },
	TAGKEYS(                        XK_1,                                     0)
	TAGKEYS(                        XK_2,                                     1)
	TAGKEYS(                        XK_3,                                     2)
	TAGKEYS(                        XK_4,                                     3)
	TAGKEYS(                        XK_5,                                     4)
	TAGKEYS(                        XK_6,                                     5)
	TAGKEYS(                        XK_7,                                     6)
	TAGKEYS(                        XK_8,                                     7)
	{ MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_e,                     quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,                     quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
