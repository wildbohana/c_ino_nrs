/*
Napisati program koji prati stanje pwm signala na pinu 26 i ispisuje njegovu dužinu trajanja. 
Za generisanje signala koristiti funkciju pwm() sa parametrima 26, 2000, 750 i 0.2. 
U slučaju da se generisani signal razlikuje za više od 10% u odnosu na prethodna 2 signala, 
ispisati da je došlo do greške, prijaviti redni broj greške kao i procenat greške u ukupnom signalu.
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

#define brPoslednjihVrednosti 10
int brVrednosti;
int vrednosti[brPoslednjihVrednosti];
int brGresaka;

void brojevi(int id, void* tptr)
{
    static int prvi = true;

    int novoStanje = digitalRead(pin26);

	// dioda iskljucena
	if (staroStanje == 1 && novoStanje == 0) 
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
			Serial.print(protekloVreme);
			Serial.print(' ');
			Serial.println(vremePerioda);

			vrednosti[brVrednosti % brPoslednjihVrednosti] = protekloVreme;

			if (brVrednosti >= 3) 
			{
				int prethodni1 = (brVrednosti - 1) % brPoslednjihVrednosti;
				int prethodni2 = (brVrednosti - 2) % brPoslednjihVrednosti;

				if ((protekloVreme < vrednosti[prethodni1] * 0.9 || protekloVreme > vrednosti[prethodni1] * 1.1) 
				&&  (protekloVreme < vrednosti[prethodni2] * 0.9 || protekloVreme > vrednosti[prethodni2] * 1.1))
				{
					brGresaka++;

					Serial.print("Greska broj: ");
					Serial.println(brGresaka);

					Serial.print("Procenat greske: ");
					Serial.println(brGresaka * 100 / brVrednosti);
				}
			}
			brVrednosti++;
        }
        prvi = false;
	}
	staroStanje = novoStanje;
}

void setup()
{
	Serial.begin(9600);

	// pwm(pin, period, duzina, greska)
	pwm(pin26, 2000, 750, 0.2);

	staroStanje = digitalRead(pin26);
	pocetnoVreme = millis();
	protekloVreme = 0;
	vremePerioda = 0;
	brVrednosti = 0;
	brGresaka = 0;
	
	createTask(brojevi, 1, TASK_ENABLE, NULL);
}

void loop()
{

}
