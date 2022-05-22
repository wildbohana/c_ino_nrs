const int analogInPin = A0;

int merenja[5] = {0};
int x = 0;

void potenciometar(int id, void * tptr)
{
    int novaJacina = analogRead(analogInPin);
	merenja[x] = novaJacina;

	int minimum = merenja[0];
	int maksimum = merenja[0];
	
	for (int i = 1; i < 5; i++)
	{
		if (merenja[i] < minimum)
			minimum = merenja[i];

		if (merenja[i] > maksimum)
			maksimum = merenja[i];
	}

	if (maksimum - minimum > 200)
	{
		Serial.println("Doslo je do naglog skoka!\n");
		
		for (int i = 0; i < 5; i++)
			merenja[i] = novaJacina;
	}
   
    // x = (x + 1) % 5;
	if (++x == 5) x = 0;
}

void setup()
{
    Serial.begin(9600);
    createTask(potenciometar, 100, TASK_ENABLE, NULL);
}

void loop()
{

}
