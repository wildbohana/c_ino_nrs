/*
Blink
Turns on an LED on for one second, then off for one second, repeatedly.
ZADATAK: promeni pin ili vreme; iskoristi tastere BTN1:4
*/
 
#define dump(v) Serial.println(v) 

#define LED_1 26
#define LED_NUM 8

void setup() 
{
	for (int i = 0; i < LED_NUM; i++)
	{
		pinMode(LED_1 + i, OUTPUT);
		digitalWrite(LED_1 + i, LOW);
	}
	
	Serial.begin(9600);  
}

void loop() 
{
	// Led Counter
	static int lcnt = 0;

	// prvo ugasi tekuci
	digitalWrite(LED_1 + lcnt, LOW);
	
	// Show 1: pali na desno
	if (digitalRead(7))
	{		
		if (lcnt == 0) lcnt = LED_NUM-1;
		else lcnt = lcnt - 1;  
	}
	// Show 2: pali na levo
	else
		lcnt = (lcnt + 1) % LED_NUM;
	
	// upali skledeci LED
	digitalWrite(LED_1 + lcnt, HIGH);    

	delay(1000);
}
