#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Macierz {
    int r;
    int c;
    float tab[200][200];
};

void wczytaj(FILE * fin, struct Macierz *m) {
    int i,j;
    // fscanf(fin, "%d", &(*m).r);
    // fscanf(fin, "%d", &(*m).c);
    fscanf(fin, "%d", &m->r);
    fscanf(fin, "%d", &m->c);

    for (i=0; i < m->r; i++) {
        for (j=0; j < m->c; j++) {
            fscanf(fin, "%f", &m->tab[i][j]);
        }
    }
}

void wypisz(struct Macierz m) {
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

float norm(struct Macierz m) {
    float s = 0;
    int i,j;

    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            s += m.tab[i][j] * m.tab[i][j];
        }
    }
    return sqrt(s);
}

float suma(struct Macierz m) {
    float s = 0;
    int i,j;

    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            s += m.tab[i][j];
        }
    }
    return s;
}

void zapisz(char nazwa[], struct Macierz m) {
    FILE * fout = fopen(nazwa, "w");
    int i,j;

    fprintf(fout, "%d\n%d\n", m.r, m.c);
    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            fprintf(fout, "%f\n", m.tab[i][j]);
        }
    }

    fclose(fout);
}

// wczytaj plik repezentujacy dwuwymiarowa macierz
// r
// c
// liczby....
int main(int argc, char *argv[]) {
    struct Macierz mac;
    FILE * fin;
    // = fopen(argv[1], "r");

    if ( strcmp( argv[1], "norm") == 0) {
        fin  = fopen(argv[2], "r");
        wczytaj(fin, &mac);
        wypisz(mac);
        printf("Norma macierzy %s = %f\n", argv[1], norm(mac));
        fclose(fin);
    } else if ( strcmp( argv[1], "suma") == 0) {
        fin  = fopen(argv[2], "r");
        wczytaj(fin, &mac);
        wypisz(mac);
        printf("Suma elementów macierzy %s = %f\n", argv[1], suma(mac));
        fclose(fin);
    } else {
        printf("Nierozpoznany argument %s, Oczekiwałem: norm.\n", argv[1]);
    }    

    zapisz("wynik.txt", mac);

    return 0;
}