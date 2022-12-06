#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
// TM1604 最新のgithubのリリースバージョンを持ってこないとビルドが通らない
// platformioの最新ライブラリに登録されていない？
#include <TM1640.h>
// #include <TCA9548.h>
// TCA9548 MP(0x70);
#include <SPI.h>
#include <U8g2lib.h>


/**
 	GND		|		GND
	VCC		|		VCC (3.3V)
	SCL		|		SCK (Pin 9)
	SDA		|		MOSI (Pin 8)
	RST		|		Pin 6
	DC		|		Pin 7
	CS		|		Pin 4 (PIN_SPI_SS)

  SPI0 SCK	    GP2
  SPI0 TX(MOSI)	GP3
  SPI0 RX(MISO)	GP4
  SPI0 CSn  SS  GP5 
*/
#define SH1112_PIN_SCK 2
#define SH1112_PIN_MOSI 3
#define SH1112_PIN_MISO 4
#define SH1112_PIN_CSn 5
// ↑違った。u8g2の中見てったらデフォルトのR0だったのでこの番号は忘れて。
#define SH1112_PIN_DC 7
#define SH1112_PIN_RST 6
U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R0,PIN_SPI_SS,SH1112_PIN_DC,SH1112_PIN_RST);

// Define a 4-digit display module. Pin suggestions:
// ESP8266 (Wemos D1): data pin 5 (D1), clock pin 4 (D2)
// ATtiny44A: data pin 9, clock pin 10 (LED_BUILTIN: 8 on ATTinyCore)
TM1640 module(9, 8, 16);    // data, clock, 4 digits

void setup() {

  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.println();
  u8g2.begin();
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

  u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_helvB08_tr);
	u8g2.drawStr(0, 9, "Hello World");
	u8g2.drawStr(40, 20, "Hello World");
	u8g2.drawStr(80, 31, "Hello World");
	u8g2.drawStr(120, 42, "Hello World");
	u8g2.drawStr(160, 53, "Hello World");
	u8g2.drawStr(200, 64, "Hello World");
	u8g2.sendBuffer();
	// delay(1000);

	// for (int i = 0; i < 3; ++i)
	// {
	// 	for (int j = i; j < 64; j += 3)
	// 	{
	// 		u8g2.drawHLine(0, j, 256);
	// 		u8g2.sendBuffer();
	// 		delay(10);
	// 	};
	// }

	// delay(1000);
}