#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ispit
{
    char imeIspita[20];
    short ocena;
} ispit;

typedef struct Student
{
    char ime[20];
    char prezime[20];
    char brojIndeksa[10];
    int  brojIspita;
    ispit ispiti[10];
} student;

#endif
