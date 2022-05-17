// definisemo pokazivac na funkciju tipa void bez parametara
typedef void (*interruptFunc) ();

// definisemo promenljive za rad sa interaptom za dugme BTN1
int BTN1 = 4;
int BTN1_old_state;
int BTN1_new_state;
interruptFunc BTN1_f_rising;
interruptFunc BTN1_f_falling;
int BTN1_enabled;

// definisemo promenljive za rad sa interaptom za dugme BTN2
int BTN2 = 34;
int BTN2_old_state;
int BTN2_new_state;
interruptFunc BTN2_f_rising;
interruptFunc BTN2_f_falling;
int BTN2_enabled;

// postavljanje interapta za dugme1
void attachInterupt1(interruptFunc f, int mode)
{
	if (mode == RISING)
		BTN1_f_rising = f;
	else
		BTN1_f_falling = f;
}

// uklanjanje interapta za dugme1
void deattachInterupt1(int mode)
{
	if (mode == RISING)
		BTN1_f_rising = NULL;
	else
		BTN1_f_falling = NULL;
}

// funkcija koja pali lampicu 27
void myInterruptOn()
{
	digitalWrite(27, HIGH);
}

// funkcija koja gasi lampicu 27
void myInterruptOff()
{
	digitalWrite(27, LOW);
}

void enableInterrupt1()
{
	BTN1_enabled = true;
}

void disableInterrupt1()
{
	BTN1_enabled = false;
}

// postavljanje interapta za dugme2
void attachInterupt2(interruptFunc f, int mode)
{
	if (mode == RISING)
		BTN2_f_rising = f;
	else
		BTN2_f_falling = f;
}

// uklanjanje interapta za dugme2
void deattachInterupt2(int mode)
{
	if (mode == RISING)
		BTN2_f_rising = NULL;
	else
		BTN2_f_falling = NULL;
}

void enableInterrupt2()
{
	BTN2_enabled = true;
}

void disableInterrupt2()
{	
	BTN2_enabled = false;
}

void myInterrupt1Enable()
{
   enableInterrupt1();
}

void myInterrupt1Disable()
{
   disableInterrupt1();
}

void dugme(int id, void * tptr)
{
	BTN1_new_state = digitalRead(BTN1);

	if (BTN1_enabled) 
	{
		if (BTN1_new_state == 1 && BTN1_old_state == 0)
		{
			if (BTN1_f_rising != NULL)
				(*BTN1_f_rising)();
		} 
		else if (BTN1_new_state == 0 && BTN1_old_state == 1)
		{
			if (BTN1_f_falling != NULL)
				(*BTN1_f_falling)();
		}
	}

	BTN1_old_state = BTN1_new_state;
}

void dugme2(int id, void * tptr)
{
	BTN2_new_state = digitalRead(BTN2);

	if (BTN2_enabled) 
	{
		if (BTN2_new_state == 1 && BTN2_old_state == 0)
		{
			if (BTN2_f_rising != NULL)
				(*BTN2_f_rising)();
		} 
		else if (BTN2_new_state == 0 && BTN2_old_state == 1)
		{
			if (BTN2_f_falling != NULL)
				(*BTN2_f_falling)();
		}
	}

	BTN2_old_state = BTN2_new_state;
}

void setup() 
{
	pinMode(27, OUTPUT);
	digitalWrite(27, LOW);

	BTN1_old_state = digitalRead(BTN1);
	BTN2_old_state = digitalRead(BTN2);

	BTN1_f_rising = NULL;
	BTN1_f_falling = NULL;
	
	if (BTN2_old_state == 0) 
		disableInterrupt1();
	else 
		enableInterrupt1();

	BTN2_f_rising = NULL;
	BTN2_f_falling = NULL;
	
	enableInterrupt2();

	attachInterupt1(myInterruptOn, RISING);
	attachInterupt1(myInterruptOff, FALLING);

	attachInterupt2(myInterrupt1Enable, RISING);
	attachInterupt2(myInterrupt1Disable, FALLING);

	createTask(dugme,  20, TASK_ENABLE, NULL);
	createTask(dugme2, 20, TASK_ENABLE, NULL);
}

void loop() {

}
