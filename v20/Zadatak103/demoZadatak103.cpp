/*
Napisati program koji ispisuje vreme u koje je bio ocitan najveci broj. 
Pri svakoj promeni najveceg broja, ispisati vreme na ekran.
*/

#include <arduinoPlatform.h>
#include <tasks.h>
#include <interrupts.h>
#include <stdio.h>
#include <serial.h>
#include <data.h>

extern serial Serial;

static int najveci;

void broj(int id, void* tptr)
{
    if (available())
    {
        char* r = read();
        int br = atoi(r + 21);

		if (br > najveci)
		{
			najveci = br;
			Serial.print("Trenutni najveci broj: ");
			Serial.println(najveci);

			char datum[12];
			strncpy(datum, r, 11);
			datum[11] = '\0';
			Serial.print("Datum: ");
			Serial.print(datum);

			char vreme[9];
			vreme[8] = '\0';
			strncpy(vreme, r + 12, 8);
			Serial.print(", vreme: ");
			Serial.println(vreme);
		}
        delete[] r;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, RANDOM, 0, 100, 0.1, 500);

    najveci = -1;
    createTask(broj, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
