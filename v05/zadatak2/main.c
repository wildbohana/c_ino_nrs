/*
Koristeći kreirani bafer, omogućiti čitanje 8 po 8 bita iz bafera u jedan karakter, 
i prikazivanje tog karaktera na ekranu. Karakter treba da se sastoji iz 8 pročitanih bitova.

Na primer, ako se pročita broj 01000001, taj broj predstavlja broj 65, što je ascii vrednost slova 'A'.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BitsBuffer.h"

int main()
{
    bitbuffer b;
    initbuff(&b);

    char message[] = "010010000110010101101100011011000110111100100000011101110110111101110010011011000110010000100001";
	
    for(int i = 0; i < strlen(message); i++) {
        push(&b, message[i] - '0');
    }

    while(!isEmpty(b)) {
        char c;

        for (int i = 0; i < 8; i++){
            int num = pop(&b);
            setBit(&c, i, num);
        }

        printf("%c", c);
    }

    return 0;
}
