const int analogInPin = A0;

#define PWM_BIT_TIME 6
#define PWM_PERIOD (PWM_BIT_TIME * 1024)

void potenciometar(int id, void * tptr)
{
    for (int i = 26; i < 34; i++)
        digitalWrite(i, LOW);

    int jacina = analogRead(analogInPin);
    int brojLampica = map(jacina, 0, 1023, 0, 8);

    for (int i = 0; i < brojLampica ; i++)
        digitalWrite(26 + i, HIGH);
}

void setup()
{
    Serial.begin(9600);

    for (int i = 26; i < 34; i++)
        pinMode(i, OUTPUT);

	// nije obavezno
	pinMode(analogInPin, INPUT);

    createTask(potenciometar, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
