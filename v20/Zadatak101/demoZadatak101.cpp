/*
Napisati program koji kontiunuirano prati stanje na senzoru i pri pristizanju novih 
podataka ispisuje podatke na ekran. Takodje, ispisati i sumu svih pristiglih podataka.
*/

#include <arduinoPlatform.h>
#include <tasks.h>
#include <interrupts.h>
#include <stdio.h>
#include <serial.h>
#include <data.h>

extern serial Serial;

int suma;

void broj(int id, void* tptr)
{
    if (available())
    {
		// dd.mm.yyyy. hh:mm:ss num
        char *r = read();
        Serial.print(r);

        // broj pocinje od 21. karaktera
        int br = atoi(r + 21);

        suma = suma + br;

        Serial.print(" Broj: ");
        Serial.print(br);
        Serial.print(" Suma: ");
        Serial.println(suma);

        delete[] r;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, RANDOM, 0, 100, 0.2, 500);

    suma = 0;
    createTask(broj, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
