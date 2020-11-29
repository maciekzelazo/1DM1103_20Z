#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "funkcje.h"

void wczytaj1(FILE * fin1, struct macierz *m) 

{
    int i,j;
    fscanf(fin1, "%d", &m->r);
    fscanf(fin1, "%d", &m->c);

    m->tab = (float**) malloc(sizeof(float*) * m->r);
    for (i=0;i<m->r;i++) {
        m->tab[i] = (float*) malloc(sizeof(float) * m->c);
        for (j=0;j< m->c; j++)
            m->tab[i][j] = j+1+i;
    }

    for (i=0; i < m->r; i++) 
        for (j=0; j < m->c; j++) 
            fscanf(fin1, "%f", &m->tab[i][j]);
}

void wypisz1(struct macierz m) {
    int i, j;
    printf("[ ");
    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            printf("%5.1f ", m.tab[i][j]);
        }
        if (i < (m.r-1))
            printf("\n  ");
    }
    printf("]\n");
}

void zapisz(char nazwa[], struct macierz m)
{
    FILE * fout = fopen(nazwa, "w");
    int i,j;

    fprintf(fout, "%d\n%d\n", m.r, m.c);
    for (i = 0; i < m.r; i++)
    {
        for (j=0; j < m.c; j++)
        {
            fprintf(fout, "%.1f\n", m.tab[i][j]);
        }
    }

    fclose(fout);
}

void zwolnij(struct macierz *m){
for (int i=0;i<m->r;i++) 
        free(m->tab[i]);
    free(m->tab);
    free(m);
}