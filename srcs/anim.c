#include <ncurses.h>
#include "anim.h"
#include "wait.h"

void goodbye(WINDOW *win)
{
    int x;
    int y;

    getmaxyx(win, y, x);
    y /= 2;
    x = x / 2 - 4;
    screenchange(win);
    mvaddch(y, x, 'G');
    refresh();
    my_wait(40);
    mvaddch(y, x + 1, 'O');
    refresh();
    my_wait(40);
    mvaddch(y, x + 2, 'O');
    refresh();
    my_wait(40);
    mvaddch(y, x + 3, 'D');
    refresh();
    my_wait(40);
    mvaddch(y, x + 6, 'B');
    refresh();
    my_wait(40);
    mvaddch(y, x + 7, 'Y');
    refresh();
    my_wait(40);
    mvaddch(y, x + 8, 'E');
    refresh();
    my_wait(40);
    mvaddch(y, x + 9, '!');
    refresh();
    my_wait(400);
    screenchange(win);
}

void    bravo(WINDOW *win)
{
    (void)win;
}

void screenchange(WINDOW *win)
{
    spirale(win, "#");
    spirale(win, " ");
}

void    spirale(WINDOW *win, char *c)
{
    int i;
    int j;
    int is_right;
    int curr_pos_x;
    int curr_pos_y;
    int max_x;
    int max_y;

    i = 0;
    j = 0;
    is_right = 0;
    getmaxyx(win, max_y, max_x);
    curr_pos_x = max_x / 2;
    curr_pos_y = max_y / 2;
    mvwprintw(win, curr_pos_y, curr_pos_x, c);
    wrefresh(win);
    while (i <= max_x)
    {
        j = 0;
        while (j < i)
        {
            if (is_right)
                curr_pos_x++;
            else
                curr_pos_x--;
            if (curr_pos_y >= 0 && curr_pos_y < max_y && curr_pos_x >= 0 && curr_pos_x < max_x)
                mvwprintw(win, curr_pos_y, curr_pos_x, c);
            j++;
        }
        wrefresh(win);
        my_wait(3);
        j = 0;
        while (j < i)
        {
            if (is_right)
                curr_pos_y--;
            else
                curr_pos_y++;
            if (curr_pos_y >= 0 && curr_pos_y < max_y && curr_pos_x >= 0 && curr_pos_x < max_x)
                mvwprintw(win, curr_pos_y, curr_pos_x, c);
            j++;
        }
        wrefresh(win);
        my_wait(3);
        i++;
        is_right = !is_right;
    }
}