/*
Napisati program koji pali lampice na pinovima od 26 do 33 u krug. 
Ukoliko je upaljen taster SW2 na pinu 7, rotirati lampice od manjih 
ka većim pinovima, a u suprotnom od većih ka manjim.
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
	// samo se jednom inicijalizuje na 0 ??
	static int br_lampice = 0;

	// prvo ugasi trenutno upaljenu lampicu
	digitalWrite(LED1 + br_lampice, LOW);
	
	// pali na desno
	if (digitalRead(7))
	{		
		if (br_lampice == 0) 
			br_lampice = 8 - 1;
		else 
			--br_lampice;
	}
	// pali na levo
	else
	{
		br_lampice = ++br_lampice % 8;
	}
	
	// upali lampicu koja je dosla na red (br_lampice)
	digitalWrite(LED1 + br_lampice, HIGH);    
	delay(1000);
}
