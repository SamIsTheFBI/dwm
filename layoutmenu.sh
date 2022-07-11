#!/bin/sh

# cat <<EOF | dmenu -l 15 | awk '{print $NF}'
# []= Tiled Layout                    0
# [M] Monocle Layout                  1
# [@] Spiral Layout                   2
# [\] Dwindle Layout                  3
# H[] Deck Layout                     4
# TTT Bstack Layout                   5
# === Bstack Horix Layout             6
# HHH Grid Layout                     7
# ### nrow Grid Layout                8
# --- Horiz Grid Layout               9
# ::: Gapless Grid Layout             10
# |M| Centered Master Layout          11
# >M> Centered Floating Master Layout 12
# ><> Floating Layout                 13
# EOF

cat ~/.local/src/dwm/layouts.csv | jgmenu --simple --config-file=~/.config/jgmenu/jgmenu_layoutmenu
