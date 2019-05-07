unsigned long lastTime = 0;
unsigned long diff = 0;

void setup() {
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(4), timestamp, CHANGE);
}

void loop() {
  delay(1000);
  Serial.println(diff);
}

void timestamp() {
  diff =  millis() - lastTime;
  lastTime = millis();
}
