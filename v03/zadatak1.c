/*
Napraviti sledeće funkcije:
void copyLEToLE(int, void*) - koja kopira broj dat u LE formatu na datu adresu u LE formatu
void copyLEToBE(int, void*) - koja kopira broj dat u LE formatu na datu adresu u BE formatu

hint: za kopiranje iz BE u LE ne moramo praviti novu funkciju, koristimo LE u BE u oba slučaja.
fun fact: za float nam ne treba nova funkcija, nego samo float tretiramo kao int
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void copyLEToLE(int x, void* copy) 
{
	for (int i = 0; i < sizeof(x); i++)
    		*((char*) copy + i) = *((char*) &x + i);
}

void copyLEToBE(int x, void* copy) 
{
	for (int i = 0; i < sizeof(x); i++)
		*((char*) copy + i) = *((char*) &x + sizeof(x) - 1 - i);
}

int main()
{
    int a = 0x012A5F87, aLE, aBE;

    copyLEToLE(a, &aLE);
    printf("Vrednost a u LE formatu: %08x\n", aLE);

    copyLEToBE(a, &aBE);
    printf("Vrednost a u BE formatu: %08x\n", aBE);
	
    return 0;
}
