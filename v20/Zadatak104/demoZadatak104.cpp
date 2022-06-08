/*
Sa senzora se ucitavaju temperature vazduha u prostoriji u kojoj treba odrzavati 
ujednacenu temperaturu od 20 stepeni. Ukoliko temperatura 3 puta zaredom 
dostigne 21 stepen, ispisati na serijski monitor da treba upaliti klima 
uredjaj na hladjenje. Ukoliko se temperatura 3 puta zaredom spusti ispod 19 
stepeni, ispisati na serijski monitor da treba upaliti klima uredjaj na grejanje.
*/

#include <arduinoPlatform.h>
#include <tasks.h>
#include <interrupts.h>
#include <stdio.h>
#include <serial.h>
#include <data.h>

extern serial Serial;

#define optimum 20

#define numOfLastValues 10
int numOfValues;
int values[numOfLastValues];

void klima(int id, void* tptr)
{
    if (available())
    {
        char *r = read();
        int t = atoi(r + 21);

        Serial.print("Temperatura: ");
        Serial.println(t);

		values[numOfValues % numOfLastValues] = t;

		if (numOfValues >= 3) 
		{
			int prev1 = (numOfValues - 1) % numOfLastValues;
			int prev2 = (numOfValues - 2) % numOfLastValues;

			if (prev1 > optimum && prev2 > optimum && t > optimum)
			{
				Serial.println("Postaje previse toplo. Ukljuci klimu.");
			}
			else if (prev1 < optimum && prev2 < optimum && t < optimum)
			{
				Serial.println("Postaje previse hladno. Iskljuci klimu.");
			}
		}

		numOfValues++;

        delete[] r;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, RANDOM, 0, 40, 0.2, 500);
	
	numOfValues = 0;
    createTask(klima, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
