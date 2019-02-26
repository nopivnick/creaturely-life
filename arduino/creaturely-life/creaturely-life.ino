/*
   Noah Pivnick
   Intro to Computational Media 2233.004 (Mimi Yin)
   Intro to Physical Computing 2301.003 (Tom Igoe)
   Final Project, 2018 Fall
*/

#include <Encoder.h> // Paul Stroffregen's Quadrature Encoder Library for Arduino

/*
  hall sensor stuff
*/
//bool crankIsTurning = false;      // whether or not the crank is turning
//bool hallSensorTypeLatch = false; // whether or not the hall effect sensor is a latch type
//bool hallSensorTypeSwitch = true; // whether or not the hall effect sensor is a switch type
//int hallSensorStatus;             // variable to read the hall effect sensor state
int countCrankCurrent = 0;          // variable to store how many times the hall effect sensor changes

//interrupt stuff from Arduino Reference site
//const byte ledPin = 13; // pin with built-in LED on the UNO
//const int hallSensorPin = 2;     // pin number w/ interrupt for hall effect sensor input
//volatile byte state = LOW;       // volatile is needed when using (in this case external) interrupts

//  Allegro A1220LUA-T stuff via SparkFun Adventures in Science @ https://www.sparkfun.com/news/2438
const int hallSensorPin = 2;       // pin number w/ interrupt for hall effect sensor input
unsigned long hallSensorTicks = 0;
unsigned long hallSensorTicksOld;

/*
   rotary encoder dial stuff
*/
// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder rotaryEncoder(3, 4);
//   avoid using pins with LEDs attached
long rotaryPositOld  = -999;

/*
   rotary encoder button stuff
*/
const int rotaryButtonPin = 8;    // the number of the pushbutton pin
const int ledPin =  13;           // the number of the LED pin
int rotaryButtonOld = 0;          // variable for last rotary button state

/*
 * DC motor stuff
 */
const int motorPin = 13;


void setup() {
  Serial.begin(9600);

  /*
     hall sensor stuff
  */
  // pinMode(ledPin, OUTPUT); // use the onboard LED to indicate every tick of the hall sensor
  pinMode(hallSensorPin, INPUT_PULLUP);

  // this interrupt uses FALLING with the Melexsis US5881 because it's a hall effect *switch*
  // goes from HIGH → LOW when the *south* pole of a magnet passes it's *branded* side
  // attachInterrupt(digitalPinToInterrupt(hallSensorPin), countHallSensorTicks, FALLING);

  // this interrupt uses CHANGE with the Allegro A1220LUA-T because it's a hall effect *latch*
  // place the *branded* face of the sensor toward the ring magnet
  // the sensor alternates HIGH → LOW → HIGH → LOW when detecting North → South → North → South poles
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), countHallSensorTicks, CHANGE);

  /*
     rotary encoder button stuff
  */
  pinMode(rotaryButtonPin, INPUT); // initialize the pushbutton pin as an input
  //  pinMode(ledPin, OUTPUT);     // initialize the LED pin as an output

}

void loop() {

  /*
     hall sensor stuff
  */
  // logic if using hall effect *switch* sensor (Melexsis US5881 unipolar)
  Serial.println(hallSensorTicks);
  delay(100);

  // logic if using hall effect *latch* sensor (Allegro A1220LUA-T)

  // blink the on-board LED when the hall effect sensor gets tripped
  // digitalWrite(ledPin, state);

  /*
     rotary encoder dial stuff
  */
  long rotaryPositNew = rotaryEncoder.read();             // read the rotory encoder and store it as rotaryPositNew
  long rotaryPositTemp = ((rotaryPositNew / 4) % 5) + 1; // translate rotaryPositNew to 1 - 5 and store it as rotaryPositTemp
  if (rotaryPositTemp != rotaryPositOld) {                // if rotaryPositTemp is anything other than the rotaryPositOld ...
    rotaryPositOld = rotaryPositTemp;                     // ... make rotaryPositOld the same value as rotaryPositTemp
    Serial.print("rotary position: ");
    Serial.println(rotaryPositTemp);
  }

  /*
     rotary button stuff
  */
  int rotaryButtonNew = digitalRead(rotaryButtonPin);     // read the state of the pushbutton value
  int rotaryButtonTemp = rotaryButtonNew;
  if (rotaryButtonTemp != rotaryButtonOld) {
    if (rotaryButtonTemp == HIGH) {
      Serial.println("rotary button: pressed");
    }
    rotaryButtonOld = rotaryButtonTemp;
  }

  /*
     DC motor stuff
  */
  int hallSensorTicksTemp = hallSensorTicks;
  if (hallSensorTicks != hallSensorTicksOld) {
    digitalWrite(motorPin, HIGH);
//    Serial.println("motor: on");
  } else {
    digitalWrite(motorPin, LOW);
  }
}

void countHallSensorTicks() {
  hallSensorTicks++;
  // state = !state;
}
