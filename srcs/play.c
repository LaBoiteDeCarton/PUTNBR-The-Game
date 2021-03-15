#include <ncurses.h>
#include <stdlib.h>
#include "key_scan.h"
#include "globalvar.h"
#include "anim.h"
#include "play.h"
#include "map.h"
#include "wait.h"
#include "color_set.h"

#include <stdio.h>

void    start_game()
{
    int i;
    WINDOW *levelinfo;
    levstat how_lend;

    i = 1;
    screenchange(stdscr);
    levelinfo = newwin(WINF_HEIGHT, WINF_WIDTH, W_HEIGHT - WINF_HEIGHT - 1, 0);
    box(levelinfo, 0, 0);
    mvwprintw(levelinfo, 0, 2, "INFO");
    mvwprintw(levelinfo, 2, 2, "Level %d:", i);
    mvwprintw(levelinfo, 3, 2, "R to restart");
    mvwprintw(levelinfo, 4, 2, "Q to quit");
    while (i < 18)
    {
        mvwprintw(levelinfo, 2, 2, "Level %d:", i);
        how_lend = start_level(levelinfo, i);
        if (how_lend == end)
            break ;
        if (i != 17 && how_lend == success)
            bravo(stdscr);
        if (i != 17 && how_lend != retry && how_lend != fail)
            i++;
        if (i == 17 && how_lend != retry && how_lend != success)
            i++;
    }
    delwin(levelinfo);
}

levstat    start_level(WINDOW *levelinfo, int level)
{
    t_map   *map;
    p_move  move;
    WINDOW  *levelpg;
    levstat res;

    (void)levelinfo;
    map = init_map(level);
    if (map != NULL)
    {  
        levelpg = newwin(map->height, map->width, (MIDDLE_PG_Y) - map->height / 2, (MIDDLE_PG_X) - map->width / 2);
        mvwprintw(levelinfo, 2, 11, "                            ");
        mvwprintw(levelinfo, 2, 11, map->lname);
        wrefresh(levelinfo);
        while(map->stat == ongoing)
        {
            afficheMap(map, levelpg);
            key_scan(&move);
            action(levelpg, map, &move);
        }
        afficheMap(map, levelpg);
        spirale(levelpg, " ");
        delwin(levelpg);
        res = map->stat;
        freee(map);
        return (res);
    }
    return (retry);
}

int     is_next_to_player(t_case **casetab, t_case *currcase)
{
    int i;

    i = 0;
    while (casetab[i])
    {   if (casetab[i]->type == player)
        {
            if (casetab[i]->positionX == currcase->positionX + 1 
                    && casetab[i]->positionY == currcase->positionY)
                return (1);
            if (casetab[i]->positionX == currcase->positionX - 1
                    && casetab[i]->positionY == currcase->positionY)
                return (1);
            if (casetab[i]->positionX == currcase->positionX 
                    && casetab[i]->positionY == currcase->positionY + 1)
                return (1);
            if (casetab[i]->positionX == currcase->positionX 
                    && casetab[i]->positionY == currcase->positionY - 1)
                return (1);
        }
        i++;
    }
    return (0);
}

int     is_valide_move(WINDOW *win, t_case **casetab, t_case *player, p_move *move)
{
    int i;
    int newx;
    int newy;
    int maxx;
    int maxy;
    
    i = 0;
    newy = player->positionY + 1 * (*move == down) - 1 * (*move == up);
    newx = player->positionX + 1 * (*move == right) - 1 * (*move == left);
    getmaxyx(win, maxy, maxx);
    if (newx == 0 || newx == maxx - 1 || newy == 0 || newy == maxy - 1)
        return (0);
    while (casetab[i])
    {
        if (newx == casetab[i]->positionX && newy == casetab[i]->positionY)
            return (0);
        i++;
    }
    return (1);
}

int     on_casetab(t_case **casetab, t_case *currcase)
{
    int i;

    i = 0;
    while (casetab[i])
    {
        if (currcase->positionX == casetab[i]->positionX
                && currcase->positionY == casetab[i]->positionY)
            return (1);
        i++;
    }
    return (0);
}

int     is_in_order(t_case **casetab)
{
    int i;

    i = 0;
    while (casetab[i + 1])
    {
        if (casetab[i]->positionX == casetab[i + 1]->positionX + 1 
                && casetab[i]->positionY == casetab[i + 1]->positionY)
            ;
        else if (casetab[i]->positionX == casetab[i + 1]->positionX - 1
                && casetab[i]->positionY == casetab[i + 1]->positionY)
            ;
        else if (casetab[i]->positionX == casetab[i + 1]->positionX 
                && casetab[i]->positionY == casetab[i + 1]->positionY + 1)
            ;
        else if (casetab[i]->positionX == casetab[i + 1]->positionX 
                && casetab[i]->positionY == casetab[i + 1]->positionY - 1)
            ;
        else
            return (0);
        i++;
    }
    return (1);
}

void    movePlayable(WINDOW *win, t_map *map, p_move *move)
{
    int i;
    int valide_move;

    i = 0;
    valide_move = 1;
    while (map->playable[i] && valide_move)
    {
        if (map->playable[i]->type == player)
            valide_move = is_valide_move(win, map->obs, map->playable[i], move);
        i++;
    }
    i = 0;
    while (map->playable[i] && valide_move)
    {
        if (map->playable[i]->type == player)
        {
            map->playable[i]->positionY += 1 * (*move == down) - 1 * (*move == up);
            map->playable[i]->positionX += 1 * (*move == right) - 1 * (*move == left);
        }
        i++;
    }
    if (!valide_move)
        beep();
}

void    action(WINDOW *win, t_map *map, p_move *move)
{
    if (*move == quit)
        map->stat = end;
    else if (*move == restart)
        map->stat = retry;
    else
    {
        movePlayable(win, map, move);
        check_newposition(map);
    }
}

void    check_newposition(t_map *map)
{
    int i;
    int changed_type;

    i = 0;
    map->stat = success;
    while (map->playable[i] && map->stat != fail)
    {
        changed_type = 0;
        if (map->playable[i]->type == collect && is_next_to_player(map->playable, map->playable[i]))
        {
            map->playable[i]->type =  player;
            changed_type = 1;
        }
        if (map->playable[i]->type == collect)
            map->stat = ongoing;
        else
            map->stat = on_casetab(map->finish, map->playable[i]) && map->stat == success ? success : ongoing;
        if (map->playable[i]->type == player)
        {
            map->stat = on_casetab(map->deadobs, map->playable[i]) ? fail : map->stat;
            if (map->stat == fail)
            {
                beep();
                flash();
            }
        }
        if (changed_type)
            i = -1;
        i++;
    }
    if (map->stat == success)
        map->stat = is_in_order(map->playable) ? success : ongoing;
}