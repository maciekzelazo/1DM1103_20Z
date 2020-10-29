#include <stdio.h>
#include <stdlib.h>


int dlugosc_napisu(char *napis) {
    int l = 0;
    while (napis[l] != 0) 
        l++;
    return l;
}

void skopiuj(char *gdzie, char *co, int max) {
    int i=0;
    while ((co[i] != 0) && (i<max)) {
        gdzie[i] = co[i];
        i++;
    }
    gdzie[i] = 0;
}

int znajdz(char z, char *n) {
    int i = 0;
    int max = dlugosc_napisu(n);

    while ( (z != n[i]) && (i < max) )
        i++;
    if (i<max)
        return i;
    else
        return -1;
}

void nawielkie(char * n) {
    char *male = "abcdefghijklmnopqrstuvwxyz";
    char *duze = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i,j;

    for (i=0; i< dlugosc_napisu(n); i++) {
        j = znajdz(n[i], male);
        if (j >= 0)
            n[i] = duze[j];
    }
}


int main(int argc, char *argv[]) {
    char napis[255];
    printf("%s ma dlugosc: %d\n", argv[1], dlugosc_napisu(argv[1]));

    printf("Przed\n");
    skopiuj(napis, argv[2], 254);
    nawielkie(napis);
    printf("Po\n");
    printf("%s ma dlugosc: %d\n", napis, dlugosc_napisu(napis));

    return 0;
}

