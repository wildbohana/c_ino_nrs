#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int konverzija(char* s)
{
    int rez;
    int mask = 1;

    int i = strlen(s) - 1;

    while (i >= 0)
    {
        if (s[i] == '1')
            rez = rez | mask;

        mask = mask << 1;
        i--;
    }

    return rez;
}

int main()
{
    int x;
	char s[33];

	printf("Unesite binarni broj: ");
	scanf("%s", s);

	x = konverzija(s);

	printf("Broj u dekadnom formatu: %d\n", x);

    return 0;
}
