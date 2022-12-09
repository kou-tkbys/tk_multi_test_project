#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
// TM1604 最新のgithubのリリースバージョンを持ってこないとビルドが通らない
// platformioの最新ライブラリにパッチが適応できない。設定の問題の可能性がある。
// https://github.com/maxint-rd/TM16xx/releases/tag/v0.5.2110
#include <TM1640.h>

/*
  u8g2ライブラリでSH1122のSPI接続のOLEDをつなげた場合のメモ
  基板(board)の各ピンにプリントされている内容と対応する名称
  RST/DCに関してはデジタルアウトのピンであればどこでも大丈夫なよう。
  ----------------------------
  board | 呼び
  ----------------------------
  GND   | GND
  VCC   | VCC(3.3v)
  SCL   | SCK
  SDA   | MOSI/TX
  RST   | RST
  DC    | DC
  CS    | PIN_SPI_SS/CSn/SS
  ----------------------------

// example construction code
#include <U8g2lib.h>
#define SH1112_PIN_DC 7
#define SH1112_PIN_RST 6
U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R0, PIN_SPI_SS, SH1112_PIN_DC,
                                    SH1112_PIN_RST);
*/

// TM1640を利用して作成した16連7セグLEDを接続する
TM1640 module(2, 3, 16);  // data, clock, 16 digits

void setup() {
  Serial.begin(9600);
  Serial.println(__FILE__);
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);

  module.setDisplayToString("HALO");  // 初めの挨拶

  delay(500);
}

int64_t sum = 0;
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // pico側のビルドインLED点灯

  // 謎の勢いでひたすらインクリメントした値を表示する
  module.setupDisplay(
      true, 7);  // sometimes noise on the line may change the intensity
  module.setDisplayToDecNumber(sum);
  sum += 1;

  digitalWrite(LED_BUILTIN, LOW);  // pico側のビルドインLED消灯
}