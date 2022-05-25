/*
Napisati program koji pri pritisku dugmeta BTN1 (pin 4) pali lampicu 
LD2 (pin 27), a pri puštanju dugmeta BTN1, gasi lampicu LD2.
- Paljenje i gašenje lampice realizovati preko preko interapta povezanih na dugme BTN1.
- Kako dugmadi nisu podrzana u interaptima, kreirati kompletan handler 
  za dugme BTN1, koji podrazumeva i funkcije attachInterrupt1() i 
  deattachInterrupt1() slične postojećim funkcijama.
*/

typedef void (*interruptFunc) ();

#define BTN1 4

int staro_stanje;
int novo_stanje;
interruptFunc dugme_rising;
interruptFunc dugme_falling;

void attachInterrupt(interruptFunc f, int mode)
{
	if (mode == RISING)
		dugme_rising = f;
	else
		dugme_falling = f;
}

void deattachInterrupt(int mode)
{
	if (mode == RISING)
		dugme_rising = NULL;
	else
		dugme_falling = NULL;
}

void interruptOn()
{
	digitalWrite(27, HIGH);
}

void interruptOff()
{
	digitalWrite(27, LOW);
}

void dugme(int id, void* tptr)
{
	novo_stanje = digitalRead(BTN1);

	if (novo_stanje == 1 && staro_stanje == 0)
		if (dugme_rising != NULL)
			(*dugme_rising)();
	else if (novo_stanje == 0 && staro_stanje == 1)
		if (dugme_falling != NULL)
			(*dugme_falling)();

	staro_stanje = novo_stanje;
}

void setup()
{
	pinMode(27, OUTPUT);
	digitalWrite(27, LOW);

	staro_stanje = digitalRead(BTN1);

	dugme_rising = NULL;
	dugme_falling = NULL;

	attachInterrupt(interruptOn, RISING);
	attachInterrupt(interruptOff, FALLING);

	createTask(dugme, 20, TASK_ENABLE, NULL);
}

void loop()
{
	
}
