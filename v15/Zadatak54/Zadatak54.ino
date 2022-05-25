/*
Napisati program koji sa potenctiometra čita vrednost ulaza na svakih 
100ms i proverava da li je došlo do naglog skoka ulaznog signala i o 
tome obaveštava korisnika putem serijskog porta. Do naglog skoka dolazi 
ukoliko se u poslednjih 5 merenja vrednost signala promenila za više od 200.
*/
const int analog_in = A0;

int merenja[5] = {0};
int brojac = 0;

void potenciometar(int id, void* tptr)
{
	int nova_jacina = analogRead(analog_in);
	merenja[brojac] = nova_jacina;

	int maksimum = merenja[0];
	int minimum = merenja[0];

	for (int i = 1; i < 5; i++)
	{
		if (merenja[i] < minimum)
			minimum = merenja[i];
		
		if (merenja[i] > maksimum)
			maksimum = merenja[i];
	}

	if (abs(maksimum - minimum) > 200)
		Serial.println("Doslo je do naglog skoka!\n");

	// bro but like, this would be array of all the same values, we could have easily used just one variable for this ???
	for (int i = 0; i < 5; i++)
		merenja[i] = nova_jacina;

    // brojac = (brojac + 1) % 5;
	if (++brojac == 5) brojac = 0;
}

void setup()
{
	Serial.begin(9600);
	createTask(potenciometar, 100, TASK_ENABLE, NULL);
}

void loop()
{

}
