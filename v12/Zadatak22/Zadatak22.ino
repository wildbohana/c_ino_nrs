#define PIN_LED1 33
#define PIN_BTN4 37

int blink1_id, blink2_id;
unsigned long blink1_var;

unsigned short stat2 = TASK_DISABLE;
unsigned long period1, period2;

void blink_task1(int id, void * tptr)
{
	static int startTime = millis();
	static int period = 0;

	int BTN4 = digitalRead(PIN_BTN4);

	if (BTN4 == HIGH) 
	{
		digitalWrite(PIN_LED1, HIGH);
		period = millis() - startTime;
	} 
	else 
	{
		digitalWrite(PIN_LED1, LOW);
		
		if (period > 2000)
		{
			executeSoftReset(RUN_SKETCH_ON_BOOT);
		}
		else 
		{
			startTime = millis();
			period = 0;
		}
	}
}

void setup()
{
	pinMode(PIN_LED1, OUTPUT);

	blink1_id = createTask(blink_task1, 50, TASK_ENABLE, &blink1_var);
}

void loop()
{

}

