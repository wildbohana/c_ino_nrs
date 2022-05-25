/*
Napisati program koji sa potenciometra čita vrednost 
ulaza i tu vrednost ispisuje na 8 lampica. Broj upaljenih 
lampica krenuvši od lampice na pinu 26 treba da bude 
srazmeran jačini ulaza sa potenicometra.

*/

const int analog_in = A0;

void potenciometar(int id, void* tptr)
{
	int jacina = analogRead(analog_in);
	int br_lampica = map(jacina, 0, 1023, 0, 8);

	for (int i = 0; i < 8; i++)
	{
		if (i < br_lampica)
			digitalWrite(26 + i, HIGH);
		else
			digitalWrite(26 + i, LOW);
	}
}

void setup()
{
	Serial.begin(9600);
	
	for (int i = 26; i < 34; i++)
		pinMode(i, OUTPUT);

	createTask(potenciometar, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
