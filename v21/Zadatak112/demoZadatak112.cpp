/*
Napisati program koji kontiunuirano prati stanje na senzorima i obradjuje prikupljene podatke. 
Od senzora se prikupljaju podaci o trenutnom datumu, vremenu, temperaturi vazduha, UV zracenju 
i vazdusnom pritisku. Koeficijent UV zracenja je vrednost između 0 i 10, dok je vazdusni 
pritisak izmedju 950 i 1050. Oba podatka su tipa short. Nakon svakog 30. podatka ispisati 
kolika je bila prosecna temperatura, prosecan vazdusni pritisak i najveca vrednost UV zracenja.

Napomena: neophodno je dopuniti tip podataka Slog novim podacima kao i generisati nove podatke.
*/

#include<arduinoPlatform.h>
#include<tasks.h>
#include<interrupts.h>
#include<stdio.h>
#include<serial.h>
#include <pwm.h>
#include<data.h>

extern serial Serial;

#define maxBrVrednosti 30
int brojVrednosti = 0;
int temperatura[maxBrVrednosti];
short UV[maxBrVrednosti];
short pritisak[maxBrVrednosti];

void brojevi(int id, void* tptr)
{
    if (available())
    {
        char *buffer = readAll();
        int velicina = *((int*) buffer);

        for (int i = 0; i < velicina; i++)
        {
            temperatura[brojVrednosti] = *(int*)(buffer + sizeof(int) + i * slogSize() + 32);
            UV[brojVrednosti]= *(short*)(buffer + sizeof(int) + i * slogSize() + 36);
            pritisak[brojVrednosti] = *(short*)(buffer + sizeof(int) + i * slogSize() + 38);

            brojVrednosti++;

			// na svakih 30 vrednosti, ispisujemo prosek
            if (brojVrednosti == maxBrVrednosti) 
			{
                brojVrednosti = 0;
                int maxUV = UV[0];
                int sumaTemp = 0;
                int sumaPrit = 0;

                for (int j = 0; j < maxBrVrednosti; j++) 
				{
                    sumaTemp += temperatura[j];
                    sumaPrit += pritisak[j];

                    if (maxUV < UV[j]) maxUV = UV[j];
                }
				
                Serial.print("Prosecna temperatura je: ");
                Serial.println(sumaTemp / maxBrVrednosti);
                Serial.print("Prosecan pritisak je: ");
                Serial.println(sumaPrit / maxBrVrednosti);
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

    createTask(brojevi, 1000, TASK_ENABLE,  NULL);
}

void loop()
{

}
