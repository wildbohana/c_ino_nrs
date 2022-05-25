/*
Napisati program koji:
- Postavlja lampice na pinovima 26-33 kao izlazne pinove i inicijalizuje 
  komunikaciju sa serijskim monitorom na 9600bps.
- Sadrži promenljivu br, inicijalno postavljenu na 0 u kojoj će biti 
  sumirane vrednosti sa analognog ulaza A0.
- Sadrži task koji prilikom pritiska na dugme na pinu 4, ukoliko je dugme 
  držano duže od 2 sekunde, povećava vrednost brojača br za vrednost
  pročitanu sa analognog ulaza A0 i ispisuje brojač na serijski monitor.
- Sadrži interapt koji se startuje pri paljenju prekidača na pinu 2, čita 
  vrednost analognog ulaza, skalira je na vrednost od 0 do 255 i dobijeni 
  broj prikazuje na lampicama 26-33 u binarnom obliku.
- Sadrži task koji učitava broj sa serijskog monitora, ukoliko postoji, i 
  ukoliko je taj broj manji od brojača br, onemogućuje task za kontrolu 
  dugmeta iz stavke 3. Ispisati odgovarajuću poruku na serijski izlaz.
*/

#define LED1 26
#define analog_in A0
#define BTN1 4
#define SW1 2

int br;
int dugme_id;
int staro_stanje;
int staro_vreme;

// 2. i 3.
void dugme(int id, void* tptr)
{
	int novo_vreme = millis();
	int novo_stanje = digitalRead(BTN1);
	
	if (novo_stanje == 1 && staro_stanje == 0)
	{
		if (millis() - staro_vreme >= 2000)
		{
			int senzor = analogRead(analog_in);
			br += senzor;
			Serial.println(br);
		}
	}
	else if (novo_stanje == 0 && staro_stanje == 1)
	{
		staro_vreme = millis();
	}

	staro_stanje = novo_stanje;
}

// 4.
void prekidac()
{
	int senzor = analogRead(analog_in);
	int skaliran = map(senzor, 0, 1023, 0, 255);

	for (int i = 26; i < 34; i++)
	{
		digitalWrite(i, skaliran % 2);
		skaliran /= 2;
	}
}

// 5.
void serijskiMonitor(int id, void* tptr)
{
	if (Serial.available())
	{
		const char* s = Serial.readString().c_str();
		int x = atoi(s);

		if (x < br)
		{
			setTaskState(dugme_id, TASK_DISABLE);
			Serial.println("Task onemogucen");
		}
		else
		{
			Serial.println("Task nije onemogucen");
		}
	}
}

void setup()
{
	// 1.
	Serial.begin(9600);
	for (int i = 0; i < 8; i++)
		pinMode(LED1 + i, OUTPUT);

	// 2.
	br = 0;

	// 3.
	staro_vreme = millis();
	dugme_id = createTask(dugme, 50, TASK_ENABLE, NULL);

	// 4.
	attachInterrupt(1, prekidac, RISING);

	// 5.
	createTask(serijskiMonitor, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
