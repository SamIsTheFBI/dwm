static const char norm_fg[] = "#ccc0ae";
static const char norm_bg[] = "#15140b";
static const char norm_border[] = "#8e8679";

static const char sel_fg[] = "#ccc0ae";
static const char sel_bg[] = "#E11530";
static const char sel_border[] = "#ccc0ae";

static const char urg_fg[] = "#ccc0ae";
static const char urg_bg[] = "#D4102A";
static const char urg_border[] = "#D4102A";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};
