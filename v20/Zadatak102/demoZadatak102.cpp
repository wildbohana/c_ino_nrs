/*
Napisati program koji kontiunuirano prati stanje na senzoru i pri pristizanju 
novih podataka ispisuje podatke na ekran. U slucaju da se generisani signal 
razlikuje za više od 10% u odnosu na prethodna 2 signala, ispisati da je doslo 
do greske, prijaviti datum i vreme greske kao i procenat greske u ukupnom signalu.
*/

#include <arduinoPlatform.h>
#include <tasks.h>
#include <interrupts.h>
#include <stdio.h>
#include <serial.h>
#include <data.h>

extern serial Serial;

#define brPoslednjihVrednosti 10
int brVrednosti;
int vrednosti[brPoslednjihVrednosti];
int brGresaka;

void broj(int id, void *tptr)
{
    if (available())
    {
		// dd.mm.yyyy. hh:mm:ss num
        char* r = read();
        brVrednosti++;

        // broj pocinje od 21. karaktera
        int br = atoi(r + 21);
        Serial.println(br);

        vrednosti[brVrednosti % brPoslednjihVrednosti] = br;

        if (brVrednosti >= 2) 
		{
            int prethodni1 = (brVrednosti - 1) % brPoslednjihVrednosti;
            int prethodni2 = (brVrednosti - 2) % brPoslednjihVrednosti;

            if ((br < vrednosti[prethodni1] * 0.9 || br > vrednosti[prethodni1] * 1.1) 
			&&  (br < vrednosti[prethodni2] * 0.9 || br > vrednosti[prethodni2] * 1.1))
			{
				brGresaka++;
				Serial.print("Greska broj: ");
				Serial.println(brGresaka);

				char datum[12];
				strncpy(datum, r, 11);
				datum[11] = '\0';
				Serial.print("Datum greske: ");
				Serial.println(datum);

				char vreme[9];
				vreme[8] = '\0';
				strncpy(vreme, r + 12, 8);
				Serial.print("Vreme greske: ");
				Serial.println(vreme);
				
				Serial.print("Procenat greske: ");
				Serial.println(brGresaka * 100 / brVrednosti);
			}
        }
        delete[] r;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, SAME, 0, 10, 0.1, 500);

    brVrednosti = -1;
    brGresaka = 0;

    createTask(broj, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
