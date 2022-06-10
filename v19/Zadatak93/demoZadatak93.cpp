/*
Napisati program koji prati stanje pwm signala na pinu 26 i ispisuje njegovu duzinu trajanja. 
Za generisanje signala koristiti funkciju pwmSin() sa parametrima 26, 2000 i 0.0. 
Nakon toga, izracunati i ispisati period oscilovanja signala. 
Period oscilovanja signala ispisati kao vreme proteklo izmedju dva maksimuma u signalu.
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

#define maksimum 2000

void brojevi(int id, void* tptr)
{
    static int prvi = true;

	static bool dostignutMaksimum = false;
	static int pocetakPerioda = 0;

    int novoStanje = digitalRead(pin26);

	if (staroStanje == 1 && novoStanje == 0) 
	{
        protekloVreme = millis() - pocetnoVreme;

		if (protekloVreme >= maksimum)
			dostignutMaksimum = true;
	} 
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

			if (dostignutMaksimum)
			{
			    int razlika = millis() - pocetakPerioda;
				Serial.print("Vreme izmedju dva maksimuma: ");
				Serial.println(razlika);

				pocetakPerioda = millis();
				dostignutMaksimum = false;
			}
        }
        prvi = false;
	}
	staroStanje = novoStanje;
}

void setup()
{
	Serial.begin(9600);

	// pwmSin(pin, period, greska)
	pwmSin(26, 2000, 0.0);

	staroStanje = digitalRead(pin26);
	pocetnoVreme = millis();
	protekloVreme = 0;
	vremePerioda = 0;

	createTask(brojevi, 1, TASK_ENABLE, NULL);
}

void loop()
{

}
