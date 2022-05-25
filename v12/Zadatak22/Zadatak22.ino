/*
Kreirati program koji koristeći task blink_task1 pali i gasi lampicu LED8 
na pinu 33 u zavisnosti od dugmeta BTN4 na pinu 37.

- Pratiti stanje dugmeta BTN4 i otkriti da li je stisnut duže od 2 sekunde. 
  Po uočavanju ovakvog događaja, na silaznoj ivici programski resetovati ploču uc32.
- Koristiti primitive millis i executeSoftReset.
- Promenu stanja dugmeta pratiti na svakih 50 ms i ukoliko je stanje 
  različito od prethodnog, prepoznati promenu stanja.
*/

#define LED8 33
#define BTN4 37

int blink1_id;

void blink_task1(int id, void *tptr)
{
	static int pocetno_vreme = millis();
	static int period = 0;

	int dugme = digitalRead(BTN4);

	if (dugme == HIGH)
	{
		digitalWrite(LED8, HIGH);
		period = millis() - pocetno_vreme;
	}
	else
	{
		digitalWrite(LED8, LOW);

		if (period > 2000)
		{
			executeSoftReset(RUN_SKETCH_ON_BOOT);
		}
		else
		{
			pocetno_vreme = millis();
			period = 0;
		}
	}
}

void setup()
{
	pinMode(LED8, OUTPUT);
	
	blink1_id = createTask(blink_task1, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
