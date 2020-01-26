#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *F;

char *adapt(char tab[])
{
    char *s = (char *)malloc(sizeof(char) * strlen(tab));
    strcpy(s, tab);
    return s;
}

int nTol(char *s, int *line, int *col)
{
    int l = strlen(s), count = 0;
    for (int i = 0; i < l; i++)
    {
        if (s[i] == '\n')
        {
            (*line)++;
            fprintf(F,"\n%d-\t", *line);
            s[i] = '\t';
            *col = 1;
        }
        else
            fprintf(F,"%c", s[i]);
    }
    return count;
}