/*
Napisati program koji broji koliko je upaljenih prekidača 
na pinovima 2, 7, 8 i 35, i u zavisnosti od toga pali duplo 
veći broj lampica, počevši od lampice sa brojem 26.
*/

#define LED1 26

void setup()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(LED1 + i, OUTPUT);
        digitalWrite(LED1 + i, LOW);
    }

    Serial.begin(9600);
}

void loop()
{
    int brojac = 0;

	if (digitalRead(2))  brojac++;
	if (digitalRead(7))  brojac++;
	if (digitalRead(8))  brojac++;
	if (digitalRead(35)) brojac++;

	int br_lampica = brojac * 2;

	for (int i = 0; i < br_lampica; i++)
		digitalWrite(LED1 + i, HIGH);
	
	delay(1000);

	for (int i = 0; i < br_lampica; i++)
		digitalWrite(LED1 + i, LOW);
}
