#include <stdio.h>
#include <stdlib.h>

int konverzija(char *s)
{
	int rez, i;
   	rez = 0;
   	i = 0;

   	while (s[i] != 0) 
	{
    		rez = rez * 2 + s[i] - '0';
    		i++;
   	}
   	return rez;
}

int main()
{
    int n;
    char s[20];

    printf("Unesite binarni broj koji treba kovertovati: ");
    scanf("%s", &s);

    n = konverzija(s);
    printf("Dekadni broj izgleda ovako: %d\n", n);
	
    return 0;
}
