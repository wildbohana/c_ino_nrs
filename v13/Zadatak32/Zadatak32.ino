#define PIN_BTN1 4

int staroStanje, staroVreme, brojac;

void dugme1(int id, void * tptr)
{
    int novoStanje = digitalRead(PIN_BTN1);

	if (staroStanje == 1  && novoStanje == 0) 
	{
        if (millis()-staroVreme >= 2000) 
		{
            brojac++;
            Serial.println(brojac);
		}
	} 
	else if (staroStanje == 0 && novoStanje == 1) 
	{
        staroVreme = millis();
	}

	staroStanje = novoStanje;
}

void setup()
{
    Serial.begin(9600);	
    staroStanje = digitalRead(PIN_BTN1);

    staroVreme = millis();
    brojac = 0;

    createTask(dugme1, 50, TASK_ENABLE, NULL);
}

void loop()
{

}

