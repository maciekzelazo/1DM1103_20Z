#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// wczytal z pliku wektor liczb i wyswietli na ekranie ich sume!
int main(int argc, char *argv[]) {
    FILE *fin; //
    int dlugosc = 0;
    int i;
    float suma, liczba;
    int wlasciwie_zinterpretowane;

    fin = fopen( "nazwa.txt", "r");
    if ((wlasciwie_zinterpretowane = fscanf(fin, "%d", &dlugosc)) != 1) {
        printf("Pierwszy napis nie jest liczbą całkowitą "
               "(Liczba prawidłowo zinterpretowanych argumentów: %d)!\n", 
               wlasciwie_zinterpretowane);
        exit(-1);
    }

    printf("%d\n", dlugosc);

    suma = 0;
    for (i=0; i<dlugosc; i++) {
        if (fscanf(fin, "%f", &liczba) != 1) {
            printf("%d-ta liczba w pliku nie jest liczbą zmiennoprzecinkową.\n", i+1);
            exit(-2);
        }
        suma += liczba;
    }

    printf("Suma %d liczb z pliku nazwa.txt: %f\n", dlugosc, suma);

    return 0;
}