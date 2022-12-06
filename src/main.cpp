#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
// TM1604 最新のgithubのリリースバージョンを持ってこないとビルドが通らない
// platformioの最新ライブラリに登録されていない？
#include <TM1640.h>
// #include <TCA9548.h>
// TCA9548 MP(0x70);

// Define a 4-digit display module. Pin suggestions:
// ESP8266 (Wemos D1): data pin 5 (D1), clock pin 4 (D2)
// ATtiny44A: data pin 9, clock pin 10 (LED_BUILTIN: 8 on ATTinyCore)
TM1640 module(9, 8, 16);    // data, clock, 4 digits

void setup() {

  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  module.setDisplayToString("HALO");
  delay(500);                        // wait
  //module.clearDisplay();
  //put your setup code here, to run once:

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  module.setupDisplay(true, 7);   // sometimes noise on the line may change the intensity level
  int nTime = ((millis() / 1000) / 60) * 100 + (millis() / 1000) % 60; // minutes+seconds as integer
  module.setDisplayToDecNumber(nTime, _BV(4)); // display dot on digit 4
  delay(500);                        // wait
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  module.setDisplayToDecNumber(nTime, _BV(3)); // display colon on digit 3
  delay(500);   
}