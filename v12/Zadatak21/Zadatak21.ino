/*
Napisati program koji pali i gasi led diode LED8 i LED2 na pinovima 33 i 27 
na svakih 500, odnosno 25 milisekundi. 
Kreirati dva task-a, blink_task1 i blink_task2, za svaku lampicu po jedan. 
Nakon toga, kreirati task blink_task3 koja omogućuje/onemogućuje task 
blink_task2 u zavisnosti od stanja prekidača SW2.
*/

#define LED8 33
#define LED2 27
#define SW2 7

int blink1_id;
int blink2_id;

int stat2 = TASK_DISABLE;

void blink_task1(int id, void* tptr)
{
	digitalWrite(LED8, !digitalRead(LED8));
}

void blink_task2(int id, void* tptr)
{
	digitalWrite(LED2, !digitalRead(LED2));
}

void blink_task3(int id, void* tptr)
{
	stat2 = getTaskState(blink2_id);

	if (digitalRead(SW2))
	{
		if (stat2 == TASK_DISABLE)
		{
			setTaskPeriod(blink2_id, 100);
			setTaskState(blink2_id, TASK_ENABLE);
		}
	}
	else
	{
		if (stat2 == TASK_ENABLE)
		{
			setTaskState(blink2_id, TASK_DISABLE);
			digitalWrite(LED2, LOW);
		}
	}
}

void setup()
{
	pinMode(LED2, OUTPUT);
	pinMode(LED8, OUTPUT);

	blink1_id = createTask(blink_task1, 500, TASK_ENABLE, NULL);
	blink2_id = createTask(blink_task2, 25, stat2, NULL);
	createTask(blink_task3, 1000, TASK_ENABLE, NULL);
}

void loop()
{

}
