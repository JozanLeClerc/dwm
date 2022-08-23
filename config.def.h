/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 22;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=14" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#6e0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* grid of tags */
#define DRAWCLASSICTAGS             1 << 0
#define DRAWTAGGRID                 1 << 1

#define SWITCHTAG_UP                1 << 0
#define SWITCHTAG_DOWN              1 << 1
#define SWITCHTAG_LEFT              1 << 2
#define SWITCHTAG_RIGHT             1 << 3
#define SWITCHTAG_TOGGLETAG         1 << 4
#define SWITCHTAG_TAG               1 << 5
#define SWITCHTAG_VIEW              1 << 6
#define SWITCHTAG_TOGGLEVIEW        1 << 7

static const unsigned int drawtagmask = DRAWTAGGRID; /* | DRAWCLASSICTAGS to show classic row of tags */
static const int tagrows = 2;

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance    title             tags mask     switchtotag,   isfloating   isfreesize   monitor */
	{ "st",              NULL,       NULL,             0,            0,             0,           0,           -1 },
	{ "St",              NULL,       NULL,             0,            0,             0,           0,           -1 }, /* St with Xresources patch */
	{ "xterm-256color",  NULL,       NULL,             0,            0,             0,           0,           -1 },
	{ "mpv",             NULL,       NULL,             0,            0,             0,           0,           -1 },
	{ "Alacritty",       NULL,       NULL,             0,            0,             0,           0,           -1 },
	{ "KeePass2",        NULL,       NULL,             0,            0,             1,           0,           -1 },
	{ NULL,              NULL,       "Event Tester",   0,            0,             0,           0,           -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define METAKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tagprevmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY,               KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY|ControlMask,   KEY,      toggleview,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]       = { "alacritty", NULL };
static const char *cooltermcmd[]   = { "cool-retro-term", NULL };
static const char *dmenucmd[]      = { "dmenu_run", "-i", "-m", "0", NULL };
static const char *dmpccmd[]       = { "/home/jozan/.local/bin/dmpc", NULL };
static const char *dmkillcmd[]     = { "/home/jozan/.local/bin/dmkill", NULL };
static const char *dmsearchcmd[]   = { "/home/jozan/.local/bin/dmsearch", NULL };
static const char *dmscrotcmd[]    = { "/home/jozan/.local/bin/dmscrot", NULL };
static const char *dmlogcmd[]      = { "/home/jozan/.local/bin/dmlog", NULL };
static const char *dmpassfullcmd[] = { "/home/jozan/.local/bin/dmpass", "--full", NULL };
static const char *dmpasscmd[]     = { "/home/jozan/.local/bin/dmpass", NULL };
static const char *dmotpcmd[]      = { "/home/jozan/.local/bin/dmotp", NULL };
static const char *ndatecmd[]      = { "/home/jozan/.local/bin/ndate", NULL };
static const char *filecmd[]       = { "alacritty", "-e", "zsh", "-ic", "lf", NULL };
static const char *editcmd[]       = { "emacsclient", "-c", NULL };
static const char *browsercmd[]    = { "iridium", "--force-dark-mode", NULL };
static const char *torbrocmd[]     = { "torify", "iridium", "--force-dark-mode", NULL };
static const char *w3mcmd[]        = { "alacritty", "-e", "w3m", "https://start.duckduckgo.com/", NULL };
static const char *nbcmd[]         = { "alacritty", "-e", "newsboat", NULL };
static const char *ncmpccmd[]      = { "alacritty", "-e", "ncmpc", NULL };
static const char *calcmd[]        = { "alacritty", "-e", "calcurse", "-C", "/home/jozan/.config/calcurse", "-D", "/home/jozan/.local/share/calcurse", NULL };
static const char *sclicmd[]       = { "alacritty", "-e", "scli", NULL };
static const char *muttcmd[]       = { "alacritty", "-e", "neomutt", NULL };
static const char *gotopcmd[]      = { "alacritty", "-e", "gotop", NULL };
static const char *htopcmd[]       = { "alacritty", "-e", "htop", NULL };
static const char *topcmd[]        = { "alacritty", "-e", "top", NULL };
static const char *blinccmd[]      = { "xbacklight", "-inc", "10", NULL };
static const char *bldeccmd[]      = { "xbacklight", "-dec", "10", NULL };
static const char *voltogcmd[]     = { "/home/jozan/.local/bin/mixer-set", "toggle", NULL };
static const char *voldeccmd[]     = { "/home/jozan/.local/bin/mixer-set", "lower", NULL };
static const char *volinccmd[]     = { "/home/jozan/.local/bin/mixer-set", "raise", NULL };
static const char *miccmd[]        = { "/home/jozan/.local/bin/mic", NULL };
static const char *mpcprevcmd[]    = { "mpc", "prev", NULL };
static const char *mpcnextcmd[]    = { "mpc", "next", NULL };
static const char *mpctogcmd[]     = { "mpc", "toggle", NULL };
static const char *mpcstopcmd[]    = { "mpc", "stop", NULL };
static const char *killespeak[]    = { "/home/jozan/.local/bin/shutup", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,                     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return,                spawn,          {.v = cooltermcmd } },
	{ MODKEY,                       XK_F1,                    spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_F2,                    spawn,          {.v = editcmd } },
	{ MODKEY,                       XK_F3,                    spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_F3,                    spawn,          {.v = torbrocmd } },
	{ MODKEY,                       XK_F4,                    spawn,          {.v = w3mcmd } },
	{ MODKEY,                       XK_F5,                    spawn,          {.v = ncmpccmd } },
	{ MODKEY,                       XK_F6,                    spawn,          {.v = nbcmd} },
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
	{ MODKEY|ShiftMask,             XK_Delete,                spawn,          {.v = miccmd } },
	{ MODKEY|ControlMask,           XK_F9,                    spawn,          {.v = dmkillcmd } },
	{ MODKEY|ControlMask,           XK_F10,                   spawn,          {.v = dmscrotcmd } },
	{ MODKEY|ControlMask,           XK_F11,                   spawn,          {.v = dmsearchcmd } },
	{ MODKEY|ControlMask,           XK_F12,                   spawn,          {.v = dmlogcmd } },
	{ MODKEY|ControlMask,           XK_BackSpace,             spawn,          {.v = dmlogcmd } },
	{ MODKEY,                       XK_BackSpace,             spawn,          {.v = dmpccmd } },
	{ MODKEY|ControlMask,           XK_p,                     spawn,          {.v = dmpasscmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_p,                     spawn,          {.v = dmpassfullcmd } },
	{ MODKEY|ControlMask,           XK_o,                     spawn,          {.v = dmotpcmd } },
	{ MODKEY,                       XK_End,                   spawn,          {.v = ndatecmd } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = blinccmd } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = bldeccmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = volinccmd } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = voldeccmd } },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = voltogcmd } },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = voltogcmd } },
	{ 0,                            XF86XK_AudioPlay,         spawn,          {.v = mpctogcmd } },
	{ 0,                            XF86XK_AudioPrev,         spawn,          {.v = mpcprevcmd } },
	{ 0,                            XF86XK_AudioNext,         spawn,          {.v = mpcnextcmd } },
	{ MODKEY,                       XK_Delete,                spawn,          {.v = killespeak } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_a,                     incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_x,                     incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_minus,                 setmfact,       {.f = -0.025} },
	{ MODKEY|ControlMask,           XK_equal,                 setmfact,       {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_j,                     movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                     movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return,                zoom,           {0} },
	{ METAKEY,                      XK_Escape,                view,           {0} },
	{ MODKEY,                       XK_q,                     killclient,     {0} },
	{ MODKEY,                       XK_s,                     setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_c,                     setlayout,      {.v = &layouts[1]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,             XK_c,                     setlayout,      {.v = &layouts[2]} }, /* centeredfloatingmaster */
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[3]} }, /* monocle */
	{ MODKEY,                       XK_n,                     setlayout,      {.v = &layouts[4]} }, /* floating */
	{ MODKEY|ShiftMask,             XK_space,                 setlayout,      {0} },
	{ MODKEY,                       XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_f,                     togglefullscr,  {0} },
	{ MODKEY,                       XK_bracketleft,           focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_bracketright,          focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_h,                     focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_l,                     focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,           tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketright,          tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,                     tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,                     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,           focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketright,          focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,                     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,                     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_w,                     movemouse,      {0} },
	{ MODKEY|ShiftMask,             XK_w,                     resizemouse,    {0} },
	{ MODKEY,                       XK_minus,                 setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,                 setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,                 setgaps,        {.i = 0  } },
	{ MODKEY|ControlMask,           XK_k,                     switchtag,      { .ui = SWITCHTAG_UP     | SWITCHTAG_VIEW } },
	{ MODKEY|ControlMask,           XK_j,                     switchtag,      { .ui = SWITCHTAG_DOWN   | SWITCHTAG_VIEW } },
	{ MODKEY|ControlMask,           XK_l,                     switchtag,      { .ui = SWITCHTAG_RIGHT  | SWITCHTAG_VIEW } },
	{ MODKEY|ControlMask,           XK_h,                     switchtag,      { .ui = SWITCHTAG_LEFT   | SWITCHTAG_VIEW } },
	{ MODKEY|METAKEY,               XK_k,                     switchtag,      { .ui = SWITCHTAG_UP     | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
	{ MODKEY|METAKEY,               XK_j,                     switchtag,      { .ui = SWITCHTAG_DOWN   | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
	{ MODKEY|METAKEY,               XK_l,                     switchtag,      { .ui = SWITCHTAG_RIGHT  | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
	{ MODKEY|METAKEY,               XK_h,                     switchtag,      { .ui = SWITCHTAG_LEFT   | SWITCHTAG_TAG | SWITCHTAG_VIEW } },
	TAGKEYS(                        XK_1,                                     0)
	TAGKEYS(                        XK_2,                                     1)
	TAGKEYS(                        XK_3,                                     2)
	TAGKEYS(                        XK_4,                                     3)
	TAGKEYS(                        XK_5,                                     4)
	TAGKEYS(                        XK_6,                                     5)
	TAGKEYS(                        XK_7,                                     6)
	TAGKEYS(                        XK_8,                                     7)
	TAGKEYS(                        XK_9,                                     8)
	{ MODKEY,                       XK_0,                      view,          {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_e,                      quit,          {0} },
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

