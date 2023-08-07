/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define BROWSER "firefox"

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 16;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no standard bar */
static int topbar             = 1;        /* 0 means standard bar at bottom */
static const int extrabar           = 1;        /* 0 means no extra bar */
static const char statussep         = '\t';      /* separator between statuses */
static const char *fonts[]          = { "Symbols Nerd Font:size=10:antialias=true:autohint=true", /* Override built in icons to fonts */
                                        "FiraCode:pixelsize=12:antialias=true:autohint=true",
                                        "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true",
                                        "IPAGothic-10", /* Japanese */ };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char color0[]                = "#000000";
static char color1[]                = "#7f0000";
static char color2[]                = "#007f00";
static char color3[]                = "#7f7f00";
static char color4[]                = "#00007f";
static char color5[]                = "#7f007f";
static char color6[]                = "#007f7f";
static char color7[]                = "#cccccc";
static char color8[]                = "#333333";
static char color9[]                = "#ff0000";
static char color10[]               = "#00ff00";
static char color11[]               = "#ffff00";
static char color12[]               = "#0000ff";
static char color13[]               = "#ff00ff";
static char color14[]               = "#00ffff";
static char color15[]               = "#ffffff";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const char *barcolors[] = {
	color0,
	color1,
	color2,
	color3,
	color4,
	color5,
	color6,
	color7,
	color8,
	color9,
	color10,
	color11,
	color12,
	color13,
	color14,
	color15,
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* {class, instance, title, tags mask, isfloating, monitor */
	{ "Gimp",       NULL,   NULL,   0,          1,  -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
    { "zoom",       NULL,   NULL,   1 << 4,     1,  -1 },
    { "calibre",    NULL,   NULL,   1 << 7,     0,  -1},
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ ":::",      gaplessgrid },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[M]",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define SUPER Mod4Mask
#define HYPER Mod3Mask
#define SHIFT ShiftMask
#define LVL3  Mod5Mask

#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
        /* Colors for the status bar */
		{ "color0",        STRING,  &color0 },
		{ "color1",        STRING,  &color1 },
		{ "color2",        STRING,  &color2 },
		{ "color3",        STRING,  &color3 },
		{ "color4",        STRING,  &color4 },
		{ "color5",        STRING,  &color5 },
		{ "color6",        STRING,  &color6 },
		{ "color7",        STRING,  &color7 },
		{ "color8",        STRING,  &color8 },
		{ "color9",        STRING,  &color9 },
		{ "color10",        STRING,  &color10 },
		{ "color11",        STRING,  &color11 },
		{ "color12",        STRING,  &color12 },
		{ "color13",        STRING,  &color13 },
		{ "color14",        STRING,  &color14 },
		{ "color15",        STRING,  &color15 },
};

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier             chain, key      function        argument */
	{ SUPER,                -1, XK_d,       spawn,          {.v = dmenucmd } },
	{ SUPER,                -1, XK_Return,  spawn,          {.v = termcmd } },
	{ SUPER,                -1, XK_b,       togglebar,      {0} },
	{ SUPER,                -1, XK_j,       focusstack,     {.i = +1 } },
	{ SUPER,                -1, XK_k,       focusstack,     {.i = -1 } },
	{ SUPER,                -1, XK_equal,   incnmaster,     {.i = +1 } },
	{ SUPER,                -1, XK_minus,   incnmaster,     {.i = -1 } },
	{ SUPER,                -1, XK_h,       setmfact,       {.f = -0.05} },
	{ SUPER,                -1, XK_l,       setmfact,       {.f = +0.05} },
	{ SUPER|SHIFT,          -1, XK_h,       setcfact,       {.f = +0.25} },
	{ SUPER|SHIFT,          -1, XK_l,       setcfact,       {.f = -0.25} },
	{ SUPER|SHIFT,          -1, XK_o,       setcfact,       {.f =  0.00} },
	{ SUPER|SHIFT,          -1, XK_Return,  zoom,           {0} },
	{ SUPER,                -1, XK_Tab,     view,           {0} },
    { SUPER,                -1, XK_f,       togglefullscr,  {0} },
	{ SUPER,                -1, XK_q,       killclient,     {0} },
	{ SUPER,                -1, XK_t,       setlayout,      {.v = &layouts[0]} },
	{ SUPER,                -1, XK_s,       togglefloating, {0} },
	{ SUPER,                -1, XK_g,       setlayout,      {.v = &layouts[2]} },
	{ SUPER,                -1, XK_space,   setlayout,      {0} },
	{ SUPER,                -1, XK_0,       view,           {.ui = ~0 } },
	{ SUPER|SHIFT,          -1, XK_0,       tag,            {.ui = ~0 } },
	{ SUPER,                -1, XK_comma,   focusmon,       {.i = -1 } },
	{ SUPER,                -1, XK_period,  focusmon,       {.i = +1 } },
	{ SUPER|SHIFT,          -1, XK_comma,   tagmon,         {.i = -1 } },
	{ SUPER|SHIFT,          -1, XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(                -1, XK_1,                       0)
	TAGKEYS(                -1, XK_2,                       1)
	TAGKEYS(                -1, XK_3,                       2)
	TAGKEYS(                -1, XK_4,                       3)
	TAGKEYS(                -1, XK_5,                       4)
	TAGKEYS(                -1, XK_6,                       5)
	TAGKEYS(                -1, XK_7,                       6)
	TAGKEYS(                -1, XK_8,                       7)
	TAGKEYS(                -1, XK_9,                       8)
	{ SUPER|SHIFT,          -1, XK_q,       quit,           {0} },
	{ SUPER|SHIFT,          -1, XK_r,       quit,           {1} }, 
    { SUPER,			    XK_r, XK_Return,		spawn,		    {.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
    { SUPER,                XK_r, XK_n,             spawn,          SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+1 dwmblocks") },
    { 0,			        -1, XK_Print,	spawn,		    {.v = (const char*[]){ "flameshot", "screen", NULL } } },
    { SHIFT,                -1, XK_Print,   spawn,		    {.v = (const char*[]){ "flameshot", "gui", NULL } } },

    /* XF86 keys */
    { 0, -1,    XF86XK_AudioMute,           spawn,  SHCMD("pamixer -t; kill -42 $(pidof dwmblocks)") },
    { 0, -1,    XF86XK_AudioRaiseVolume,    spawn,  SHCMD("pamixer -i 5; kill -42 $(pidof dwmblocks)") },
    { 0, -1,    XF86XK_AudioLowerVolume,    spawn,  SHCMD("pamixer -d 5; kill -42 $(pidof dwmblocks)") },
    { 0, -1,    XF86XK_MonBrightnessUp,     spawn,  {.v = (const char*[]){ "xbacklight", "-inc", "5", NULL } } },
	{ 0, -1,    XF86XK_MonBrightnessDown,   spawn,  {.v = (const char*[]){ "xbacklight", "-dec", "5", NULL } } },
    { 0, -1,    XF86XK_AudioPlay,           spawn,  { .v = (const char*[]){"mpc", "toggle", NULL} } },

    /* Thinkpad emulation with the LVL3 key */
    { LVL3, -1,     XK_Down,    spawn,  { .v = (const char*[]){"mpc", "toggle", NULL} } },
    { LVL3, -1,     XK_Up,      spawn,  { .v = (const char*[]){"mpc", "stop", NULL} } },
    { LVL3, -1,     XK_Left,    spawn,  { .v = (const char*[]){"mpc", "prev", NULL} } },
    { LVL3, -1,     XK_Right,   spawn,  { .v = (const char*[]){"mpc", "next", NULL} } },

    /* mpc keybinds */
    { SUPER,  XK_m,       XK_p,       spawn,          { .v = (const char*[]){"mpc", "toggle", NULL} } },
    { SUPER,  XK_m,       XK_comma,   spawn,          { .v = (const char*[]){"mpc", "prev", NULL} } },
    { SUPER,  XK_m,       XK_period,  spawn,          { .v = (const char*[]){"mpc", "next", NULL} } },
    { SUPER,  XK_m,       XK_1,       spawn,          { .v = (const char*[]){"radio", NULL} } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         SUPER,          Button1,        movemouse,      {0} },
	{ ClkClientWin,         SUPER,          Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,          Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            SUPER,          Button1,        tag,            {0} },
	{ ClkTagBar,            SUPER,          Button3,        toggletag,      {0} },
};

