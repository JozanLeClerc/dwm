/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 24;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "Hack Nerd Font:size=14" };
// static const char *fonts[]          = { "Terminess Nerd Font:style=Bold:size=13" };
// static const char *fonts[]          = { "GohuFont 11 Nerd Font:size=13" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#1d2021"; /* bar background */
static const char col_gray2[]       = "#32302f"; /* last square, windows borders */
static const char col_gray3[]       = "#ebdbb2"; /* squares bg, maybe text */
static const char col_gray4[]       = "#ebdbb2"; /* selected square */
static const char col_cyan[]        = "#9d0006"; /* red tint */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = { "alacritty", "--class", "spterm", NULL };
const char *spcmd2[] = { "alacritty", "--class", "spfm", "-e", "zsh", "-ic", "lf", NULL };
const char *spcmd3[] = { "pcmanfm", NULL };
const char *spcmd4[] = { "alacritty", "--class", "spflip", "-e", "hf", NULL };
const char *spcmd5[] = { "alacritty", "--class", "spmpd", "-e", "ncmpc", NULL };
const char *spcmd6[] = { "alacritty", "--class", "spnews", "-e", "nb", NULL };
static Sp scratchpads[] = {
	/* name     cmd  */
	{"spterm",  spcmd1},
	{"spfm",    spcmd2},
	{"spfmgui", spcmd3},
	{"spflip",  spcmd4},
	{"spmpd",   spcmd5},
	{"spnews",  spcmd6},
};

/* tagging */
static const char *tags[] = {
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  ",
	"  "
};

static const unsigned int ulinepad	= 6;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 3;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const char *tagsel[][3] = {
	/* fg        bg */
	// gruvbox light
	// { "#9d0006", "#1d2021", "" }, // red
	// { "#79740e", "#1d2021", "" }, // green
	// { "#b57614", "#1d2021", "" }, // yellow
	// { "#076678", "#1d2021", "" }, // blue
	// { "#8f3f71", "#1d2021", "" }, // magenta
	// { "#427b58", "#1d2021", "" }, // cyan
	// { "#af3a03", "#1d2021", "" }, // orange
	// { "#928374", "#1d2021", "" }, // gray
	// { "#ebdbb2", "#1d2021", "" }, // white
	// gruvbox dark
	{ "#cc241d", "#1d2021" }, // red
	{ "#d65d0e", "#1d2021" }, // orange
	{ "#d79921", "#1d2021" }, // yellow
	{ "#458588", "#1d2021" }, // blue
	{ "#8ec07c", "#1d2021" }, // cyan
	{ "#98971a", "#1d2021" }, // green
	{ "#b16286", "#1d2021" }, // magenta
	{ "#fe8019", "#1d2021" }, // re orange
	{ "#ebdbb2", "#1d2021" }, // white
	{ "#7c6f64", "#1d2021" }, // empty
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance    title  tags mask  isfloating   isterminal noswallow   monitor */
	{ "st",                  NULL,       NULL,  0,         0,           1,         0,         -1 },
	{ "St",                  NULL,       NULL,  0,         0,           1,         0,         -1 }, /* St with Xresources patch */
	{ "xterm-256color",      NULL,       NULL,  0,         0,           1,         0,         -1 },
	{ "mpv",                 NULL,       NULL,  0,         0,           0,         0,         -1 },
	{ "Alacritty",           NULL,       NULL,  0,         0,           1,         0,         -1 },
	{ "rclone-browser",      NULL,       NULL,  1 << 1,    0,           0,         0,          2 },
	{ "org.remmina.Remmina", NULL,       NULL,  1 << 2,    0,           0,         0,          2 },
	{ "Vmware",              NULL,       NULL,  1 << 3,    0,           0,         0,          2 },
	{ "teams-for-linux",     NULL,       NULL,  0,         0,           0,         0,          1 },
	{ "thunderbird",         NULL,       NULL,  1 << 2,    0,           0,         0,          1 },
	{ NULL,                  "spterm",   NULL,  SPTAG(0),  1,           0,         0,         -1 },
	{ NULL,                  "spfm",     NULL,  SPTAG(1),  1,           1,         0,         -1 },
	{ NULL,                  "pcmanfm",  NULL,  SPTAG(2),  1,           0,         0,         -1 },
	{ NULL,                  "spflip",   NULL,  SPTAG(3),  1,           1,         0,         -1 },
	{ NULL,                  "spmpd",    NULL,  SPTAG(4),  1,           1,         0,         -1 },
	{ NULL,                  "spnews",   NULL,  SPTAG(5),  0,           1,         0,         -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const float fgw = .75, fgh = .75;

#define FORCE_VSPLIT 1

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "###",      nrowgrid },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define METAKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY|ControlMask,   KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|METAKEY,               KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tagprevmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      tagnextmon,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *term_cmd[]        = { "alacritty", NULL };
static const char *hardflip_cmd[]    = { "alacritty", "-e", "hf", NULL };
static const char *dmenucmd[]        = { "dmrun", NULL };
static const char *dmapps_cmd[]      = { "dmapps", NULL };
static const char *dmpc_cmd[]        = { "dmpc", NULL };
static const char *dmbookm_cmd[]     = { "dmbookm", NULL };
static const char *dmkill_cmd[]      = { "dmkill", NULL };
static const char *dmsearch_cmd[]    = { "dmsearch", NULL };
static const char *dmscrot_cmd[]     = { "dmscrot", NULL };
static const char *dmlog_cmd[]       = { "dmlog", NULL };
static const char *dmpass_full_cmd[] = { "dmpass", "--full", NULL };
static const char *dmpass_cmd[]      = { "dmpass", NULL };
static const char *dmotp_cmd[]       = { "dmotp", NULL };
static const char *dmclip_cmd[]      = { "dmclip", NULL };
static const char *ndate_cmd[]       = { "ndate", NULL };
// static const char *file_cmd[]        = { "alacritty", "-e", "zsh", "-ic", "lf", NULL };
// static const char *file_alt_cmd[]    = { "pcmanfm", NULL };
// static const char *edit_cmd[]        = { "emacsclient", "-c", NULL };
static const char *browser_cmd[]     = { "firefox", NULL };
static const char *torbro_cmd[]      = { "torify", "librewolf", NULL };
// static const char *nb_cmd[]          = { "alacritty", "-e", "newsboat", NULL };
// static const char *ncmpc_cmd[]       = { "alacritty", "-e", "ncmpc", NULL };
static const char *cal_cmd[]         = { "alacritty", "-e", "calcurse", "-C", "/home/jozan/.config/calcurse", "-D", "/home/jozan/.local/share/calcurse", NULL };
static const char *scli_cmd[]        = { "alacritty", "-e", "scli", NULL };
static const char *mutt_cmd[]        = { "alacritty", "-e", "neomutt", NULL };
static const char *gotop_cmd[]       = { "alacritty", "-e", "gotop", NULL };
static const char *htop_cmd[]        = { "alacritty", "-e", "htop", NULL };
static const char *top_cmd[]         = { "alacritty", "-e", "top", NULL };
static const char *bl_inc_cmd[]      = { "xbacklight", "-inc", "10", NULL };
static const char *bl_dec_cmd[]      = { "xbacklight", "-dec", "10", NULL };
static const char *vol_tog_cmd[]     = { "mixer-set", "toggle", NULL };
static const char *vol_dec_cmd[]     = { "mixer-set", "lower", NULL };
static const char *vol_inc_cmd[]     = { "mixer-set", "raise", NULL };
static const char *mic_cmd[]         = { "mic", NULL };
static const char *mpc_prev_cmd[]    = { "mpc", "prev", NULL };
static const char *mpc_next_cmd[]    = { "mpc", "next", NULL };
static const char *mpc_tog_cmd[]     = { "mpc", "toggle", NULL };
static const char *mpc_stop_cmd[]    = { "mpc", "stop", NULL };
static const char *killespeak_cmd[]  = { "/home/jozan/.local/bin/shutup", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	{ MODKEY,                       XK_p,                     dmenuspawn,     {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                spawn,          {.v = term_cmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_Return,                spawn,          {.v = hardflip_cmd } },
	{ MODKEY|ControlMask,           XK_Return,                dmenuspawn,     {.v = dmapps_cmd } },
	{ MODKEY,                       XK_F1,                    togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_F2,                    togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_F2,                    togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_F3,                    spawn,          {.v = browser_cmd } },
	{ MODKEY|ShiftMask,             XK_F3,                    spawn,          {.v = torbro_cmd } },
	{ MODKEY,                       XK_F4,                    togglescratch,  {.ui = 3 } },
	{ MODKEY,                       XK_F5,                    togglescratch,  {.ui = 4 } },
	{ MODKEY,                       XK_F6,                    togglescratch,  {.ui = 5 } },
	{ MODKEY,                       XK_F7,                    spawn,          {.v = cal_cmd } },
	{ MODKEY,                       XK_F8,                    spawn,          {.v = scli_cmd } },
	{ MODKEY,                       XK_F9,                    spawn,          {.v = mutt_cmd } },
	{ MODKEY,                       XK_F10,                   spawn,          {.v = gotop_cmd } },
	{ MODKEY,                       XK_F11,                   spawn,          {.v = htop_cmd } },
	{ MODKEY,                       XK_F12,                   spawn,          {.v = top_cmd } },
	{ MODKEY|ShiftMask,             XK_F6,                    spawn,          {.v = mpc_prev_cmd } },
	{ MODKEY|ShiftMask,             XK_F7,                    spawn,          {.v = mpc_tog_cmd } },
	{ MODKEY|ShiftMask,             XK_F8,                    spawn,          {.v = mpc_next_cmd } },
	{ MODKEY|ShiftMask,             XK_F9,                    spawn,          {.v = mpc_stop_cmd } },
	{ MODKEY|ShiftMask,             XK_F10,                   spawn,          {.v = vol_tog_cmd } },
	{ MODKEY|ShiftMask,             XK_F11,                   spawn,          {.v = vol_dec_cmd } },
	{ MODKEY|ShiftMask,             XK_F12,                   spawn,          {.v = vol_inc_cmd } },
	{ MODKEY|ShiftMask,             XK_Delete,                spawn,          {.v = mic_cmd } },
	{ MODKEY|ControlMask,           XK_Delete,                spawn,          {.v = mic_cmd } },
	{ MODKEY|ControlMask,           XK_F7,                    dmenuspawn,     {.v = dmbookm_cmd } },
	{ MODKEY|ControlMask,           XK_F8,                    dmenuspawn,     {.v = dmclip_cmd } },
	{ MODKEY|ControlMask,           XK_F9,                    dmenuspawn,     {.v = dmkill_cmd } },
	{ MODKEY|ControlMask,           XK_F10,                   dmenuspawn,     {.v = dmscrot_cmd } },
	{ MODKEY|ControlMask,           XK_F11,                   dmenuspawn,     {.v = dmsearch_cmd } },
	{ MODKEY|ControlMask,           XK_F12,                   dmenuspawn,     {.v = dmlog_cmd } },
	{ MODKEY|ControlMask,           XK_BackSpace,             dmenuspawn,     {.v = dmlog_cmd } },
	{ MODKEY,                       XK_BackSpace,             dmenuspawn,     {.v = dmpc_cmd } },
	{ MODKEY|ControlMask,           XK_p,                     dmenuspawn,     {.v = dmpass_cmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_p,                     dmenuspawn,     {.v = dmpass_full_cmd } },
	{ MODKEY|ControlMask,           XK_o,                     dmenuspawn,     {.v = dmotp_cmd } },
	{ MODKEY,                       XK_End,                   spawn,          {.v = ndate_cmd } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = bl_inc_cmd } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = bl_dec_cmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          {.v = vol_inc_cmd } },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          {.v = vol_dec_cmd } },
	{ 0,                            XF86XK_AudioMute,         spawn,          {.v = vol_tog_cmd } },
	{ 0,                            XF86XK_AudioPlay,         spawn,          {.v = mpc_tog_cmd } },
	{ 0,                            XF86XK_AudioPrev,         spawn,          {.v = mpc_prev_cmd } },
	{ 0,                            XF86XK_AudioNext,         spawn,          {.v = mpc_next_cmd } },
	{ MODKEY,                       XK_Delete,                spawn,          {.v = killespeak_cmd } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_a,                     incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_x,                     incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_minus,                 setmfact,       {.f = -0.025} },
	{ MODKEY|ControlMask,           XK_equal,                 setmfact,       {.f = +0.025} },
	{ MODKEY|ControlMask|ShiftMask, XK_minus,                 setcfact,       {.f = -0.05} },
	{ MODKEY|ControlMask|ShiftMask, XK_equal,                 setcfact,       {.f = +0.05} },
	{ MODKEY|ControlMask|ShiftMask, XK_0,                     setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_j,                     movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                     movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return,                zoom,           {0} },
	{ METAKEY,                      XK_Escape,                view,           {0} },
	{ MODKEY,                       XK_q,                     killclient,     {0} },
	{ MODKEY,                       XK_s,                     setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,             XK_s,                     setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_z,                     setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,             XK_z,                     setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_x,                     setlayout,      {.v = &layouts[1]} }, /* bottoastack */
	{ MODKEY|ShiftMask,             XK_x,                     setlayout,      {.v = &layouts[2]} }, /* bottomstackhoriz */
	{ MODKEY,                       XK_c,                     setlayout,      {.v = &layouts[3]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,             XK_c,                     setlayout,      {.v = &layouts[4]} }, /* centeredfloatingmaster */
	{ MODKEY,                       XK_v,                     setlayout,      {.v = &layouts[5]} }, /* centeredmaster */
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[6]} }, /* monocle */
	{ MODKEY,                       XK_n,                     setlayout,      {.v = &layouts[7]} }, /* floating */
	{ MODKEY|ShiftMask,             XK_space,                 setlayout,      {0} },
	{ MODKEY,                       XK_space,                 togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_space,                 toggleforegrounded, {0} },
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
	{ MODKEY|ControlMask,           XK_h,                     shiftview,      { .i = -1 } },
	{ MODKEY|ControlMask,           XK_l,                     shiftview,      { .i = +1 } },
	{ MODKEY|METAKEY,               XK_h,                     shiftboth,      { .i = -1 } },
	{ MODKEY|METAKEY,               XK_l,                     shiftboth,      { .i = +1 } },
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
	{ MODKEY|ShiftMask,             XK_r,                      quit,          {1} },
	{ MODKEY,                       XK_o,                      winview,       {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = term_cmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
