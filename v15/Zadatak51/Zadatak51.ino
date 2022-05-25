/*
Napisati program koji sa potenciometra čita vrednost ulaza 
i tu vrednost ispisuje na digitalni izlaz LD8 (pin 33). 
Stanje potenciometra osvežavati na svakih 500 milisekundi.
*/

// A0 - potenciometar
const int analog_in = A0;
const int analog_out = 33;

void potenciometar(int id, void* tptr)
{
	int senzor = analogRead(analog_in);
	int skaliran = map(senzor, 0, 1023, 0, 255);

	analogWrite(analog_out, skaliran);

	Serial.print("sensor = ");
	Serial.print(senzor);
	Serial.print("\t output = ");
	Serial.println(skaliran);
}

void setup()
{
	Serial.begin(9600);
	pinMode(analog_out, OUTPUT);
	createTask(potenciometar, 500, TASK_ENABLE, NULL);
}

void loop()
{

}
