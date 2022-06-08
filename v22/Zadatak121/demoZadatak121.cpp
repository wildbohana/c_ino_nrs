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

#define myPIN 26
int oldState, periodTime, startTime, elapsedTime;

#define numOfLastValues 20
int numOfValues;
int values[numOfLastValues];
int brPojavljivanja[41];
int numOfErrors;
int suma = 0;
int suma20 = 0;

void brojevi(int id, void * tptr)
{
    static int first = true;
    int newState = digitalRead(myPIN);

	// dioda iskljucena
	if (oldState == 1  && newState == 0) 
	{
        elapsedTime = millis() - startTime;
	} 
	// dioda ukljucena
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

			// prosecna temperatura za poslednjih 20 merenja
			// ulazni signal predstavlja temparaturu u prostoriji u rasponu od 1 do 40 stepeni
			int temperatura = map(elapsedTime, 0, 2000, 0, 40);
			suma20 = suma20 - values[numOfValues % numOfLastValues] + temperatura;
			values[numOfValues % numOfLastValues] = temperatura;

			// prosecna temperatura za sva merenja
			suma = suma + temperatura;
			brPojavljivanja[temperatura]++;
			numOfValues++;

			Serial.print("Prosecna temperatura: ");
			Serial.println(suma / numOfValues);

			if (numOfValues >= numOfLastValues) 
			{
				Serial.print("Prosecna temperatura poslednjih 20 merenja: ");
				Serial.println(suma20 / numOfLastValues);
			}

			// nakon svakih 20 prikupljenih temperatura, ispisati koja  
			// temperatura je najcesce izmerena u prostoriji.
			if (numOfValues % numOfLastValues == 0) 
			{
				int maxJ = 0;
				for (int j = 1; j <= 40; j++)
					if (brPojavljivanja[j] > brPojavljivanja[maxJ])
						maxJ = j;

				Serial.print("Najcesca temperatura: ");
				Serial.println(maxJ);
			}
        }
        first = false;
	}
	oldState = newState;
}

void setup()
{
	Serial.begin(9600);

	pwmSin(myPIN, 2000, 0.0);

	oldState = digitalRead(myPIN);
	startTime = millis();
	elapsedTime = 0;
	periodTime = 0;
	numOfValues = 0;
	
	for (int i = 0; i < numOfLastValues; i++)
		values[i] = 0;
	for (int i = 0; i <= 40; i++)
		brPojavljivanja[i] = 0;
		
	createTask(brojevi, 1, TASK_ENABLE, NULL);
}

void loop()
{

}
