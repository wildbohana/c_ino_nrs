#ifndef ISPIT_H_INCLUDED
#define ISPT_H_INCLUDED
#pragma pack(4)

typedef struct {
    short dan, mesec, godina;
    char ocena;
    int sifraIspRok;
    char profesor[30];
} ispit;

void ispisiPodatke();

#endif
