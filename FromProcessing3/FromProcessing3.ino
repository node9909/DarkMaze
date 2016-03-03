/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
#include <Servo.h>      // include the servo library

Servo servoMotor1;       // creates an instance of the servo object to control a servo
int servoPin1 = A0;       // Control pin for servo motor
Servo servoMotor2;
int servoPin2 = A1;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  for (int i = 2; i < 7; i++) {
    pinMode(i, OUTPUT);
  }
  // reserve 200 bytes for the inputString:
  inputString.reserve(100);

  servoMotor1.attach(servoPin1);
  servoMotor2.attach(servoPin2);
  //servoMotor.write(90);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    for (int i = 0; i < 5; i++) {
      if (inputString[i] == '1') {
        digitalWrite(i + 2, HIGH);
      }
      else if (inputString[i] == '0') {
        digitalWrite(i + 2, LOW);
      }
    }
    // forward
    if (inputString[1] == '1') {
      servoMotor1.write(20);
      delay(15);
    }
    
    // back
    if (inputString[2] == '1') {
      servoMotor1.write(160);
      delay(15);
    }
    
    // left
    if (inputString[3] == '1') {
      servoMotor2.write(20);
      delay(15);
    }

    //right
    if (inputString[4] == '1') {
      servoMotor2.write(160);
      delay(15);
    }


    //Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

