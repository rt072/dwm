/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 7;        /* horizontal padding for statusbar */
static const int vertpadbar         = 1;        /* vertical padding for statusbar */
static const char *fonts[]          = { "Liberation Mono:size=10",
                                        "FontAwesome:size=9:antialias=true:autohint=true"
};
static const char dmenufont[]       = "Liberation Mono:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#4e9699";

static const unsigned int baralpha = 0xee;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     		 instance    title       tags mask     isfloating   	monitor */
	{ "Gimp",    		  NULL,       NULL,       0,            	 1,           -1 },
	{ "Firefox", 		  NULL,       NULL,       1 << 2,          	 0,           -1 },
	{ "Spacefm",  		  NULL,       NULL,       0,         	     1,           -1 },
    { "TelegramDesktop",  NULL,       NULL,       1 << 3,            1,           -1 },
	{ "Claws-mail", 	  NULL,       NULL,       1 << 3,            1,           -1 },
	{ "Seafile Client",   NULL,       NULL,       1 << 3,            1,           -1 },
	{ "Mousepad", 		  NULL,       NULL,       0,    	         1,           -1 },
	{ "Subl3", 			  NULL,       NULL,       1 << 5,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "HHH",      grid },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_settings", NULL };
static const char *termcmd[]  = { "st", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod1Mask,             	    XK_F2,      spawn,          {.v = dmenucmd } },
	{ MODKEY,		                XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,       togglebar,      {0} },
    { MODKEY|ShiftMask,             XK_j,       rotatestack,    {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,       rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
	// { Mod1Mask,                     XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,     view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,       killclient,     {0} },
	{ MODKEY,                       XK_t,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,       setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,       setlayout,      {.v = &layouts[3]} },
    { MODKEY|ControlMask,           XK_comma,   cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,           XK_period,  cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	TAGKEYS(                        XK_7,                       6)
	TAGKEYS(                        XK_8,                       7)
	TAGKEYS(                        XK_9,                       8)
    { MODKEY|ShiftMask,       		XK_r,      self_restart,    {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,            {0} },

	/* User Programs */
	{ MODKEY , 			      		XK_Escape,  spawn,	        SHCMD ("oblogout")},
    { 0,                      		0x1008ff02, spawn,          SHCMD ("xbacklight -inc 5 && xbacklight_notify")},
    { 0,                      		0x1008ff03, spawn,          SHCMD ("xbacklight -dec 5 && xbacklight_notify")},
    { 0,                      		0x1008ff12, spawn,          SHCMD ("amixer -q -D pulse set Master toggle")},
    { 0,                      		0x1008ff11, spawn,          SHCMD ("amixer -q -D pulse set Master 3%- unmute")},
    { 0 ,                     		0x1008ff13, spawn,          SHCMD ("amixer -q -D pulse set Master 3%+ unmute")},
    { MODKEY|ControlMask,     		XK_f,       spawn,          SHCMD ("firefox-esr")},
    { MODKEY|ControlMask,    		XK_s,       spawn,          SHCMD ("spacefm")},
    { 0,                      		0xff61,     spawn,          SHCMD ("scrot -e 'mv $f ~/Pictures/screenshots/'")},
    { MODKEY,                 		0xff61,     spawn,          SHCMD ("gnome-screenshot -a")},
    { MODKEY|ControlMask,           XK_v,       spawn,          SHCMD ("vncviewer")},
    { MODKEY|ControlMask,      		XK_equal,   spawn,          SHCMD ("galculator")},
    { MODKEY|ControlMask,      		XK_l,       spawn,          SHCMD ("i3lock -i /home/rt072/Pictures/lock.jpg -c '#000000'")}, 
    { Mod1Mask,             	    XK_t,       spawn,          SHCMD ("translate_textbox")},
    { ControlMask|Mod1Mask,    	    XK_Up,      spawn,          SHCMD ("mpc volume +2")},
    { ControlMask|Mod1Mask,    	    XK_Down,    spawn,          SHCMD ("mpc volume -2")},
    { ControlMask|Mod1Mask,    	    XK_p,       spawn,          SHCMD ("mpc toggle")},
    { ControlMask|Mod1Mask,    	    XK_Left,    spawn,          SHCMD ("mpc prev")},
    { ControlMask|Mod1Mask,         XK_Right,   spawn,          SHCMD ("mpc next")},
    { ControlMask|Mod1Mask,    	    XK_u,       spawn,          SHCMD ("mpc update")},
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

