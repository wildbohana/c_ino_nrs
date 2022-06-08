/*
Napisati program koji kontiunuirano prati stanje na senzorima i obradjuje prikupljene podatke. 
Od senzora se prikupljaju podaci o rednom broju elektronskog uredjaja na kojem se vrsi merenje, 
kao i naponu i jacini struje na uredjaju. Redni broj uredjaja je broj iz intervala od 0 do 20, 
jacina struje izrazava se u miliamperima i krece se u intervalu od 0 do 3000, 
a napon u voltima u intervalu od 180 do 260.
Svaki put kada napon padne ispod 200, ispisati poruku o tome na serijski monitor, 
koja sadrzi redni broj greske, redni broj uredjaja, kao i jacinu napona.
Nakon svakog merenja, ispisivati prosecnu jacinu struje u poslednjih 10 merenja.
Redni broj uredjaja je tipa integer, a napon i jacina struje tipa short.

Napomena 1: za generisanje podataka koristiti naredbu: 
startStopDataGeneration(START_GENERATION, RANDOM, 0, 20, 0.0, 200);
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

#define maxBrVrednosti 10
int brojVrednosti = 0;
int redniBrojGreske = 0;
int Uredjaj[maxBrVrednosti];
short Napon[maxBrVrednosti], Struja[maxBrVrednosti];

void brojevi(int id, void* tptr)
{
    if (available())
    {
        char* buffer = readAll();
        int velicina = *((int*) buffer);

        for (int i = 0; i < velicina; i++)
        {
            Uredjaj[brojVrednosti % maxBrVrednosti] = *(int*)(buffer + sizeof(int) + i * slogSize() + 32);
            Napon[brojVrednosti % maxBrVrednosti]= *(short*)(buffer + sizeof(int) + i * slogSize() + 36);
            Struja[brojVrednosti % maxBrVrednosti] = *(short*)(buffer + sizeof(int) + i * slogSize() + 38);

			// ako je napon pao ispod 200, ispisati poruku o tome
            if (Napon[brojVrednosti % maxBrVrednosti] < 200)
			{
                Serial.print("Pao napon ispod 200, redni broj greske: ");
                redniBrojGreske++;
                Serial.println(redniBrojGreske);

                Serial.print("Na uredjaju: ");
                Serial.println(Uredjaj[brojVrednosti % maxBrVrednosti]);
                Serial.print("Na jacinu napona: ");
                Serial.println(Napon[brojVrednosti % maxBrVrednosti]);
            }

            brojVrednosti++;

			// nakon svakog merenja, ispisivati prosecnu jacinu struje u poslednjih 10 merenja
			// nema smisla da racunamo ovo sve dok ne dodjemo do desetog merenja
            if (brojVrednosti > maxBrVrednosti) 
			{
                int sumaStruje = 0;

                for (int j = 0; j < maxBrVrednosti; j++)
                    sumaStruje += Struja[j];
                
                Serial.print("Prosecna struja je: ");
                Serial.println(sumaStruje/maxBrVrednosti);
            }
        }
		
        delete[] buffer;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, RANDOM, 0, 20, 0.0, 200);

    createTask(brojevi, 1000, TASK_ENABLE,  NULL);
}

void loop()
{

}
