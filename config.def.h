/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no standard bar */
static const int topbar             = 1;        /* 0 means standard bar at bottom */
static const int extrabar           = 1;        /* 0 means no extra bar */
static const char statussep         = '\t';      /* separator between statuses */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const char *barcolors[] = {
	"#000000",
	"#7f0000",
	"#007f00",
	"#7f7f00",
	"#00007f",
	"#7f007f",
	"#007f7f",
	"#cccccc",
	"#333333",
	"#ff0000",
	"#00ff00",
	"#ffff00",
	"#0000ff",
	"#ff00ff",
	"#00ffff",
	"#ffffff",
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
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
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
+static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

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
};

static const Key keys[] = {
	/* modifier                     chainkey,   key        function        argument */
	{ MODKEY,                       -1,         XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             -1,         XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       -1,         XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             -1,         XK_b,      toggleextrabar, {0} },
	{ MODKEY,                       -1,         XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       -1,         XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             -1,         XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             -1,         XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             -1,         XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       -1,         XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              -1,         XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              -1,         XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    -1,         XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       -1,         XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             -1,         XK_c,      killclient,     {0} },
	{ MODKEY,                       -1,         XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       -1,         XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       -1,         XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       -1,         XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             -1,         XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             -1,         XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       -1,         XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,         XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       -1,         XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       -1,         XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,         XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             -1,         XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        -1,         XK_1,                      0)
	TAGKEYS(                        -1,         XK_2,                      1)
	TAGKEYS(                        -1,         XK_3,                      2)
	TAGKEYS(                        -1,         XK_4,                      3)
	TAGKEYS(                        -1,         XK_5,                      4)
	TAGKEYS(                        -1,         XK_6,                      5)
	TAGKEYS(                        -1,         XK_7,                      6)
	TAGKEYS(                        -1,         XK_8,                      7)
	TAGKEYS(                        -1,         XK_9,                      8)
	{ MODKEY|ShiftMask,             -1,         XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, -1,         XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

