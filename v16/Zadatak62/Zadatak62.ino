/*
Napisati program koji učitava cifru po cifru sa serijskog ulaza i 
ispisuje te cifre u binarnom sistemu na lampicama na pinovima 29, 28, 27 i 26.
- Ukoliko je na primer ucitana cifra 5, ispisati 0101, tj. 
  upalite lampice 28 i 26, a ostale ugasiti.
*/

void ispis(int id, void* tptr) 
{
	if (Serial.available()) 
	{
		char c = Serial.read();

		if ('0' <= c && c <= '9') 
		{
			Serial.println(c);

			c = c - '0';
			char s[5];

			// itoa(integer, string, osnova)
			itoa(c, s, 2);

			Serial.println(s);

			int len = strlen(s);

			for (int i = 0; i < len; i++)
				if (s[i] == '1')
					digitalWrite(25 + len - i, HIGH);
				else
					digitalWrite(25 + len - i, LOW);

			for (int i = len; i < 4; i++)
				digitalWrite(26 + i, LOW);
		}
	}
}

void setup()
{
	Serial.begin(9600);

	for (int i = 26; i < 30; i++) 
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
	
	createTask(ispis, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
