static const char norm_fg[] = "#EADAB1";
static const char norm_bg[] = "#322119";
static const char norm_border[] = "#788997";

static const char sel_fg[] = "#EADAB1";
static const char sel_bg[] = "#8F7056";
static const char sel_border[] = "#EADAB1";

static const char urg_fg[] = "#EADAB1";
static const char urg_bg[] = "#C3763A";
static const char urg_border[] = "#C3763A";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};
