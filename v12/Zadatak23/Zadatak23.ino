#define LED_8 33

int blink1_id, blink2_id;
unsigned int brLampica;

void blink1_task(int id, void * tptr)
{
    digitalWrite(LED_8, !digitalRead(LED_8));
}

void blink2_task(int id, void * tptr)
{
    brLampica = 0;
	
    if (digitalRead(2))  brLampica++;
    if (digitalRead(7))  brLampica++;
    if (digitalRead(8))  brLampica++;
    if (digitalRead(35)) brLampica++;

    setTaskPeriod(blink1_id, ++brLampica * 100);
}

void setup()
{
    pinMode(LED_8, OUTPUT);

    // ovo ne mora jer se ovi pinovi podrazumevaju kao INPUT
    pinMode(2,  INPUT);
    pinMode(7,  INPUT);
    pinMode(8,  INPUT);
    pinMode(35, INPUT);

    blink1_id = createTask(blink1_task,  100, TASK_ENABLE, NULL);
    blink2_id = createTask(blink2_task, 1000, TASK_ENABLE, NULL);
}

void loop()
{

}
