#ifndef KEY_SCAN_H
# define KEY_SCAN_H


typedef enum
{
    left,
    up,
    right,
    down,
    quit,
    restart,
    start,
    enter,
    undefined
} p_move;

void key_scan(p_move *move);

#endif