/* appearance */
static const unsigned int borderpx		= 2;        /* border pixel of windows */
static const Gap default_gap			= {.isgap = 1, .realgap = 5, .gappx = 0};   /* gappx sets the default gap width*/
static const unsigned int snap      	= 2;       /* snap pixel */
static const unsigned int gappih		= 5;       /* horiz inner gap between windows */
static const unsigned int gappiv		= 4;       /* vert inner gap between windows */
static const unsigned int gappoh		= 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov		= 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps				= 0;        /* 1 means no outer gap when there is only one window */
static const int showbar				= 1;        /* 0 means no bar */
static const int topbar					= 1;        /* 0 means bottom bar */
static const Bool viewontag				= False;     /* Switch view on tag switch */
static const char *fonts[]				=  { "JetBrainsMono Nerd Font:style:medium:size=10","Noto Sans Mono CJK JP:style=SemiBold:size=10" };
static const char dmenufont[]			= "JetBrainsMono Nerd Font:style:medium:size=10";
static const unsigned int baralpha		= 0xdf;
static const unsigned int borderalpha	= OPAQUE;
static const unsigned int ulinepad		= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 				= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

#include "colors-wal-dwm.h"

static const unsigned int alphas[][3]      = {
		/*               fg      bg        border     */
		[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
		[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", };
//static const char *tags[] = { "", "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	// For tag masks, 1 << (n-1) where n is the tag number in which you want to open the app
	
	/* class				instance				title			tags		switchtotag	isfloating		monitor */
	{ "st-256color",		"st-256color",   		NULL,  			0,				0,          0,           	-1 },
	{ "copyq",				"copyq",   				NULL,  			0,				0,          1,           	-1 },
	{ "Chromium",  			"chromium",				NULL,   		1 << 1,			1,			0,           	-1 },
	{ "TelegramDesktop",	"telegram-desktop", 	NULL,   		1 << 2,			1,			0,           	-1 },
	{ "Geany",  			"geany",     			NULL,   		1 << 3,			1,			0,           	-1 },
	{ "PPSSPPSDL",  		"PPSSPPSDL",     		NULL,   		1 << 4,			1,			1,				-1 },   //PPSSPP AppImage
	{ "dolphin-emu",  		"dolphin-emu",     		NULL,  			1 << 4,			1,			0,          	-1 },		// pacman
	{ "mGBA",  				"AppRun.wrapped",   	NULL, 			1 << 4,			1,			0,				-1 },   //mGBA AppImage
	{ "Pcsx2",  			"pcsx2",     			NULL, 			1 << 4,			1,			0,				-1 },
	{ "mpv",  				"gl",     				NULL,   		1 << 5,			1,			0,           	-1 },
	{ "Pcmanfm",  			"pcmanfm",     			NULL,   		1 << 6,			1,			0,           	-1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1   /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol				arrange function */
	{ "[]=",					tile },    /* first entry is default */
	{ "[Monocle]",   			monocle }, /* a single big window */	
	{ "[@]",					spiral },
	{ "[\\]",					dwindle },
	{ "H[]",					deck },
	{ "TTT",					bstack },
	{ "===",					bstackhoriz },
	{ "HHH",					grid },
	{ "###",					nrowgrid },
	{ "---",					horizgrid },
	{ ":::",					gaplessgrid },
	{ "|M|",					centeredmaster },
	{ ">M>",					centeredfloatingmaster },
	{ "><>",					NULL },    /* no layout function means floating behavior */
	{ NULL,						NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 			=	{ "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]        = { "st",                NULL };
static const char *browsercmd[]     = { "chromium",          NULL };
static const char *chatapp[]        = { "telegram-desktop",  NULL };
static const char *txteditor[]	    = { "geany",             NULL };
static const char *fileman[]	    	= { "thunar", 	     		 NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {


	/*__App_Shortcuts__*/
	/* modifier								key					function			argument */
	{MODKEY,                 XK_p,      	spawn,      {.v = dmenucmd } },
	{MODKEY|ShiftMask,       XK_Return, 	spawn,      {.v = termcmd } },
	{MODKEY|ShiftMask,       XK_w,      	spawn,      {.v = browsercmd} },
	{MODKEY|ShiftMask,       XK_m,      	spawn,      {.v = chatapp} },
	{MODKEY|ShiftMask,       XK_h,      	spawn,      SHCMD("st htop") },
	{MODKEY|ShiftMask,       XK_e,      	spawn,      {.v = txteditor} },
	{MODKEY,             	   XK_e,      	spawn,      {.v = fileman} },


        /*__Window_Management_ig_*/
	/* modifier							key	   					function					argument */
	{ MODKEY,               XK_b,      			togglebar,      		{0} },
	{ MODKEY,               XK_Left,   			focusstack,     		{.i = +1 } },
	{ MODKEY,               XK_Right,  			focusstack,     		{.i = -1 } },
	{ MODKEY,               XK_bracketleft, incnmaster,     		{.i = +1 } },
	{ MODKEY,               XK_bracketright,incnmaster,     		{.i = -1 } },
	{ MODKEY,               XK_comma,      	setmfact,       		{.f = -0.05} },
	{ MODKEY,               XK_period,      setmfact,       		{.f = +0.05} },
	{ MODKEY,               XK_Return,			zoom,           		{0} },
	{ MODKEY,               XK_Tab,					view,           		{0} },
	{ MODKEY|ShiftMask,     XK_c,						killclient,     		{0} },
	{ MODKEY,             	XK_f,						togglefullscr,  		{0} },
	{ MODKEY,               XK_t,						setlayout,      		{.v = &layouts[0]} },  //Tiling
	{ MODKEY,               XK_y,						setlayout,      		{.v = &layouts[1]} },  //Monocle
	{ MODKEY,               XK_u,						setlayout,      		{.v = &layouts[2]} },  //Spiral
	{ MODKEY,               XK_i,						setlayout,      		{.v = &layouts[3]} },  //Dwindle
	{ MODKEY,               XK_o,						setlayout,      		{.v = &layouts[4]} },  //Deck
	{ MODKEY,               XK_space,				setlayout,      		{0} },
	{ MODKEY|ShiftMask,     XK_space,				togglefloating, 		{0} },
	{ MODKEY,               XK_0,						view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,						tag,            		{.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_comma,				focusmon,       		{.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,				focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,				tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,				tagmon,         		{.i = +1 } },
	{ MODKEY|ControlMask,	XK_Right,				viewnext,				{0} },
	{ MODKEY|ControlMask,	XK_Left,				viewprev,				{0} },
	{ MODKEY|ShiftMask,		XK_Right,				tagtonext,				{0} },
	{ MODKEY|ShiftMask,		XK_Left,				tagtoprev,				{0} },
	{ MODKEY,               XK_minus,				incrgaps,        		{.i = -5 } },	
	{ MODKEY|ALTKEY,        XK_minus,				incrigaps,        	{.i = -5 } },
	{ MODKEY,               XK_equal,				incrgaps,        		{.i = +5 } },	
	{ MODKEY|ALTKEY,        XK_equal,				incrigaps,        	{.i = +5 } },
	{ MODKEY|ShiftMask,     XK_minus,				togglegaps,     		{0} },
	{ MODKEY|ShiftMask,     XK_equal,				defaultgaps,    		{0} },
	{ MODKEY,             	XK_F5,					quit,           		{0} },
	{ ControlMask,         	XK_F5,					quit,           		{1} },
	{ MODKEY|ControlMask,		XK_comma,				cyclelayout,    		{.i = -1 } },
	{ MODKEY|ControlMask,   XK_period,			cyclelayout,    		{.i = +1 } },
	{ ALTKEY, 							XK_Tab,					spawn,							SHCMD("rofi -show window")},
	{ MODKEY|ALTKEY,        XK_Left,				spawn,        	SHCMD("xrandr --output eDP --rotate left") },
	{ MODKEY|ALTKEY,        XK_Right,				spawn,        	SHCMD("xrandr --output eDP --rotate right") },
	{ MODKEY|ALTKEY,        XK_Up,					spawn,        	SHCMD("xrandr --output eDP --rotate normal") },
	{ MODKEY|ALTKEY,        XK_Down,				spawn,        	SHCMD("xrandr --output eDP --rotate inverted") },

	/*__dmenu_stuff_*/
	/* modifier			key	   	function			argument */
	{ MODKEY,      XK_x,    	spawn,      SHCMD("sysact")},
	{ MODKEY,      XK_m,    	spawn,      SHCMD("watchmedia")},
	{ MODKEY,			 XK_a,    	spawn,      SHCMD("rofi -show drun -show-icons -theme ~/.config/rofi/applauncher.rasi")},
	{ MODKEY,			 XK_s,    	spawn,      SHCMD("playt-beta")},
	{ MODKEY,			 XK_c,    	spawn,      SHCMD("colpick")},

	/*__Switching_Tags__*/
	/*														tag no.*/
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
	/* modifier,		key,			function,	argument */
	{ 0, 				XF86XK_AudioMute,   		spawn,		SHCMD("volume tmute")},
	{ 0, 				XF86XK_AudioRaiseVolume, 	spawn,		SHCMD("volume incr")},
	{ 0, 				XF86XK_AudioLowerVolume, 	spawn,		SHCMD("volume decr")},
	{ 0, 				XF86XK_MonBrightnessUp,  	spawn,		SHCMD("shine incr")},
	{ 0, 				XF86XK_MonBrightnessDown, 	spawn,		SHCMD("shine decr")},
	{ 0, 				XK_Print, 					spawn,		SHCMD("screencap")},
	{ MODKEY, 			XK_Print, 					spawn,		SHCMD("screencap fullsave")},
	{ ShiftMask, 		XK_Print, 					spawn,		SHCMD("screencap selectcopy")},
	{ MODKEY|ShiftMask, XK_Print, 					spawn,		SHCMD("screencap selectsave")},
	{ 0,				XF86XK_AudioNext,			spawn,		SHCMD("mpc next")},
	{ 0,				XF86XK_AudioPrev,			spawn,		SHCMD("mpc prev")},	
	{ 0,				XF86XK_AudioPlay,			spawn,		SHCMD("mpc toggle")},
	{ MODKEY, 			XK_z, 						spawn,		SHCMD("touchpadtap")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
//{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY|ShiftMask,Button1,        dragmfact,    	{0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

