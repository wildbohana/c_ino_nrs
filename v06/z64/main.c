#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#pragma pack(4)

typedef struct {
    char ime[12];
    char prezime[12];
    char pol;
    short danR, mesecR, godinaR;
    char JMBG[14];
} Osoba;

void ispisStariju(char* buffer)
{
    int maxOsobaIndex = 0;

    for (int i = 1; i < *(short*) buffer; i++)
    {
        short* dan1 = (short*) &buffer[26 + maxOsobaIndex * sizeof(Osoba) + sizeof(short)];
        short* mesec1 = (short*) &buffer[28 + maxOsobaIndex * sizeof(Osoba) + sizeof(short)];
        short* godina1 = (short*) &buffer[30 + maxOsobaIndex * sizeof(Osoba) + sizeof(short)];

        short* dan2 = (short*) &buffer[26 + i * sizeof(Osoba) + sizeof(short)];
        short* mesec2 = (short*) &buffer[28 + i * sizeof(Osoba) + sizeof(short)];
        short* godina2 = (short*) &buffer[30 + i * sizeof(Osoba) + sizeof(short)];

        if (!(*godina1 < *godina2 ||
            *godina1 == *godina2 && *mesec1 < *mesec2 ||
            *godina1 == *godina2 && *mesec1 == *mesec2 && *dan1 < *dan2))
            maxOsobaIndex = i;
    }

    printf("Ime: %s\nPrezime: %s\nPol: %c\nJMBG: %s\n",
        buffer + maxOsobaIndex * sizeof(Osoba) + sizeof(short),
        buffer + maxOsobaIndex * sizeof(Osoba) + sizeof(short) + 12,
        *(buffer + maxOsobaIndex * sizeof(Osoba) + sizeof(short) + 24),
        buffer + maxOsobaIndex * sizeof(Osoba) + sizeof(short) + 32);
}

int main(void)
{
    Osoba os[3];
    char* buffer = (char*) malloc(sizeof(os) + 2);

    os[0] = (Osoba) {"Milica", "Milutinovic", 'M', 14, 2, 2001, "0123456789123"};
    os[1] = (Osoba) {"Nikola", "Novak", 'Z', 15, 7, 2004, "0123666789123"};
    os[2] = (Osoba) {"Mirjana", "Marjanovic", 'Z', 1, 1, 1999, "0163666789123"};

    *((short*) buffer) = 3;
    memcpy(buffer + 2, &os, sizeof(os));

    ispisStariju(buffer);

    free(buffer);

    return 0;
}
