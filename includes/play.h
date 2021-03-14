#ifndef PLAY_H
# define PLAY_H
#include "map.h"

void        start_game();
levstat     start_level(WINDOW *win, int level);
void        action(WINDOW *win, t_map *map, p_move *move);
void        movePlayable(WINDOW *win, t_map *map, p_move *move);
void        check_newposition(t_map *map);

#endif