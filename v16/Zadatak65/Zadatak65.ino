/*
Napisati program koji učitava dva broja sa serijskog ulaza, 
sabira ih i ispisuje njihov zbir.
*/

void sabiranje(int id, void* tptr) 
{
	static int na_redu_je = 1;
	static int prvi, drugi;

	if (na_redu_je == 1)
	{
		if (Serial.available())
		{
			const char* sabirak1 = Serial.readString().c_str();
			prvi = atoi(sabirak1);
			na_redu_je = 2;
		}
	}
	else
	{
		if (Serial.available())
		{
			const char* sabirak2 = Serial.readString().c_str();
			drugi = atoi(sabirak2);
			Serial.println(prvi + drugi);
			na_redu_je = 1;
		}
	}
}

void setup()
{
  	Serial.begin(9600);
  	createTask(sabiranje, 1000, TASK_ENABLE, NULL);
}

void loop()
{

}
