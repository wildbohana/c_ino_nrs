/*
Napisati program koji koristeći task blink_task1 proverava stanje 
na prekidaču i ukoliko je prekidač upaljen, upaliti lampicu, 
a ukoliko je prekidač ugašen, ugasiti lampicu. 
Redni broj prekidača i lampice primiti kao parametar. 
Koristeći dati task, kontrolisati lampice na pinovima 26, 27, 28 i 29 
u zavisnosti od stanja na prikidačima na pinovima 2, 7, 8 i 35.
*/

typedef struct {
    int led;
	int sw;
} Struktura;

Struktura s1, s2, s3, s4;

void blink_task1(int id, void * tptr)
{
    Struktura* s = (Struktura*) tptr;

    if (digitalRead(s->sw)) 
		digitalWrite(s->led, HIGH);
    else 
		digitalWrite(s->led, LOW);
}

void setup()
{
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(28, OUTPUT);
    pinMode(29, OUTPUT);

    s1.led = 26; s1.sw = 2;
    s2.led = 27; s2.sw = 7;
    s3.led = 28; s3.sw = 8;
    s4.led = 29; s4.sw = 35;

    createTask(blink_task1, 100, TASK_ENABLE, &s1);
    createTask(blink_task1, 100, TASK_ENABLE, &s2);
    createTask(blink_task1, 100, TASK_ENABLE, &s3);
    createTask(blink_task1, 100, TASK_ENABLE, &s4);
}

void loop()
{

}
