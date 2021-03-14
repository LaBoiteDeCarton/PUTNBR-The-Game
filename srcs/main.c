#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "key_scan.h"
#include "menu.h"
#include "play.h"
#include "anim.h"
#include "color_set.h"
#include "globalvar.h"


int     main()
{
    p_move user_res;
    WINDOW *gamewindow;

    system(RESIZE_CHAR_BIG);
    system(RESIZE_CHAR_NORMAL);
    gamewindow = initscr();
    curs_set(FALSE);
    keypad(gamewindow, TRUE);
    wresize(gamewindow, W_HEIGHT, W_WIDTH);
    active_color();
    screenchange(stdscr);
    noecho();
    user_res = menu();
    if (user_res == start)
        start_game();
    goodbye(gamewindow);
    delwin(gamewindow);
    endwin();
    return(1);
}