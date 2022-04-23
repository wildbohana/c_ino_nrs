/*
U programskom jeziku C/C++ implementirati funkciju čija je deklaracija:
float* Calculate(char* buffer);

Funkcija kao parametar prima pokazivač na niz bajtova. Niz bajtova treba interpretirati kao na slici ispod. 
Prvi bajt predstavlja matematičke operacije (0 - sabiranje, 1 - oduzimanje, 2 - množenje, 3 - deljenje).
Naredna četiri bajta predstavljaju prvi operand tipa integer, nakon čega 
slede naredna četiri bajta koja predstavljaju drugi operand tipa integer.

Na osnovu podataka dobijenih u nizu, primeniti odgovarajuću matematičku operaciju na operande. 
Povratna vrednost funkcije predstavlja pokazivač na broj u pokretnom zarezu (float) 
koji se dobije kao rezultat matematičke operacije.

Napisati test program za ovu funkciju.
*/

#include <stdio.h>
#include <stdlib.h>

enum kodOperacije {sabiranje, oduzimanje, mnozenje, deljenje};

// funkcija Calculate
float* Calculate(const char* inBuff)
{
	int* operand = (int*) (inBuff + 1);
	float* rez = NULL;
	rez = (float*) malloc(sizeof(float));

	switch (inBuff[0])
	{
		case sabiranje:
			*rez = (float)(operand[0] + operand[1]);
			break;
		case oduzimanje:
			*rez = (float)(operand[0] - operand[1]);
			break;
		case mnozenje:
			*rez = (float)(operand[0] * operand[1]);
			break;
		case deljenje:
			*rez = (float)operand[0] / operand[1];
			break;
	}

	return rez;
}


int main(int argc, char* argv[])
{
	// zauzimamo bafer koji cemo proslediti funkciji
	char* p_ParametarFunkcije = (char*) malloc(sizeof(char) + 2 * sizeof(int));
	char operacija;

	printf("Unesite operaciju koju zelite da koristite [+, -, *, /]:");
	scanf("%c", &operacija);
        fflush(stdin);
	
	// smestanje koda operacije u prvi bajt
	if (operacija == '+')
		p_ParametarFunkcije[0] = sabiranje; 
	else if (operacija == '-')
		p_ParametarFunkcije[0] = oduzimanje;
	else if (operacija == '*')
		p_ParametarFunkcije[0] = mnozenje;
	else if (operacija == '/')
		p_ParametarFunkcije[0] = deljenje;
	else 
		return 0;

	int op1, op2;

	// unos operanada
	printf("Unesite prvi broj: ");
	scanf("%d", &op1);
	getchar();

	printf("Unesite drugi broj: ");
	scanf("%d", &op2);
	getchar();

	// pokazuje na 2. mesto u baferu - prvi operand
	int* operand = (int*) (p_ParametarFunkcije + sizeof(char));

	// smestamo operande na njihovu poziciju u baferu
	operand[0] = op1;
	operand[1] = op2;

	float* rezultat;

	rezultat = Calculate(p_ParametarFunkcije);
	printf("Resenje je: %f\n", *rezultat);

	// obavezno oslobadjamo dinamicki alociranu memoriju
	free(rezultat);
	free(p_ParametarFunkcije);

	return 0;
}

