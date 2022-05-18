int oldState;

int PIN_LD1 = 26;
int PIN_BTN1 = 4;
int PIN_SW1 = 2;
int INT_SW1 = 1;
int br, lampica_id;

void interruptOff();

void interruptOn(){
   br++;
   if (br>10) br = 1;
   detachInterrupt(INT_SW1);
   attachInterrupt(INT_SW1, interruptOff, RISING);
}
void interruptOff(){
   br++;
   if (br>10) br = 1;
   detachInterrupt(INT_SW1);
   attachInterrupt(INT_SW1, interruptOn, FALLING);
}

void lampica(int id, void * tptr)
{
   digitalWrite(PIN_LD1, !digitalRead(PIN_LD1));
}

void dugme(int id, void * tptr)
{
    int newState = digitalRead(PIN_BTN1);
  if (oldState == 1  && newState == 0) {
        Serial.print("Period: ");
        Serial.println(1000/br);
  } else if (oldState == 0 && newState ==1) {
        setTaskPeriod(lampica_id, 1000/(2*br));
  }
  oldState = newState;
}

void serijskiMonitor(int id, void * tptr)
{
    if (Serial.available()){
        char c = Serial.read();
        if ('0'<=c && c<='9') {
            br = c-'0'+1;
            setTaskPeriod(lampica_id, 1000/(2*br));
        }
    }
}

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_LD1, OUTPUT);
  br = 1;
  if (digitalRead(PIN_SW1))
    attachInterrupt(INT_SW1, interruptOn, FALLING);
  else
    attachInterrupt(INT_SW1, interruptOff, RISING);
  lampica_id = createTask(lampica, 1000/(2*br), TASK_ENABLE, NULL);
  createTask(dugme, 50, TASK_ENABLE, NULL);
  createTask(serijskiMonitor, 50, TASK_ENABLE, NULL);
}

void loop()
{

}
