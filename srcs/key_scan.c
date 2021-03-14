#include <ncurses.h>
#include "key_scan.h"

void key_scan(p_move *move)
{
    *move = undefined; //to remove
    while (*move == undefined)
    {
        flushinp();
        switch (getch())
        {
            case KEY_LEFT:
                *move = left;
                break ;
            case KEY_RIGHT:
                *move = right;
                break ;
            case KEY_UP:
                *move = up;
                break ;
            case KEY_DOWN:
                *move = down;
                break ;
            case 10:
                *move = enter;
                break ;
            case 'q':
            case 'Q':
                *move = quit;
                break ;
            case 'r':
            case 'R':
                *move = restart;
                break ;
            case 's':
            case 'S':
                *move = start;
                break ;
            default:
                *move = undefined;
        }
    }
}