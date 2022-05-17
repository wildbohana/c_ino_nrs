#define LED_1 26

void setup()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(LED_1 + i, OUTPUT);
        digitalWrite(LED_1 + i, LOW);
    }

    Serial.begin(9600);
}

void loop()
{
    int cnt = 0;
    int brzina;
    int pin7 = digitalRead(7);

    if (pin7) brzina = 1000;
    else brzina = 200;

    for (int i = 0; i < 8; i++)
    {
        if (i < 4)
        {
            digitalWrite(LED_1 + i, HIGH);
            digitalWrite(LED_1 + 7 - i, HIGH);
            delay(brzina);
            digitalWrite(LED_1 + i, LOW);
            digitalWrite(LED_1 + 7 - i, LOW);
        }
        else
        {
            cnt += 2;

            digitalWrite(LED_1 + i - cnt, HIGH);
            digitalWrite(LED_1 + 7 - i + cnt, HIGH);
            delay(brzina);
            digitalWrite(LED_1 + i - cnt, LOW);
            digitalWrite(LED_1 + 7 - i + cnt, LOW);
        }
    }
}
