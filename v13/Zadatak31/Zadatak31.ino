/*
Napisati program koji koristeći task blink_task1() pali i gasi led diodu 
LED1 na pinu 26 na svakih 100 milisekundi. 
Nakon toga:
- Napisati task prekidac1() koji se pali na svakih 50 ms i proverava 
  stanje prekidača SW1 na pinu 2. Ukoliko je prekidač upravo upaljen, 
  omogućiti korišćenje taska blink_task1, a ukoliko je upravo ugašen, onemogućiti ga.
- Napisati task prekidac2() koji se pali na svakih 50 ms i proverava 
  stanje prekidača SW2 na pinu 7. Ukoliko je prekidač upravo upaljen, 
  promeniti vreme blinkanja taska blink_task1 na 1000 ms, a ukoliko je upravo ugašen na 100ms.
*/

#define LED1 26
#define SW1 2
#define SW2 7

int blink1_id;
int staro_stanje1;
int staro_stanje2;

void blink_task1(int id, void* tptr)
{
	digitalWrite(LED1, !digitalRead(LED1));
}

void prekidac1(int id, void* tptr)
{
	int novo_stanje = digitalRead(SW1);

	if (novo_stanje == 1 && staro_stanje1 == 0)
		setTaskState(blink1_id, TASK_ENABLE);
	else if (novo_stanje == 0 && staro_stanje1 == 1)
		setTaskState(blink1_id, TASK_DISABLE);

	staro_stanje1 = novo_stanje;
}

void prekidac2(int id, void* tptr)
{
	int novo_stanje = digitalRead(SW2);

	if (novo_stanje == 1 && staro_stanje2 == 0)
		setTaskPeriod(blink1_id, 1000);
	else if (novo_stanje == 0 && staro_stanje2 == 1)
		setTaskPeriod(blink1_id, 100);

	staro_stanje2 = novo_stanje;
}

void setup()
{
	pinMode(LED1, OUTPUT);

	staro_stanje1 = digitalRead(SW1);
	staro_stanje2 = digitalRead(SW2);

	if (staro_stanje1 == 1)
		blink1_id = createTask(blink_task1, 100, TASK_ENABLE, NULL);
	else
		blink1_id = createTask(blink_task1, 100, TASK_DISABLE, NULL);

	createTask(prekidac1, 50, TASK_ENABLE, NULL);
	createTask(prekidac2, 50, TASK_ENABLE, NULL);
}

void loop()
{
	
}

