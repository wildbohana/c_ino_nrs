void kopiranje(int id, void * tptr) 
{
	static int na_redu_je = 0;
	static int prvi;
	static int drugi;

	if (na_redu_je == 0)
	{
		if (Serial.available())
		{
			const char* sabirak1 = Serial.readString().c_str();
			prvi = atoi(sabirak1);
			na_redu_je = 1;
		}
	}
	else
	{
		if (Serial.available())
		{
			const char* sabirak2 = Serial.readString().c_str();
			drugi = atoi(sabirak2);
			Serial.println(prvi + drugi);
			na_redu_je = 0;
		}
	}
}

void setup()
{
  	Serial.begin(9600);
  	createTask(kopiranje, 1000, TASK_ENABLE, NULL);
}

void loop()
{

}
