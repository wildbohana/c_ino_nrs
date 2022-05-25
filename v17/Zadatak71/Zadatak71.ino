/*
Napisati program koji:
- Postavlja lampicu na pinu 26 kao izlazni pin i inicijalizuje komunikaciju 
  sa serijskim monitorom na 9600bps.
- Sadrži globalnu promenljivu br koja može da ima vrednosti od 1 do 10.
  Inicijalna vrednost promenljive je 1. Postavlja task koji pali i gasi 
  lampicu na pinu 26. Broj blinkanja u jednoj sekundi treba da bude 
  jednak broju br.
- Prilikom pritiska na dugme na pinu 4 ispisuje period blinkanja lampice na 
  serijski monitor. Prilikom puštanja dugmeta na pinu 4 menja frekvenciju 
  blinkanja na vrednost br.
- Sadrži interapte vezane za prekidač 1 (pin 2) koji pri promeni stanja 
  prekidača povećavaju vrednost promenljive br. Ukoliko br pređe vrednost
  10, postaviti vrednost na 1. Promenu prepoznati koristeći 2 uvezana 
  interapta sa različitim modovima paljenja.
- Napraviti task koji prati stanje na serijskom monitoru i ukoliko je 
  učitan znak od 0 do 9, u promenljivu br postavlja vrednost znaka uvećanu
  za 1 i menja period blinkanja lampice srazmeran broju br.
*/

#define LED1 26
#define BTN1 4
#define SW1 2

int staro_stanje;
int br;
int lampica_id;

// 4.
void interruptOn();
void interruptOff();

// 2.
void lampica(int id, void* tptr)
{
	digitalWrite(LED1, !digitalRead(LED1));
}

// 3.
void dugme(int id, void* tptr)
{
	int novo_stanje = digitalRead(BTN1);

	if (novo_stanje == 1 && staro_stanje == 0)
	{
		setTaskPeriod(lampica_id, 1000 / (2 * br));
	}
	else if (novo_stanje == 0 && staro_stanje == 1)
	{	
		Serial.print("period: ");
		Serial.println(1000 / (2 * br));
	}

	staro_stanje = novo_stanje;
}

// 4.
void interruptOn(int id, void* tptr)
{
	if (++br > 10) br = 1;

	detachInterrupt(1);
	attachInterrupt(1, interruptOff, RISING);
}

void interruptOff(int id, void* tptr)
{
	if (++br > 10) br = 1;

	detachInterrupt(1);
	attachInterrupt(1, interruptOn, FALLING);
}

// 5.
void serijskiMonitor(int id, void* tptr)
{
	if (Serial.available())
	{
		char c = Serial.read();

		if ('0' <= c && c <= '9')
		{
			br = c - '0' + 1;
			setTaskPeriod(lampica_id, 1000 / (2 * br));
		}
	}
}

void setup()
{
	// 1.
	Serial.begin(9600);

	pinMode(LED1, OUTPUT);
	digitalWrite(LED1, LOW);

	// 2.
	br = 1;
	lampica_id = createTask(lampica, 1000 / (br * 2), TASK_ENABLE, NULL);

	// 3.
	staro_stanje = digitalRead(BTN1);
	createTask(dugme, 50, TASK_ENABLE, NULL);

	// 4.
	if (digitalRead(SW1))
		attachInterrupt(1, interruptOn, FALLING);
	else
		attachInterrupt(1, interruptOff, RISING);

	// 5.
	createTask(serijskiMonitor, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
