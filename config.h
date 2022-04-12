/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = False;     /* Switch view on tag switch */
//static const char *fonts[]          = {"fontawesome:size=10:antialias=true:autohint=true","NotoSans-Regular:size=10","SourceHanSansJP-Normal:size=10", "JetBrains Mono:size=10" };    //{"JetBrains Mono:size=10", "fontawesome:size=10:antialias=true:autohint=true"};
static const char *fonts[]  =  { "JetBrainsMono Nerd Font:style:medium:size=10","Material Design Icons-Regular:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:style:medium:size=10";

#include "/home/samisthefbi/.cache/wal/colors-wal-dwm.h"
#include "layouts.c"

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", };
//static const char *tags[] = { "", "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	// For tag masks, 1 << (n-1) where n is the tag number in which you want to open the app
	
	/* class		instance		title		tags		switchtotag    isfloating	monitor */
	{ "st-256color",	"st-256color",       	NULL,  		0, 		0,           	0,           	-1 },
	{ "Chromium",  		"chromium",     	NULL,   	1 << 1,       	1,		0,           	-1 },
	{ "TelegramDesktop",  	"telegram-desktop",     NULL,   	1 << 2,       	1,		0,           	-1 },
	{ "Geany",  		"geany",     		NULL,   	1 << 3,       	1,		0,           	-1 },
	{ "PPSSPPSDL",  	"PPSSPPSDL",     	NULL,   	1 << 4,       	1,		0,		-1 },
	{ "dolphin-emu",  	"dolphin-emu",     	NULL,  		1 << 4,       	1,		0,          	-1 },
	{ "mGBA",  		"AppRun.wrapped",     	NULL, 		1 << 4,       	1,		0,		-1 },
	{ "Pcsx2",  		"pcsx2",     		NULL, 		1 << 4,       	1,		0,		-1 },
	{ "mpv",  		"gl",     		NULL,   	1 << 5,       	1,		0,           	-1 },
	{ "Pcmanfm",  		"pcmanfm",     		NULL,   	1 << 6,       	1,		0,           	-1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol		arrange function */
	{ "[Tiling]",		tile },    /* first entry is default */
	{ "[Floating]",      	NULL },    /* no layout function means floating behavior */
	{ "[Monocle]",      	monocle }, /* a single big window */
	{ "[Grid]",      	grid },
 	{ "[Dwindle]",      	dwindle },
	{ NULL,       		NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]        = { "st",                NULL };
static const char *browsercmd[]     = { "chromium",          NULL };
static const char *chatapp[]        = { "telegram-desktop",  NULL};
//static const char *processview[]    = { "htop",              NULL };


#include <X11/XF86keysym.h>

static Key keys[] = {


	/*__App_Shortcuts__*/
	/* modifier                    key		function			argument */
	{MODKEY,                       XK_p,      	spawn,                    	{.v = dmenucmd } },
	{MODKEY|ShiftMask,             XK_Return, 	spawn,                    	{.v = termcmd } },
	{MODKEY|ShiftMask,             XK_w,      	spawn,                    	{.v = browsercmd} },
	{MODKEY|ShiftMask,             XK_m,      	spawn,                    	{.v = chatapp} },
	//{MODKEY|ShiftMask,             XK_h,      	spawn,                    	{.v = processview} },


        /*__Window_Management_ig_*/
	/* modifier			key	   	function			argument */
	{ MODKEY,                       XK_b,      	togglebar,      		{0} },
	{ MODKEY,                       XK_Left,   	focusstack,     		{.i = +1 } },
	{ MODKEY,                       XK_Right,  	focusstack,     		{.i = -1 } },
	{ MODKEY,                       XK_i,      	incnmaster,     		{.i = +1 } },
	{ MODKEY,                       XK_d,      	incnmaster,     		{.i = -1 } },
	{ MODKEY,                       XK_h,      	setmfact,       		{.f = -0.05} },
	{ MODKEY,                       XK_l,      	setmfact,       		{.f = +0.05} },
	{ MODKEY,                       XK_Return, 	zoom,           		{0} },
	{ MODKEY,                       XK_Tab,    	view,           		{0} },
	{ MODKEY|ShiftMask,             XK_c,      	killclient,     		{0} },
	{ MODKEY,             		XK_f,      	togglefullscr,  		{0} },
	{ MODKEY,                       XK_t,      	setlayout,      		{.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      	setlayout,      		{.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      	setlayout,      		{.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      	setlayout,      		{.v = &layouts[3]} },
	{ MODKEY,                       XK_e,      	setlayout,      		{.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  	setlayout,      		{0} },
	{ MODKEY|ShiftMask,             XK_space,  	togglefloating, 		{0} },
	{ MODKEY,                       XK_0,      	view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      	tag,            		{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  	focusmon,       		{.i = -1 } },
	{ MODKEY,                       XK_period, 	focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 	tagmon,         		{.i = +1 } },
	{ MODKEY,             		XK_F5,	   	quit,           		{0} },
	{ ControlMask,             	XK_F5,	   	quit,           		{1} },
	{ MODKEY|ControlMask,		XK_comma,  	cyclelayout,    		{.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, 	cyclelayout,    		{.i = +1 } },

	/*__dmenu_stuff_*/
	/* modifier			key	   	function			argument */
	{ MODKEY,                       XK_x,    	spawn,            		SHCMD("sysact")},
	{ MODKEY,                       XK_m,    	spawn,            		SHCMD("watchmedia")},
	{ MODKEY,                       XK_a,    	spawn,            		SHCMD("addtonotes")},
	{ MODKEY,			XK_c,    	spawn,            		SHCMD("addtoclipboard")},

	/*__Switching_Tags__*/
	/*  				key						tag no.*/
	TAGKEYS(                        XK_1,                      			0)
	TAGKEYS(                        XK_2,                      			1)
	TAGKEYS(                        XK_3,                      			2)
	TAGKEYS(                        XK_4,                      			3)
	TAGKEYS(                        XK_5,                      			4)
	TAGKEYS(                        XK_6,                      			5)
	TAGKEYS(                        XK_7,                      			6)
	TAGKEYS(                        XK_8,                      			7)
	TAGKEYS(                        XK_9,                      			8)


	/*__Xf86/Multimedia_Keys_(mostly)__*/
	/* modifier, 		key,				function,	argument */
	{ 0, 			XF86XK_AudioMute,   		spawn,       	SHCMD("volume tmute")},
	{ 0, 			XF86XK_AudioRaiseVolume, 	spawn,  	SHCMD("volume incr")},
	{ 0, 			XF86XK_AudioLowerVolume, 	spawn,		SHCMD("volume decr")},
	{ 0, 			XF86XK_MonBrightnessUp,  	spawn,  	SHCMD("shine incr")},
	{ 0, 			XF86XK_MonBrightnessDown, 	spawn, 		SHCMD("shine decr")},
	{ 0, 			XK_Print, 			spawn, 		SHCMD("screencap")},
	{ MODKEY, 		XK_Print, 			spawn, 		SHCMD("screencap fullsave")},
	{ ShiftMask, 		XK_Print, 			spawn,		SHCMD("screencap selectcopy")},
	{ MODKEY|ShiftMask, 	XK_Print, 			spawn,		SHCMD("screencap selectsave")},
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

