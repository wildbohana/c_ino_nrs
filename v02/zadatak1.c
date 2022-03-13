#include <stdio.h>
#include <stdlib.h>

enum operacija { sabiranje, oduzimanje, mnozenje, deljenje };

float* Calculate(const char* inBuff) {

	char izbor = *inBuff;
	int* a = (int*)(inBuff + 1 * sizeof(char));
	int* b = (int*)(inBuff + 5 * sizeof(char));

	float* rez = (float*)malloc(sizeof(float));

	// *p == niz[0]
	switch (izbor) {

	case sabiranje:
		*rez = (float)(*a + *b);
		break;
	case oduzimanje:
		*rez = (float)(*a - *b);
		break;
	case mnozenje:
		*rez = (float)(*a * *b);
		break;
	case deljenje:
		*rez = (float)(*a / *b);		// samo ovo radi kako treba
		break;
	}

	return rez;
}

int main(int argc, char* argv[])
{
	char niz[9] = { 1, 0, 0, 0, 12, 0, 0, 0, 3 };		// računa: 12 - 3

	float* rezultat;
	rezultat = Calculate(niz);

	printf("Resenje je : %f\n", *rezultat);
	free(rezultat);

	return 0;
}
