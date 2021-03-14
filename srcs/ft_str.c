#include "ft_str.h"
#include <stdlib.h>

int     my_atoi(char *content, int *i)
{
    int res;
    res = 0;

    while (content[*i] <= '9' && content[*i] >= '0')
    {
        res = res * 10 + (content[*i] - '0');
        *i += 1;
    }
    return (res);
}

char    *fetch_line(char *content, int *i)
{
    int     taille;
    int     j;
    char    *fst_line;
    
    taille = 0;
    while (content[*i + taille] != '\n')
        taille++;
    if ((fst_line = (char *)malloc(sizeof(char) * (taille + 1))))
    {
        j = 0;
        while (j < taille)
        {
            fst_line[j] = content[*i];
            j++;
            *i += 1;
        }
        fst_line[j] = '\0';
    }
    else
        fst_line = NULL;
    return (fst_line);
}