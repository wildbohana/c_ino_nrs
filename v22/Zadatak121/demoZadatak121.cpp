/*
Napisati program koji prati stanje pwm signala na pinu 26 i ispisuje njegovu duzinu trajanja. 
Za generisanje signala koristiti funkciju pwmSin() sa parametrima 26, 2000 i 0.0.
Neka ulazni signal predstavlja temparaturu u prostoriji u rasponu od 1 do 40 stepeni. 
Ispisati prosecnu temperaturu poslednjih 20 merenja, kao i prosecnu temperaturu za sva merenja.
Nakon svakih 20 prikupljenih temperatura, ispisati koja temperatura je 
najcesce izmerena u prostoriji.
*/

#include <arduinoPlatform.h>
#include <tasks.h>
#include <interrupts.h>
#include <stdio.h>
#include <serial.h>
#include <pwm.h>

extern serial Serial;

#define pin26 26
int staroStanje;
int vremePerioda;
int pocetnoVreme;
int protekloVreme;

#define brPoslednjihVrednosti 20
int brVrednosti;
int vrednosti[brPoslednjihVrednosti] = {0};
int brPojavljivanja[41] = {0};
int brGresaka;
int suma;
int suma20;

void brojevi(int id, void * tptr)
{
    static int prvi = true;
	
    int novoStanje = digitalRead(pin26);

	// dioda iskljucena
	if (staroStanje == 1  && novoStanje == 0) 
	{
        protekloVreme = millis() - pocetnoVreme;
	} 
	// dioda ukljucena
	else if (staroStanje == 0 && novoStanje == 1)
	{
        int vreme = millis();
        vremePerioda = vreme - pocetnoVreme;
        pocetnoVreme = vreme;

        if (!prvi) 
		{
			brVrednosti++;

			Serial.print(protekloVreme);
			Serial.print(' ');
			Serial.println(vremePerioda);

			int temperatura = map(protekloVreme, 0, 2000, 0, 40);
			suma20 = suma20 - vrednosti[brVrednosti % brPoslednjihVrednosti] + temperatura;
			vrednosti[brVrednosti % brPoslednjihVrednosti] = temperatura;

			// prosecna temperatura za sva merenja
			suma = suma + temperatura;
			brPojavljivanja[temperatura]++;

			Serial.print("Prosecna temperatura: ");
			Serial.println(suma / brVrednosti);

			if (brVrednosti >= brPoslednjihVrednosti) 
			{
				Serial.print("Prosecna temperatura poslednjih 20 merenja: ");
				Serial.println(suma20 / brPoslednjihVrednosti);
			}

			// nakon svakih 20 prikupljenih temperatura, ispisati koja  
			// temperatura je najcesce izmerena u prostoriji.
			if (brVrednosti % brPoslednjihVrednosti == 0) 
			{
				int maxJ = 0;
				
				for (int j = 1; j <= 40; j++)
					if (brPojavljivanja[j] > brPojavljivanja[maxJ])
						maxJ = j;

				Serial.print("Najcesca temperatura: ");
				Serial.println(maxJ);
			}
        }
        prvi = false;
	}
	staroStanje = novoStanje;
}

void setup()
{
	Serial.begin(9600);

	pwmSin(pin26, 2000, 0.0);

	staroStanje = digitalRead(pin26);
	pocetnoVreme = millis();
	protekloVreme = 0;
	vremePerioda = 0;

	brVrednosti = 0;		
	suma = 0;
	suma20 = 0;

	createTask(brojevi, 1, TASK_ENABLE, NULL);
}

void loop()
{

}
