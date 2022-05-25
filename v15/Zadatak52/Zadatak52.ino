/*
Umesto funkcije analogWrite(), razviti svoju PWM funkciju, shodno sledećim zahtevima:
- Širina osnovnog PWM impulsa (bita) je konfigurabilna, i jednaka umnošku od 1ms.
- Period PWM jednak je trajanju 1024 bita.
- Promena vrednosti očitane sa potenciometra menja odnos signal/pauza.
*/

const int analog_in = A0;
const int analog_out = 33;

int pocetno_vreme;

#define bit_vreme 6
#define period (bit_vreme * 1024)

void potenciometar(int id, void* tptr)
{
	int senzor = analogRead(analog_in);
	int skaliran = senzor * bit_vreme;

	// lampica je upaljena
	if (millis() - pocetno_vreme < skaliran)
		digitalWrite(analog_out, HIGH);
	// lampica je ugasena
	else if (millis() - pocetno_vreme < period)
		digitalWrite(analog_out, LOW);
	// novi ciklus
	else
		pocetno_vreme = millis();
}

void setup()
{
	Serial.begin(9600);
	pinMode(analog_out, OUTPUT);

	pocetno_vreme = millis();
	createTask(potenciometar, bit_vreme, TASK_ENABLE, NULL);
}

void loop()
{

}
