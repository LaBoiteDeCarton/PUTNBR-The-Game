#ifndef MAP_H
# define MAP_H

typedef struct s_map t_map;
typedef struct s_case t_case;
typedef enum s_casetype t_casetype;
typedef enum s_lev_stat levstat;

enum s_lev_stat
{
    ongoing,
    success,
    retry,
    fail,
    end
};

enum s_casetype
{
    player,
    collect,
    item,
    obs,
    finish,
    deadobs,
    none
};

struct s_case
{
    int positionX;
    int positionY;
    t_casetype type;
    char c;
};

struct s_map
{
    t_case  **playable; //deplacement selon status player ou collect +++ condition de transfor de collect vers player
    t_case  **item;
    t_case  **obs;
    t_case  **deadobs;
    t_case  **finish;
    levstat stat;
    int     width;
    int     height;
    char    *lname;
};

void    afficheCase(t_case **casetab, WINDOW *win);
void    afficheMap(t_map *map, WINDOW *win);
t_map   *init_map(int level);
void    freee(t_map *map);

#endif