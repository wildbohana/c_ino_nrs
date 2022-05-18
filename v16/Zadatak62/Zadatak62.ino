void ispis(int id, void * tptr) 
{
	if (Serial.available()) 
	{
		char c = Serial.read();

		if ('0' <= c && c <= '9') 
		{
			Serial.println(c);

			c = c - '0';
			char s[5];
			itoa(c, s, 2);

			Serial.println(s);

			int i, len = strlen(s);

			for (i = 0; i < len; i++)
				if (s[i] == '1')
					digitalWrite(25 + len - i, HIGH);
				else
					digitalWrite(25 + len - i, LOW);

			for (i = len; i < 4; i++)
				digitalWrite(26 + i, LOW);
		}
	}
}

void setup()
{
	Serial.begin(9600);

	for(int i = 26; i < 30; i++) 
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
	createTask(ispis, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
