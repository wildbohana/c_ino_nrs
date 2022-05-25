/*
Napisati program koji pali lampice na pinovima od 26 do 33, tako 
što prvo pali lampice 26 i 33, zatim 27 i 32, itd... sve dok se 
lampice ne sudare. Nakon toga, lampice paliti u obrnutom redosledu, 
pa sve ponavljati. U zavisnosti od stanja prekidača SW na pinu 7, 
podesiti jednu od dve brzine rotacije.
*/

#define LED1 26

void setup()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(LED1 + i, OUTPUT);
        digitalWrite(LED1 + i, LOW);
    }

    Serial.begin(9600);
}

void loop()
{
    int br = 0;
    int brzina;
    int pin7 = digitalRead(7);

    if (pin7) brzina = 1000;
    else brzina = 200;

    for (int i = 0; i < 8; i++)
    {
        if (i < 4)
        {
            digitalWrite(LED1 + i, HIGH);
            digitalWrite(LED1 + 7 - i, HIGH);
            delay(brzina);
            digitalWrite(LED1 + i, LOW);
            digitalWrite(LED1 + 7 - i, LOW);
        }
        else
        {
            br += 2;

            digitalWrite(LED1 + i - br, HIGH);
            digitalWrite(LED1 + 7 - i + br, HIGH);
            delay(brzina);
            digitalWrite(LED1 + i - br, LOW);
            digitalWrite(LED1 + 7 - i + br, LOW);
        }
    }
}
