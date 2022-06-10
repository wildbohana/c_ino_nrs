/*
Napisati program koji prati stanje pwm signala na pinu 26 i ispisuje njegovu duzinu trajanja. 
Za generisanje signala koristiti funkciju pwmRandom() sa parametrima 26 i 2000.
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
        int time = millis();
        vremePerioda = time - pocetnoVreme;
        pocetnoVreme = time;

        if (!prvi) 
		{
           Serial.print(protekloVreme);
           Serial.print(' ');
           Serial.println(vremePerioda);
        }
        prvi = false;
	}
	staroStanje = novoStanje;
}

void setup()
{
	Serial.begin(9600);

	// pwmRandom(pin, period)
	pwmRandom(pin26, 2000);

	staroStanje = digitalRead(pin26);
	pocetnoVreme = millis();
	protekloVreme = 0;
	vremePerioda = 0;

	createTask(brojevi, 1, TASK_ENABLE, NULL);
}

void loop()
{

}
