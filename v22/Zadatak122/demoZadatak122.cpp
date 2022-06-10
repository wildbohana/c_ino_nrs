/*
Napisati program koji kontiunuirano prati stanje na senzorima, obradjuje prikupljene podatke i ispisuje na serijski monitor. Od senzora se prikupljaju podaci o rednom 
broju elektronskog uređaja na kojem se vrsi merenje, kao i naponu i jacini struje na 
uredjaju. Redni broj uredjaja je broj iz intervala od 0 do 20, jacina struje izrazava 
se u miliamperima i krece se u intervalu od 0 do 3000, a napon u voltima u intervalu 
od 180 do 260.
Ukoliko neki uredjaj primi napon koji se za više od 30 volti razlikuje od 
prethodnog napona za taj uredjaj, prijaviti upozorenje na serijski monitor.
Nakon svakih 30 ucitanih podataka, ispisati koji uredjaj ima najvise prijavljenih 
upozorenja. U slucaju da ima vise takvih uredjaja, ispisati jedan od njih.
Redni broj uređaja je tipa integer, a napon i jacina struje tipa short.

Napomena 1: za generisanje podataka koristiti naredbu: 
startStopDataGeneration(START_GENERATION, RANDOM, 0, 20, 0.0, 1000);
Napomena 2: fajl data.cpp za ovaj zadatak nalazi se na sajtu predmeta.
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
#define brPoslednjihUredjaja 21
int brVrednosti;
short napon[brPoslednjihUredjaja] = {0};
short brUpozorenja[brPoslednjihUredjaja] = {0};

void brojevi(int id, void* tptr)
{
    if (available())
    {
        char* buffer = readAll();
        int velicina = *((int*) buffer);

        brVrednosti++;

        for (int i = 0; i < velicina; i++)
        {
            int brUredjaja = *(int*) (buffer + sizeof(int) + i * slogSize() + 32);
            int izmereniNapon = *(short*) (buffer + sizeof(int) + i * slogSize() + 36);
            int izmerenaJacina = *(short*) (buffer + sizeof(int) + i * slogSize() + 38);

            Serial.print(brUredjaja);
            Serial.print(" ");
            Serial.print(izmereniNapon);
            Serial.print(" ");
            Serial.println(izmerenaJacina);

			// ukoliko neki uredjaj primi napon koji se za više od 30 volti razlikuje od 
			// prethodnog napona za taj uredjaj, prijaviti upozorenje na serijski monitor
            if (abs(izmereniNapon - napon[brUredjaja]) > 30 && napon[brUredjaja] != 0) 
			{
                brUpozorenja[brUredjaja]++;
                Serial.print("Upozorenje, neodgovarajuc napon na uredjaju broj: ");
                Serial.println(brUredjaja);
            }

            napon[brUredjaja] = izmereniNapon;

			// nakon svakih 30 ucitanih podataka, ispisati koji
			// uredjaj ima najvise prijavljenih upozorenja
            if (brVrednosti % brPoslednjihVrednosti == 0) 
			{
                int maxJ = 0;

                for (int j = 1; j < brUredjaja; j++)
                    if (brUpozorenja[maxJ] < brUpozorenja[j])
                        maxJ = j;

                Serial.print("Najvise upozorenja je na uredjaju broj: ");
                Serial.println(maxJ);
            }
        }
        delete[] buffer;
    }
}

void setup()
{
    Serial.begin(9600);

	startStopDataGeneration(START_GENERATION, RANDOM, 0, 20, 0.0, 1000);

    brVrednosti = -1;
    createTask(brojevi, 1000, TASK_ENABLE,  NULL);
}

void loop()
{

}
