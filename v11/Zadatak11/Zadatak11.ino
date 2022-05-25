/*
Napisati program koji pali i gasi led diode LD8 i LD2 na pinovima 33 i 27. 
Pin 33 se i pali i gasi u jednom ciklusu loop-a, 
a pin 27 se pali ili gasi u zavisnosti od stanja prekidača SW2 na pinu 7.
*/

#define dump(v) Serial.println(v) 

#define LED8 33
#define LED2 27
#define SW2 7

void setup()
{
	pinMode(LED8, OUTPUT);
	pinMode(LED2, OUTPUT);

	Serial.begin(9600);
}

void loop()
{
	digitalWrite(LED8, HIGH);
	delay(1000);
	digitalWrite(LED8, LOW);
	delay(1000);

	int pin7 = digitalRead(SW2);
	dump(pin7);

	if (pin7)
		digitalWrite(LED2, HIGH);
	else
		digitalWrite(LED2, LOW);
}
