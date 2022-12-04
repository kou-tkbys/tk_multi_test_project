#include <Arduino.h>
#include <TCA9548.h>
#include <TM1640.h>

TCA9548 MP(0x70);

// Define a 4-digit display module. Pin suggestions:
// ESP8266 (Wemos D1): data pin 5 (D1), clock pin 4 (D2)
// ATtiny44A: data pin 9, clock pin 10 (LED_BUILTIN: 8 on ATTinyCore)
TM1640 module(9, 10, 16);    // data, clock, 4 digits

void setup() {

  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.println();

  Wire.begin();
  if (MP.begin() == false)
  {
    Serial.println("COULD NOT CONNECT");
  }

  Serial.print("MASK:\t");
  Serial.println(MP.getChannelMask(), HEX);
  for (int chan = 0; chan < 8; chan++)
  {
    Serial.print("PRE:\t");
    Serial.print(MP.isEnabled(chan));
    MP.enableChannel(chan);
    Serial.print("\t");
    Serial.println(MP.isEnabled(chan));
    delay(100);
  }
  Serial.println();
  MP.setChannelMask(0x00);

  Serial.print("MASK:\t");
  Serial.println(MP.getChannelMask(), HEX);
  for (int chan = 0; chan < 8; chan++)
  {
    MP.enableChannel(chan);

    Serial.print("MASK:\t");
    Serial.println(MP.getChannelMask(), HEX);
    delay(100);
  }
  for (int chan = 0; chan < 8; chan++)
  {
    MP.disableChannel(chan);
    Serial.print("MASK:\t");
    Serial.println(MP.getChannelMask(), HEX);
    delay(100);
  }
  Serial.println();

  Serial.println("done...");
  //put your setup code here, to run once:


   pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  module.setDisplayToString("HALO");
  delay(500);                        // wait
  //module.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  module.setupDisplay(true, 7);   // sometimes noise on the line may change the intensity level
  int nTime = ((millis() / 1000) / 60) * 100 + (millis() / 1000) % 60; // minutes+seconds as integer
  module.setDisplayToDecNumber(nTime, _BV(4)); // display dot on digit 4
  delay(500);                        // wait
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  module.setDisplayToDecNumber(nTime, _BV(3)); // display colon on digit 3
  delay(500);                        // wait
}