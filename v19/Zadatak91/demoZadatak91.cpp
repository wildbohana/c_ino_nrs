/*
Napisati program koji prati stanje pwm signala na pinu 26 i ispisuje njegovu duzinu trajanja. 
Za generisanje signala koristiti funkciju pwmRandom() sa parametrima 26 i 2000.
*/

#include<arduinoPlatform.h>
#include<tasks.h>
#include<interrupts.h>
#include<stdio.h>
#include <serial.h>
#include <pwm.h>

extern serial Serial;

#define myPIN 26

int oldState;
int periodTime;
int startTime;
int elapsedTime;

void brojevi(int id, void* tptr)
{
    static int first = true;

    int newState = digitalRead(myPIN);

	// dioda iskljucena
	if (oldState == 1 && newState == 0) 
	{
		// merimo koliko dugo je bila ukljucena
        elapsedTime = millis() - startTime;
	} 
	// dioda ukljucena
	else if (oldState == 0 && newState == 1) 
	{
        int time = millis();
		// ukupno trajanje perioda
        periodTime = time - startTime;
        startTime = time;

		// ispisujemo za sve vrednosti osim za prvu
        if (!first) 
		{
           Serial.print(elapsedTime);
           Serial.print(' ');
           Serial.println(periodTime);
        }

        first = false;
	}
	
	oldState = newState;
}

void setup()
{
	Serial.begin(9600);

	// pwmRandom(pin, period)
	pwmRandom(myPIN, 2000);

	oldState = digitalRead(myPIN);
	startTime = millis();
	elapsedTime = 0;
	periodTime = 0;

	createTask(brojevi, 1, TASK_ENABLE, NULL);
}

void loop()
{

}
