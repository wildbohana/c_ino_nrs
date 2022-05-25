/*
Napisati program koji:
- Inicijalno postavlja sve lampice kao izlazne pinove, gasi ih i inicijalizuje 
  komunikaciju sa serijskim ulazom/izlazom na bit rate 9600. Na serijskom izlazu 
  ispisati ime, prezime i broj indeksa. Kreirati globalnu promenljivu x1 i 
  inicijalizovati je na 0.
- Sadrži funkciju fun1() koja proverava stanje potenciometra A0 i ispisuje njegovo 
  stanje na lampicama na pinovima 26-33, srazmerno jačini učitanog podatka. Funkcija 
  vraća broj upaljenih lampica.
- Kreira task task1() sa periodom od 40 ms, koji proverava stanje potenciometra i 
  ispisuje ga na diodama koristeći funkciju fun1(). Osim toga, task proverava i da li 
  je upravo pritisnuto dugme BTN1 (pin4) i ukoliko je upravo pritisnuto resetuje 
  stanje promenljive x1 na 0. Ukoliko je upravo pritisnuto dugme BTN2 (pin 34), tada 
  se promenljiva x1 uvećava za broj upaljenih lampica.
- Kreira interapt vezan za prekidač SW1 koji pri njegovom paljenju ispisuje vrednost 
  promenljiva x1 na serijski monitor.
- Kreira task task2() sa periodom 50 ms koji proverava stanje dugmeta BTN4 na pinu 37
  i ukoliko je bilo pritisnuto duže od 5 sekundi, resetuje celu pločicu.
*/

#define analog_in A0
#define BTN1 4
#define BTN2 34
#define BTN4 37

int x1;
int staro_stanje1;
int staro_stanje2;
int staro_stanje4;
int staro_vreme;

// 2.
int fun1()
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

	return br_lampica;
}

// 3.
void task1(int id, void* tptr)
{
	int broj_lamp = fun1();

	int novo_stanje1 = digitalRead(BTN1);
	int novo_stanje2 = digitalRead(BTN2);

	if (staro_stanje1 == 0 && novo_stanje1 == 1)
	{
		x1 = 0;
	}

	if (staro_stanje2 == 0 && novo_stanje2 == 1)
	{
		x1 += broj_lamp;
	}

	staro_stanje1 = novo_stanje1;
	staro_stanje2 = novo_stanje2;
}

// 4.
void prekidac()
{
	Serial.println(x1);
}

// executeSoftReset(RUN_SKETCH_ON_BOOT);

// 5. 
void task2(int id, void* tptr)
{
	int novo_stanje4 = digitalRead(BTN4);

	if (staro_stanje4 == 0 && novo_stanje4 == 1)
	{
		staro_vreme = millis();
	}
	else if (staro_stanje4 == 1 && novo_stanje4 == 0)
	{
		if (millis() - staro_vreme >= 5000)
			 executeSoftReset(RUN_SKETCH_ON_BOOT);
	}

	staro_stanje4 = novo_stanje4;
}

void setup()
{
	// 1.
	Serial.begin(9600);

	for (int i = 26; i < 34; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}

	Serial.println("Bojana Mihajlovic, PR83/2020");

	x1 = 0;

	// 2. i 3.
	staro_stanje1 = digitalRead(BTN1);
	staro_stanje2 = digitalRead(BTN2);
	createTask(task1, 40, TASK_ENABLE, NULL);

	// 4.
	attachInterrupt(1, prekidac, RISING);

	// 5.
	staro_stanje4 = digitalRead(BTN4);
	createTask(task2, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
