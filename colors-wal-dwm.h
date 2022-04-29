static const char norm_fg[] = "#c4c0c1";
static const char norm_bg[] = "#091019";
static const char norm_border[] = "#898687";

static const char sel_fg[] = "#c4c0c1";
static const char sel_bg[] = "#73798E";
static const char sel_border[] = "#c4c0c1";

static const char urg_fg[] = "#c4c0c1";
static const char urg_bg[] = "#226CA2";
static const char urg_border[] = "#226CA2";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};
