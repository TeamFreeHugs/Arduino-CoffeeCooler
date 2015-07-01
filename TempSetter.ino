#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeTemperature myTemp(PORT_3, SLOT1);

Me7SegmentDisplay disp(PORT_6);

MePotentiometer tempSetter(PORT_8);

MeDCMotor motor(M1);

MeJoystick joystick(PORT_7);

int x = 0;
int y = 0;

int setTemp = 10;
int currentTemp = 0;

boolean showCurrent = true;

void setup() {
  disp.set();
  disp.init();
  Serial.begin(9600);
}

void loop() {
  setTemp = tempSetter.read();
  if (setTemp == 0) {
    setTemp = 22;
  } else {
    setTemp = 22 + setTemp / 100;
  }
  currentTemp = myTemp.temperature();
  Serial.println("Potentiometer = " + setTemp);
  Serial.println("Temperature = " + currentTemp);
  x = joystick.readX();
  y = joystick.readY();
  if (x <= 90 && y <= 90) {
    disp.display(setTemp);
  } else {
    disp.display(currentTemp);
  }
  delay(100);
}
