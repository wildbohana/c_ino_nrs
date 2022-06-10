/*
Napisati program koji kontiunuirano prati stanje na senzorima i obradjuje prikupljene podatke. 
Od senzora se prikupljaju podaci o trenutnom datumu, vremenu, temperaturi vazduha, UV zracenju 
i vazdusnom pritisku. Koeficijent UV zracenja je vrednost između 0 i 10, dok je vazdusni 
pritisak izmedju 950 i 1050. Oba podatka su tipa short. Nakon svakog 30. podatka ispisati 
kolika je bila prosecna temperatura, prosecan vazdusni pritisak i najveca vrednost UV zracenja.

Napomena: neophodno je dopuniti tip podataka Slog novim podacima kao i generisati nove podatke.
*/

#include <arduinoPlatform.h>
#include <tasks.h>
#include <interrupts.h>
#include <stdio.h>
#include <serial.h>
#include <pwm.h>
#include <data.h>

extern serial Serial;

#define brPoslednjihVrednosti 30
int brVrednosti;
int temperatura[brPoslednjihVrednosti];
short UV[brPoslednjihVrednosti];
short pritisak[brPoslednjihVrednosti];

void brojevi(int id, void* tptr)
{
    if (available())
    {
        char *buffer = readAll();
        int velicina = *((int*) buffer);

        brVrednosti++;

        for (int i = 0; i < velicina; i++)
        {
            temperatura[brVrednosti] = *(int*)(buffer + sizeof(int) + i * slogSize() + 32);
            UV[brVrednosti] = *(short*)(buffer + sizeof(int) + i * slogSize() + 36);
            pritisak[brVrednosti] = *(short*)(buffer + sizeof(int) + i * slogSize() + 38);

			// na svakih 30 vrednosti, ispisujemo prosek
            if (brVrednosti == brPoslednjihVrednosti) 
			{
                brVrednosti = 0;
                int maxUV = UV[0];
                int sumaTemp = 0;
                int sumaPrit = 0;

                for (int j = 0; j < brPoslednjihVrednosti; j++) 
				{
                    sumaTemp += temperatura[j];
                    sumaPrit += pritisak[j];

                    if (maxUV < UV[j]) maxUV = UV[j];
                }
				
                Serial.print("Prosecna temperatura je: ");
                Serial.println(sumaTemp / brPoslednjihVrednosti);
                Serial.print("Prosecan pritisak je: ");
                Serial.println(sumaPrit / brPoslednjihVrednosti);
                Serial.print("Najveci koeficijent UV zracenja je: ");
                Serial.println(maxUV);
            }
        }
        delete[] buffer;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, SIN, 15, 40, 0.0, 200);

	brVrednosti = -1;
    createTask(brojevi, 1000, TASK_ENABLE,  NULL);
}

void loop()
{

}
