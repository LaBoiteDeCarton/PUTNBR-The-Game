#ifndef GLOBALVAR_H
# define GLOBALVAR_H

#define W_HEIGHT 21
#define W_WIDTH 41
#define WINF_HEIGHT (W_HEIGHT - 14) // == 7
#define WINF_WIDTH W_WIDTH - 1 // == 40
#define MIDDLE_PG_X (W_WIDTH / 2) // == 20
#define MIDDLE_PG_Y ((W_HEIGHT - WINF_HEIGHT) / 2) - 1 // == 7
#define RESIZE_CHAR_BIG "printf '\e[8;30;80t'"
#define RESIZE_CHAR_NORMAL "printf '\e[8;20;40t'"

#endif