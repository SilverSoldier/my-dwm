/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 0,       False,       -1 },
	{ "Konqueror",  NULL,       NULL,       1 << 0,       False,       -1 },
	{ "Gnome-panel",  NULL,       NULL,       1 << 0,       True,       -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
/* False to take care of "empty space around terminals" problem */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

// misc
static const char *ffcmd[]  = { "firefox", NULL };
static const char *utermcmd[]  = { "urxvt", NULL };

// gnome specific commands
static const char *termcmd[]  = { "gnome-terminal", NULL };
static const char *gpcmd[]  = { "gnome-panel", NULL };

// dwm specific tools
//xterm with tabbed (from suckless)
static const char *termcmd2[]  = { "tabbed", "-c", "xterm", "-into", NULL };
//custom sleep
static const char *sleepcmd[]  = { "dwm-sleep.sh", NULL };

// on moving to KDE
static const char *krcmd[]  = { "konqueror", NULL };
static const char *ktermcmd[]  = { "konsole", NULL };

// for XFCE4 based items
static const char *xfcetermcmd[]  = { "xfce4-terminal", NULL };

/* alsa sound */
static const char channel[]   = "Master";

/* battery */
static const char batterypath[] = "/sys/class/power_supply/";
static const char batterynow[]  = "energy_now";
static const char batteryfull[] = "energy_full_design";

/* bar update interval in seconds (smallest value = 1) */
static unsigned int update_interval = 1;
// not working : abandoned for now
//static const char *nmappletcmd[]  = { "nm-applet", NULL };

// note that konsole and gnome-terminal are mapped to the same key
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	//misc
        { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = ffcmd } },
        { MODKEY|ShiftMask,             XK_u,      spawn,          {.v = utermcmd } },
	//gnome specific
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_g,      spawn,          {.v = gpcmd } },
	//dwm specific
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = termcmd2 } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = sleepcmd } },
	//kde specific
        //{ MODKEY|ShiftMask,             XK_k,      spawn,          {.v = krcmd } },
	//{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = ktermcmd } },
	//xfce4 specific
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = xfcetermcmd } },
	//others
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
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
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

static const struct arg args[] = {
    /* function     format          argument */
    { wifi_perc,    "wifi %4s | ",  "wlp3s0" },
    { battery_perc, "bat %4s | ",   "BAT0" },
    { cpu_perc,     "cpu %4s ",     NULL },
    { temp,         "%3s | ",       "/sys/devices/platform/coretemp.0/hwmon/hwmon2/temp1_input" },
    { ram_perc,     "ram %3s | ",   NULL },
    { vol_perc,     "vol %4s | ",   "default" },
    { disk_perc,    "ssd %3s | ",   "/" },
    { datetime,     "%s",           "%y-%m-%d %H:%M:%S" },
};
