/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows
*/ static const Gap default_gap        = {.isgap = 8, .realgap = 8, .gappx
= 8}; static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10",
"NotoColorEmoji:pixelsize=13:antialias=true:autohint=true" }; static const
char dmenufont[]       = "monospace:size=10";
// static const char col_gray1[]       = "#1C1F26";
// static const char col_gray2[]       = "#444444";
// static const char col_gray3[]       = "#bbbbbb";
// static const char col_gray4[]       = "#7393B3";
// static const char col_cyan[]        = "#272b35";
//
// static const char *colors[][3]      = {
// 	/*               fg         bg         border   */
// 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
// 	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
// };
 static const char col_gray1[]       = "#222222";
 static const char col_gray2[]       = "#444444";
 static const char col_gray3[]       = "#bbbbbb";
 static const char col_gray4[]       = "#eeeeee";
 static const char col_cyan[]        = "#005577";
 static const char *colors[][3]      = {
 	/*               fg         bg         border   */
 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
 	[SchemeSel]  = { col_gray4, col_cyan,  col_gray2 },
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
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/fish", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

/* audio control */
#include <X11/XF86keysym.h>

// static const char *upvol[] = { "/usr/bin/amixer", "set", "Master", "1%+", NULL };
// static const char *downvol[] = { "/usr/bin/amixer", "set", "Master", "1%-", NULL };
// static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle", NULL };

#define XK_VolM 0x1008FF12
#define XK_AuPlay 0x1008FF14
#define XK_AuPrev 0x1008FF16
#define XK_AuNext 0x1008FF17

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
//    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
//  	{ 0,					        XK_VolM,   spawn, {.v = mutevol} },
//	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
    { 0,                            XF86XK_AudioLowerVolume, spawn, SHCMD("amixer set Master 1%- && pkill -RTMIN+10 dwmblocks") },
  	{ 0,					        XK_VolM,   spawn, SHCMD("amixer set Master toggle && pkill -RTMIN+10 dwmblocks")},
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, SHCMD("amixer set Master 1%+ && pkill -RTMIN+10 dwmblocks") },
  	{ 0,	        				XK_AuPlay, spawn,		   SHCMD("playerctl play-pause") },
	{ 0,		        			XK_AuPrev, spawn,		   SHCMD("playerctl previous") },
	{ 0,			        		XK_AuNext, spawn,		   SHCMD("playerctl next") },
  	{ 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set +1%") },
  	{ 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 1%-") },
	// { MODKEY,                       XK_r,      spawn,          SHCMD("launcher") },
	{ MODKEY,			XK_s,	    spawn,	   SHCMD("librewolf") },
	{ MODKEY,			XK_c,       spawn,	   SHCMD("st -e nvim ~/Software/dwm/config.h") },
    { MODKEY,           XK_n,       spawn,     SHCMD("st -e nvim") },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd} },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd} },
	{ MODKEY,                       XK_Return, spawn,          SHCMD("st fish") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_l,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      rotatestack,    {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_j,      focusstack,     {.i = +1 } }, 
	{ MODKEY|Mod1Mask,              XK_k,      focusstack,     {.i = -1 } }, 
	{ MODKEY,                       XK_h,      focusdir,       {.i = 0 } }, // left
	{ MODKEY,                       XK_l,      focusdir,       {.i = 1 } }, // right
	{ MODKEY,                       XK_k,      focusdir,       {.i = 2 } }, // up
	{ MODKEY,                       XK_j,      focusdir,       {.i = 3 } }, // down
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
    { MODKEY|ControlMask,           XK_r,      quit,           {1} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

