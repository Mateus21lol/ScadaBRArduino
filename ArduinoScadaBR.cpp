#include <Modbus.h>
#include <ModbusSerial.h>

// constants won't change. Used here to set a pin number:
const int ledPin =  2;// the number of the LED pin
const int ledPin1 = 9;
const int ledPin2 = 10;
const int ledPin3 = 11;
const int ledPin4 = 12;
const int ledPin5 = 13;


// Variables will change:
int ledState = 0; 
int ledState1 = 1;
int ledState2 = 2;
int ledState3 = 3; 
int ledState4 = 4; // ledState used to set the LED
int ledState5 = 5;

unsigned long previousMillis = 0;
boolean startTimer = false; 

// constants won't change:
const long intervalo = 10000;

ModbusSerial mb;

void setup() {

  mb.config(&Serial, 9600, SERIAL_8N1);
  mb.setSlaveId(1);
  
  // set the digital pin as output:
  pinMode(ledPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);

  mb.addCoil(ledState);
  mb.addCoil(ledState1);
  mb.addCoil(ledState2);
  mb.addCoil(ledState3);
  mb.addCoil(ledState4);
  mb.addCoil(ledState5);
  
}

void loop() {
 
  mb.task();

  unsigned long currentMillis = millis();

  digitalWrite(ledPin1, mb.Coil(ledState1));
  digitalWrite(ledPin2, mb.Coil(ledState2));
  digitalWrite(ledPin3, mb.Coil(ledState3));
  digitalWrite(ledPin4, mb.Coil(ledState4));
  digitalWrite(ledPin5, mb.Coil(ledState5));

  if (mb.Coil(ledState)) {
    if (!startTimer) {
      previousMillis = currentMillis;
      startTimer = !startTimer;
      mb.Coil(ledState1, 1);  
    }
    if (currentMillis - previousMillis >= intervalo) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (mb.Coil(ledState1)) {
        mb.Coil(ledState1, 0);
        mb.Coil(ledState2, 1);  
      } else if (mb.Coil(ledState2)) {
        mb.Coil(ledState2, 0);
        mb.Coil(ledState3, 1);
        mb.Coil(ledState4, 1);   
      } else if (mb.Coil(ledState3) && mb.Coil(ledState4)) {
        mb.Coil(ledState3, 0);
        mb.Coil(ledState4, 0);
        mb.Coil(ledState5, 1);
      } else {
        mb.Coil(ledState, 0);
        mb.Coil(ledState5, 0);
      }
    }
  } else {
    mb.Coil(ledState1, 0);
    mb.Coil(ledState2, 0);
    mb.Coil(ledState3, 0);
    mb.Coil(ledState4, 0);
    mb.Coil(ledState5, 0);
    startTimer = false;  
  }

}

  