#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char*argv[])
{
    FILE *fin1;
    FILE *fin2;
    fin1=fopen(argv[1], "r");
    fin2=fopen(argv[2], "r");
    float macierz[100][100];
    float wektor[100];
    int liczba_wierszy_macierzy;
    int liczba_kolumn_macierzy;
    int liczba_wierszy_wektora;
   
    fscanf(fin1, "%d %d %f %f %f %f %f %f", &liczba_wierszy_macierzy, &liczba_kolumn_macierzy, &macierz[3][1], &macierz[3][2], 
    &macierz[4][1], &macierz[4][2], &macierz[5][1], &macierz[5][2]);
    fscanf(fin2, "%d %f %f %f %f", &liczba_wierszy_wektora, &wektor[2], &wektor[3], &wektor[4], &wektor[5]);

    
    if(liczba_kolumn_macierzy==liczba_wierszy_wektora)
    {
        printf("(%d) ", liczba_wierszy_macierzy);
        printf("[%.1f %.1f %.1f]", (macierz[3][1]*wektor[3])+(macierz[3][2]*wektor[4]), 
    (macierz[4][1]*wektor[3])+(macierz[4][2]*wektor[4]), (macierz[5][1]*wektor[3])+(macierz[5][2]*wektor[4])); 
    }
    else
    {
         printf("Nie można pomnożyć przez siebie podanych macierzy");
    }  
}


