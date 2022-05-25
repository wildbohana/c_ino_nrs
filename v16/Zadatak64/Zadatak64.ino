/*
Napisati program koji na svakih 1s učitava binarni broj koji 
formiraju prekidaci na pinovima 25, 8, 7 i 2m prebacuje ga u 
dekadni i ispisuje taj broj na serijskom monitoru u dekadnom sistemu.
- Na primer, ako su upaljeni samo prekidači na pinovima 8 i 2, 
  tada oni čine broj 0101 u osnovi 2, što je broj 5.
*/

void ispis(int id, void* tptr) 
{
	int broj = 0;

	if (digitalRead(2))  broj += 1;
	if (digitalRead(7))  broj += 2;
	if (digitalRead(8))  broj += 4;
	if (digitalRead(35)) broj += 8;
  	
	Serial.println(broj);
}

void setup()
{
  	Serial.begin(9600);
  	createTask(ispis, 1000, TASK_ENABLE, NULL);
}

void loop()
{

}
