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

#define brPoslednjihVrednosti 10
int brVrednosti;
int vrednosti[brPoslednjihVrednosti];

void klima(int id, void* tptr)
{
    if (available())
    {
        char* r = read();
		brVrednosti++;

        int t = atoi(r + 21);

        Serial.print("Temperatura: ");
        Serial.println(t);

		vrednosti[brVrednosti % brPoslednjihVrednosti] = t;

		if (brVrednosti >= 3)
		{
			int prethodni1 = (brVrednosti - 1) % brPoslednjihVrednosti;
			int prethodni2 = (brVrednosti - 2) % brPoslednjihVrednosti;

			if (vrednosti[prethodni1] > optimum && vrednosti[prethodni2] > optimum && t > optimum)
			{
				Serial.println("Postaje previse toplo. Ukljuci klimu.");
			}
			else if (vrednosti[prethodni1] < optimum && vrednosti[prethodni2] < optimum && t < optimum)
			{
				Serial.println("Postaje previse hladno. Iskljuci klimu.");
			}
		}
        delete[] r;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, RANDOM, 15, 25, 0.1, 500);

	brVrednosti = -1;
    createTask(klima, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
