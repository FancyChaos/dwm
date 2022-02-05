/* See LICENSE file for copyright and license details. */

/* appearance */

/* Gaps and borders */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

/* Look and feel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]              = {
        "Fira Code Nerd Font:pixelsize=18:antialias=true"
};
static const char dmenufont[]       = "Fira Code Nerd Font:pixelsize=18:antialias=true";

/* Colors */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#DE5100";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>
#include "shift-tools.c"

static Key keys[] = {
	/* modifier                     key        function        argument */

        /* Standard TAGKEYS to switch between tags */
        TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },

        /* Keybinding of shift-tools patch for switching between tags */
        { MODKEY|ControlMask,           XK_Right,  shiftview,      { .i = +1 } },
        { MODKEY|ControlMask,           XK_Left,   shiftview,      { .i = -1 } },

        { MODKEY|ShiftMask,             XK_x,      shiftboth,      { .i = +1 }  },
        { MODKEY|ShiftMask,             XK_y,      shiftboth,      { .i = -1 }  },

        { MODKEY|ShiftMask,             XK_Right,  pushup,         {0}  },
        { MODKEY|ShiftMask,             XK_Left,   pushdown,       {0}  },
        { MODKEY|ShiftMask,             XK_j,      pushup,         {0}  },
        { MODKEY|ShiftMask,             XK_k,      pushdown,       {0}  },

        /* Generic key bindings */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_x,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY,                       XK_m,      spawn,          SHCMD("instantlock") },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

        /* Special key bindings (multimedia) */
        { 0,                XF86XK_MonBrightnessUp,   spawn, SHCMD("fbrightness +1") },
        { 0,                XF86XK_MonBrightnessDown, spawn, SHCMD("fbrightness -1") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
};

