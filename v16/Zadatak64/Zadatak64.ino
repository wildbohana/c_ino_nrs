void ispis(int id, void * tptr) 
{
	int broj = 0;

	if (digitalRead(35)) broj += 8;
	if (digitalRead(8))  broj += 4;
	if (digitalRead(7))  broj += 2;
	if (digitalRead(2))  broj += 1;
   	
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
