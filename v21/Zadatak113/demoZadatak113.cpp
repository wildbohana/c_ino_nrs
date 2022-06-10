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

#define brPoslednjihVrednosti 10
int brVrednosti;
int redniBrGreske;
int uredjaj[brPoslednjihVrednosti];
short napon[brPoslednjihVrednosti];
short struja[brPoslednjihVrednosti];

void brojevi(int id, void* tptr)
{
    if (available())
    {
        char* buffer = readAll();
        int velicina = *((int*) buffer);

		brVrednosti++;

        for (int i = 0; i < velicina; i++)
        {
            uredjaj[brVrednosti % brPoslednjihVrednosti] = *(int*)(buffer + sizeof(int) + i * slogSize() + 32);
            napon[brVrednosti % brPoslednjihVrednosti] = *(short*)(buffer + sizeof(int) + i * slogSize() + 36);
            struja[brVrednosti % brPoslednjihVrednosti] = *(short*)(buffer + sizeof(int) + i * slogSize() + 38);

			// ako je napon pao ispod 200, ispisati poruku o tome
            if (napon[brVrednosti % brPoslednjihVrednosti] < 200)
			{
				redniBrGreske++;
                Serial.print("Pao napon ispod 200, redni broj greske: ");
                Serial.println(redniBrGreske);

                Serial.print("Na uredjaju: ");
                Serial.println(uredjaj[brVrednosti % brPoslednjihVrednosti]);
                Serial.print("Na jacinu napona: ");
                Serial.println(napon[brVrednosti % brPoslednjihVrednosti]);
            }

			// nakon svakog merenja, ispisivati prosecnu jacinu struje u poslednjih 10 merenja
            if (brVrednosti > brPoslednjihVrednosti) 
			{
                int sumaStruje = 0;

                for (int j = 0; j < brPoslednjihVrednosti; j++)
                    sumaStruje += struja[j];
                
                Serial.print("Prosecna struja je: ");
                Serial.println(sumaStruje / brPoslednjihVrednosti);
            }
        }
        delete[] buffer;
    }
}

void setup()
{
    Serial.begin(9600);

    startStopDataGeneration(START_GENERATION, RANDOM, 0, 20, 0.0, 200);

	brVrednosti = -1;
	redniBrGreske = 0;
    createTask(brojevi, 1000, TASK_ENABLE,  NULL);
}

void loop()
{

}
