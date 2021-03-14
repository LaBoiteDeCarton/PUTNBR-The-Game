#include <ncurses.h>
#include "key_scan.h"
#include "menu.h"
#include "anim.h"
#include "globalvar.h"
#include "color_set.h"

p_move menu()
{
    p_move user_res;
    p_move user_keyscan;
    int y;
    int x;
    int menu_h;
    int menu_w;
    WINDOW *wmenu;
    WINDOW *wstart;
    WINDOW *wquit;

    menu_h = 10;
    menu_w = 15;
    getmaxyx(stdscr, y, x);
    y = y / 2 - menu_h / 2;
    x = x / 2 - menu_w / 2;
    wmenu = subwin(stdscr, menu_h, menu_w, y, x);
    keypad(wmenu, TRUE);
    box(wmenu, 0, 0);
    mvwprintw(wmenu, 0, 2, "MENU");
    wstart = subwin(wmenu, 1, menu_w - 6, y + 3, x + 3);
    mvwprintw(wstart, 0, 2, "START");
    wquit = subwin(wmenu, 1, menu_w - 6, y + 6, x + 3);
    mvwprintw(wquit, 0, 2, "QUIT");
    wbkgd(wstart, COLOR_PAIR(C_SELECT));
    wbkgd(wquit, COLOR_PAIR(C_DEFAULT));
    wrefresh(wmenu);
    user_res = start;
    while (1)
    {
        key_scan(&user_keyscan);
        if (user_keyscan == enter)
            break ;
        else if (user_keyscan == down)
        {
            wbkgd(wstart, COLOR_PAIR(C_DEFAULT));
            wbkgd(wquit, COLOR_PAIR(C_SELECT));
            user_res = quit;
            wrefresh(wstart);
            wrefresh(wquit);
        }
        else if (user_keyscan == up)
        {
            wbkgd(wstart, COLOR_PAIR(C_SELECT));
            wbkgd(wquit, COLOR_PAIR(C_DEFAULT));
            user_res = start;
            wrefresh(wstart);
            wrefresh(wquit);
        }
    }
    delwin(wstart);
    delwin(wquit);
    delwin(wmenu);
    return (user_res);
}