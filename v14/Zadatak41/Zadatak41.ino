// pokazivac na funkciju tipa void bez parametara
typedef void (*interruptFunc) ();

// promenljive za rad sa prekidom za dugme BTN1
int BTN1 = 4;
int BTN1_old_state;
int BTN1_new_state;
interruptFunc BTN1_f_rising;
interruptFunc BTN1_f_falling;

// pravljenje prekida za dugme1
void attachInterupt1(interruptFunc f, int mode)
{
	if (mode == RISING) 
		BTN1_f_rising = f;
	else 
		BTN1_f_falling = f;
}

// uklanjanje prekida za dugme1
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

void dugme(int id, void * tptr)
{
	BTN1_new_state = digitalRead(BTN1);

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

	BTN1_old_state = BTN1_new_state;
}

void setup() 
{
	pinMode(27, OUTPUT);
	digitalWrite(27, LOW);

	BTN1_old_state = digitalRead(BTN1);

	BTN1_f_rising = NULL;
	BTN1_f_falling = NULL;

	attachInterupt1(myInterruptOn, RISING);
	attachInterupt1(myInterruptOff, FALLING);

	createTask(dugme, 20, TASK_ENABLE, NULL);
}

void loop() 
{

}
