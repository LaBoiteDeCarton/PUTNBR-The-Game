#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "file.h"
#include "color_set.h"
#include "ft_str.h"

#include <unistd.h>
#include "wait.h"

void        add_case_to_casetab(t_case **casetab, t_case *new_case)
{
    int i;

    i = 0;
    while (casetab[i] != NULL)
        i++;
    casetab[i] = new_case;
    casetab[i + 1] = NULL;
}

void        add_case_to_map(t_map *map, t_case *new_case)
{
    if (new_case->type == player)
        add_case_to_casetab(map->playable, new_case);
    else if (new_case->type == collect)
        add_case_to_casetab(map->playable, new_case);
    else if (new_case->type == obs)
        add_case_to_casetab(map->obs, new_case);
    else if (new_case->type == deadobs)
        add_case_to_casetab(map->deadobs, new_case);
    else if (new_case->type == finish)
        add_case_to_casetab(map->finish, new_case);
}

t_case      *create_case(int y, int x, t_casetype currtype, char l)
{
    t_case *newcase;

    while (!(newcase = (t_case *)malloc(sizeof(t_case))))
        ;
    newcase->positionX = x;
    newcase->positionY = y;
    newcase->type = currtype;
    newcase->c = l;
    return (newcase);
}

void    creat_map_from_content(t_map *newmap, char *content)
{
    int         taille;
    int         i;
    int         x;
    int         y;
    char        l;
    t_casetype  currtype;
    int         winx;
    int         winy;
    char        *name;

    i = 0;
    name = fetch_line(content, &i);
    i += 1;
    newmap->lname = name;
    winy = my_atoi(content, &i);
    i += 1;
    winx = my_atoi(content, &i);
    i += 1;
    newmap->width = winx;
    newmap->height = winy;
    while (content[i] != '\n')
    {
        taille = my_atoi(content, &i);
        if (content[i] == 'p')
        {
            while (!(newmap->playable = (t_case **)malloc(sizeof(t_case *) * (taille + 1))))
                ;
        }
        else if (content[i] == 'o')
        {
            while (!(newmap->obs = (t_case **)malloc(sizeof(t_case *) * (taille + 1))))
                ;
        }   
        else if (content[i] == 'd')
        {
            while (!(newmap->deadobs = (t_case **)malloc(sizeof(t_case *) * (taille + 1))))
                ;
        }
        else if (content[i] == 'i')
        {
            while (!(newmap->item = (t_case **)malloc(sizeof(t_case *) * (taille + 1))))
                ;
        }
        else if (content[i] == 'f')
        {
            while (!(newmap->finish = (t_case **)malloc(sizeof(t_case *) * (taille + 1))))
                ;
        }
        i += 2;
    }
    newmap->playable[0] = NULL;
    newmap->obs[0] = NULL;
    newmap->deadobs[0] = NULL;
    newmap->item[0] = NULL;
    newmap->finish[0] = NULL;
    i += 1;
    while (content[i] && content[i] != '\n')
    {
        y = my_atoi(content, &i);
        i += 1;
        x = my_atoi(content, &i);
        i += 1;
        if (content[i] == 'p')
            currtype = player;
        else if (content[i] == 'c')
            currtype = collect;
        else if (content[i] == 'o')
            currtype = obs;
        else if (content[i] == 'd')
            currtype = deadobs;
        else if (content[i] == 'f')
            currtype = finish;
        else if (content[i] == 'i')
            currtype = item;
        while (content[i] != ':')
            i += 1;
        i += 1;
        l = content[i];
        add_case_to_map(newmap, create_case(y, x, currtype, l));
        i += 2;
    }
}

t_map   *init_map(int level)
{
    t_map   *newmap;
    char    *filename;
    char    *content;

    if ((newmap = (t_map *)malloc(sizeof(t_map))))
    {
        filename = create_fn(level);
        content = read_file(filename);
        newmap->stat = ongoing;
        creat_map_from_content(newmap, content);
        free(filename);
    }
    else
        newmap = NULL;
    return (newmap);
}

void    afficheCase(t_case **casetab, WINDOW *win)
{
    int i;

    i = 0;
    while (casetab[i] != NULL)
    {
        if (casetab[i]->type == collect) //un peu nul mais pas trouvé d'autres façon de faire
        {
            wattron(win, COLOR_PAIR(C_COLLECT));
            mvwaddch(win, casetab[i]->positionY, casetab[i]->positionX, casetab[i]->c);
            wattroff(win, COLOR_PAIR(C_COLLECT));
        }
        else if (casetab[i]->type == player)
        {
            wattron(win, COLOR_PAIR(C_PLAYER));
            mvwaddch(win, casetab[i]->positionY, casetab[i]->positionX, casetab[i]->c);
            wattroff(win, COLOR_PAIR(C_PLAYER));
        }
        else
            mvwaddch(win, casetab[i]->positionY, casetab[i]->positionX, casetab[i]->c);
        i++;
    }
}

void    afficheMap(t_map *map, WINDOW *win)
{
    wclear(win);
    wborder(win, '#', '#', '#', '#', '#', '#', '#', '#');
    afficheCase(map->playable, win);
    wattron(win, COLOR_PAIR(C_ITEM));
    afficheCase(map->item, win);
    wattroff(win, COLOR_PAIR(C_ITEM));
    wattron(win, COLOR_PAIR(C_OBS));
    afficheCase(map->obs, win);
    wattroff(win, COLOR_PAIR(C_OBS));
    wattron(win, COLOR_PAIR(C_DEAD_OBS));
    afficheCase(map->deadobs, win);
    wattroff(win, COLOR_PAIR(C_DEAD_OBS));
    wattron(win, COLOR_PAIR(C_FINISH));
    afficheCase(map->finish, win);
    wattroff(win, COLOR_PAIR(C_FINISH));
    wrefresh(win);
}

void    freee_casetab(t_case **casetab)
{
    int i;
    
    i = -1;
    while (casetab[++i] != NULL)
        free(casetab[i]);
    free(casetab);
}

void    freee(t_map *map)
{
    freee_casetab(map->playable);
    freee_casetab(map->obs);
    freee_casetab(map->finish);
    freee_casetab(map->deadobs);
    freee_casetab(map->item);
    free(map->lname);
    free(map);
}