#define dump(v) Serial.println(v) 

void setup() 
{
	pinMode(33, OUTPUT);
	pinMode(27, OUTPUT);

	Serial.begin(9600);  
}

void loop() 
{
	digitalWrite(33, HIGH);
	delay(1000); 
	digitalWrite(33, LOW);
	delay(1000);

	int pin7 = digitalRead(7);
	dump(pin7);

	if (pin7)
		digitalWrite(27, HIGH);
	else
		digitalWrite(27, LOW);  
}
