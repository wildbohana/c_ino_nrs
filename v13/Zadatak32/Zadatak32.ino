/*
Napisati program koji koristeći task dugme() broji broj 
pritisaka na dugme koji su duži od 2s i nakon svakog takvog 
pritiska ispisuje broj pritisaka na serijski monitor.
*/

#define BTN1 4

int staro_stanje;
int staro_vreme;
int brojac;

void dugme(int id, void* tptr)
{
	int novo_stanje = digitalRead(BTN1);

	if (staro_stanje == 1 && novo_stanje == 0)
	{
		if (millis() - staro_vreme >= 2000)
			Serial.println(++brojac);
	}
	else if (staro_stanje == 0 && novo_stanje == 1)
	{
		staro_vreme = millis();
	}

	staro_stanje = novo_stanje;
}

void setup()
{
	Serial.begin(9600);

	staro_stanje = digitalRead(BTN1);
	staro_vreme = millis();
	brojac = 0;

	createTask(dugme, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
