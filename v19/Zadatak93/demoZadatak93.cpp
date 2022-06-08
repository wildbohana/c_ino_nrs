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

#define myPIN 26
int oldState;
int periodTime;
int startTime;
int elapsedTime;

#define maksimum 2000

void brojevi(int id, void* tptr)
{
    static int first = true;

	static bool dostignut_maksimum = false;
	static int period_begin = 0;

    int newState = digitalRead(myPIN);

	if (oldState == 1 && newState == 0) 
	{
        elapsedTime = millis() - startTime;

		if (elapsedTime >= maksimum)
			dostignut_maksimum = true;
	} 
	else if (oldState == 0 && newState == 1) 
	{
        int time = millis();
        periodTime = time - startTime;
        startTime = time;

        if (!first) 
		{
			Serial.print(elapsedTime);
			Serial.print(' ');
			Serial.println(periodTime);

			if (dostignut_maksimum)
			{
			    int razlika = millis() - period_begin;
				Serial.print("Vreme izmedju dva maksimuma: ");
				Serial.println(razlika);

				period_begin = millis();
				dostignut_maksimum = false;
			}
        }
        first = false;
	}
	oldState = newState;
}

void setup()
{
	Serial.begin(9600);

	// pwmSin(pin, period, greska)
	pwmSin(26, 2000, 0.0);

	oldState = digitalRead(myPIN);
	startTime = millis();
	elapsedTime = 0;
	periodTime = 0;

	createTask(brojevi, 1, TASK_ENABLE, NULL);
}

void loop()
{

}
