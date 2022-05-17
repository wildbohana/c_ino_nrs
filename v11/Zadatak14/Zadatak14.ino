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

    int pin2  = digitalRead(2);
    int pin7  = digitalRead(7);
    int pin8  = digitalRead(8);
    int pin35 = digitalRead(35);

    int LED_NUM = 0;

    if (pin2)  cnt++;
    if (pin7)  cnt++;
    if (pin8)  cnt++;
    if (pin35) cnt++;

    LED_NUM = cnt * 2;

    for (int i = 0; i < LED_NUM; i++)
        digitalWrite(LED_1 + i, HIGH);

    delay(1000);

    for (int i = 0; i < 8; i++)
        digitalWrite(LED_1 + i, LOW);
}
