#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Adafruit_NeoPixel.h>
#define PIN 5
#define NUMPIXELS 2


Adafruit_NeoPixel rgb(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RF24 radio(9, 10);  // CE, CSN
const byte address[4] = "yurv";

int data[3];

void setup() {

  Serial.begin(9600);
  rgb.begin();

  rgb.setBrightness(100);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(100);
  radio.stopListening();
  radio.setAutoAck(true);
  if (radio.begin()) {
    // Hàm kiểm tra kết nối phần cứng
    if (radio.isChipConnected()) {
      Serial.println("nRF24L01: Kết nối thành công!");
    } else {
      Serial.println("nRF24L01: Lỗi! Không tìm thấy chip.");
    }
  } else {
    Serial.println("nRF24L01: Không thể khởi tạo (Check dây CE/CSN)");
  }
}


void loop() {
  rgb.setPixelColor(1, rgb.Color(255, 0, 0));
  rgb.show();
  data[0] = analogRead(A6);
  data[1] = analogRead(A5);
  data[2] = analogRead(A2);
 /* Serial.print(data[0]);
  Serial.print("   ");
  Serial.print(data[1]);
  Serial.print("   ");
  Serial.println(data[2]);
*/
  radio.write(&data, sizeof(data));
  if (radio.write(&data, sizeof(data))) {
    rgb.setPixelColor(0, rgb.Color(0, 0, 255));
    rgb.show();
  } else {
    rgb.setPixelColor(0, rgb.Color(255, 0, 0));
    rgb.show();
  }
}