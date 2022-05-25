/*
Napisati program koji koristeći task blink_task1 pali i gasi led diodu 
LD8 na pinu 33 na svakih 100 milisekundi. Kreirati i task blink_task2, 
koji na svakih 25 milisekundi proverava stanje prekidača na pinovima 
2, 7, 8, i 35, broji koliko ima upaljenih prekidača i u zavisnosti od toga, 
postavlja period blinkanja lampice LD8 na 100, 200, 300, 400 ili 500ms. 
Period blinkanja menjati periodom na koji se startuje blink_task1
*/

#define LED8 33

int blink1_id;
int br_lampica;

void blink_task1(int id, void * tptr)
{
    digitalWrite(LED8, !digitalRead(LED8));
}

void blink_task2(int id, void * tptr)
{
    br_lampica = 0;
	
    if (digitalRead(2))  br_lampica++;
    if (digitalRead(7))  br_lampica++;
    if (digitalRead(8))  br_lampica++;
    if (digitalRead(35)) br_lampica++;

    setTaskPeriod(blink1_id, ++br_lampica * 100);
}

void setup()
{
	// pinovi 2, 7, 8, 35 se podrazumevaju kao input
    pinMode(LED8, OUTPUT);

    blink1_id = createTask(blink_task1, 100, TASK_ENABLE, NULL);
    createTask(blink_task2, 1000, TASK_ENABLE, NULL);
}

void loop()
{

}
