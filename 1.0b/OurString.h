#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *adapt(char tab[])
{
    int l = strlen(tab);
    char *s = (char *)malloc(sizeof(char) * l);
    strcpy(s, tab);
    return s;
}

int nTol(char *s, int *line, int *col)
{
    int l = strlen(s), count = 0;
    printf("\033[0;32m");
    for (int i = 0; i < l; i++)
    {
        if (s[i] == '\n')
        {
            printf("\033[0;37m\n%d-\033[0;32m\t", *line);
            (*line)++;
            s[i] = '\t';
            *col = 1;
        }
        else
            printf("%c", s[i]);
    }
    printf("\033[0;37m");
    return count;
}