#include <ncurses.h>
#include "color_set.h"

void    active_color()
{
    start_color();
    use_default_colors();
    init_pair(C_PLAYER, COLOR_GREEN, -1);
    init_pair(C_OBS, COLOR_WHITE, -1);
    init_pair(C_DEAD_OBS, COLOR_RED, -1);
    init_pair(C_ITEM, COLOR_RED, COLOR_MAGENTA);
    init_pair(C_FINISH, COLOR_GREEN, COLOR_GREEN);
    init_pair(C_DEFAULT, -1, -1);
    init_pair(C_SELECT, COLOR_BLACK, COLOR_WHITE);
    init_pair(C_COLLECT, COLOR_YELLOW, -1);
}