/*
Dopuniti zadatak 1 sa sledećim funkcionalnostima:
- Kreirati funkciju enableInterrupt1() koja omogućuje korišćenje interapta za dugme BTN1.
- Kreirati funkciju disableInterrupt1() koja onemogućuje korišćenje interapta za dugme BTN1.
- Kreirati funkciju getInterrupatEnable1() koja vraća da li je omogućen prekid na dugmetu BTN1.
- Proširiti funkconalnost handler-a da podržava i dugme BTN2.
- Omogućiti da pri paljenju/gašenju dugmeta BTN2 bude 
  omogućeno/onemogućeno korišćenje interapta na dugmetu BTN1.
*/

typedef void (*interruptFunc) ();

#define BTN1 4
#define BTN2 34

int staro_stanje_1;
int novo_stanje_1;
interruptFunc dugme_rising_1;
interruptFunc dugme_falling_1;
int dugme_omoguceno_1;

int staro_stanje_2;
int novo_stanje_2;
interruptFunc dugme_rising_2;
interruptFunc dugme_falling_2;
int dugme_omoguceno_2;

void attachInterrupt_1(interruptFunc f, int mode)
{
	if (mode == RISING)
		dugme_rising_1 = f;
	else
		dugme_falling_1 = f;
}

void deattachInterrupt_1(int mode)
{
	if (mode == RISING)
		dugme_rising_1 = NULL;
	else
		dugme_falling_1 = NULL;
}

void interruptOn()
{
	digitalWrite(27, HIGH);
}

void interruptOff()
{
	digitalWrite(27, LOW);
}

void enableInterrupt_1()
{
	dugme_omoguceno_1 = true;
}

void disableInterrupt_1()
{
	dugme_omoguceno_1 = false;
}

void attachInterrupt_2(interruptFunc f, int mode)
{
	if (mode == RISING)
		dugme_rising_2 = f;
	else
		dugme_falling_2 = f;
}

void deattachInterrupt_2(int mode)
{
	if (mode == RISING)
		dugme_rising_2 = NULL;
	else
		dugme_falling_2 = NULL;
}

void enableInterrupt_2()
{
	dugme_omoguceno_2 = true;
}

void disableInterrupt_2()
{
	dugme_omoguceno_2 = false;
}

void dozvoliInterrupt_1()
{
	enableInterrupt_1();
}

void onemoguciInterrupt_1()
{
	disableInterrupt_1();
}

void dugme_1(int id, void* tptr)
{
	novo_stanje_1 = digitalRead(BTN1);

	if (dugme_omoguceno_1)
	{
		if (novo_stanje_1 == 1 && staro_stanje_1 == 0)
			if (dugme_rising_1 != NULL)
				(*dugme_rising_1)();
		else if (novo_stanje_1 == 0 && staro_stanje_1 == 1)
			if (dugme_falling_1 != NULL)
				(*dugme_falling_1)();
	}	

	staro_stanje_1 = novo_stanje_1;
}

void dugme_2(int id, void* tptr)
{
	novo_stanje_2 = digitalRead(BTN2);

	if (dugme_omoguceno_2)
	{
		if (novo_stanje_2 == 1 && staro_stanje_2 == 0)
			if (dugme_rising_2 != NULL)
				(*dugme_rising_2)();
		else if (novo_stanje_2 == 0 && staro_stanje_2 == 1)
			if (dugme_falling_2 != NULL)
				(*dugme_falling_2)();
	}

	staro_stanje_2 = novo_stanje_2;
}

void setup()
{
	pinMode(27, OUTPUT);
	digitalWrite(27, LOW);

	staro_stanje_1 = digitalRead(BTN1);
	staro_stanje_2 = digitalRead(BTN2);

	dugme_rising_1 = NULL;
	dugme_falling_1 = NULL;
	dugme_rising_2 = NULL;
	dugme_falling_2 = NULL;

	if (staro_stanje_2 == 0)
		onemoguciInterrupt_1();
	else
		dozvoliInterrupt_1();

	enableInterrupt_2();

	attachInterrupt_1(interruptOn, RISING);
	attachInterrupt_1(interruptOff, FALLING);

	attachInterrupt_2(dozvoliInterrupt_1, RISING);
	attachInterrupt_2(onemoguciInterrupt_1, FALLING);

	createTask(dugme_1, 20, TASK_ENABLE, NULL);
	createTask(dugme_2, 20, TASK_ENABLE, NULL);
}

void loop()
{

}
