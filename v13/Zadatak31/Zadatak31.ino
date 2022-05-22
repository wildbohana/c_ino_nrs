#define PIN_SW1 2
#define PIN_SW2 7
#define PIN_LED1a 26

int staroStanje1, staroStanje2, blink1_id;

void blink_task1(int id, void * tptr)
{
	digitalWrite(PIN_LED1a, !digitalRead(PIN_LED1a));
}

void prekidac1(int id, void * tptr)
{
    int novoStanje = digitalRead(PIN_SW1);

	if (staroStanje1 == 1 && novoStanje == 0)
        setTaskState(blink1_id, TASK_DISABLE);
	else if (staroStanje1 == 0 && novoStanje == 1)
        setTaskState(blink1_id, TASK_ENABLE);
	
	staroStanje1 = novoStanje;
}

void prekidac2(int id, void * tptr)
{
    int novoStanje = digitalRead(PIN_SW2);

	if (staroStanje2 == 1 && novoStanje == 0)
        setTaskPeriod(blink1_id, 100);
	else if (staroStanje2 == 0 && novoStanje == 1)
        setTaskPeriod(blink1_id, 1000);
	
	staroStanje2 = novoStanje;
}

void setup()
{
    pinMode(PIN_LED1a, OUTPUT);
    staroStanje1 = digitalRead(PIN_SW1);
    staroStanje2 = digitalRead(PIN_SW2);

    if (staroStanje1 == 1)
        blink1_id = createTask(blink_task1, 100, TASK_ENABLE, NULL);
    else
        blink1_id = createTask(blink_task1, 100, TASK_DISABLE, NULL);
		
    createTask(prekidac1, 50, TASK_ENABLE, NULL);
    createTask(prekidac2, 50, TASK_ENABLE, NULL);
}

void loop()
{

}

