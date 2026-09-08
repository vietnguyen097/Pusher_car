
/*
  0           2
1   1       3   3
  0           2

1 2       3 4

<<<<<<<<<<<<<<<<<<<<<<<    Xe A    >>>>>>>>>>>>>>>>>>>>>>>>>


| \\  \\  \\|           ___________            |//  //  // |
|  \\  \\  \|          | L298N {A} |           |/  //  //  |             2 bánh trước 
|\  \\  \\  |   [OUT 3]| [ ]   [ ] |[OUT 1]    |  //  //  /|
|\\  \\  \\ |   [OUT 4]| [ ]   [ ] |[OUT 2]    | //  //  //|
| \\  \\  \\|          |___________|           |//  //  // |
 







|//  //  // |           ___________            | \\  \\  \\|
|/  //  //  |          | L298N {B} |           |  \\  \\  \|
|  //  //  /|   [OUT 1]| [ ]   [ ] |[OUT 3]    |\  \\  \\  |              2 bánh sau 
| //  //  //|   [OUT 2]| [ ]   [ ] |[OUT 4]    |\\  \\  \\ |
|//  //  // |          |___________|           | \\  \\  \\|



*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int RXV[3];
#include <Adafruit_NeoPixel.h>
#define LED A4
#define nLED 6
Adafruit_NeoPixel strip(nLED, LED, NEO_GRB + NEO_KHZ800);
unsigned long lastRecvTime = 0;
const int in1a = 2;
const int in2a = 3;
const int in3a = 4;
const int in4a = 5;
unsigned long previousMillis = 0;
int currentPixel = 0;
bool isWaiting = false;
const int in1b = 6;
const int in2b = 7;
const int in3b = 8;
const int in4b = 9;
const unsigned long timeout = 300;
RF24 radio(A3, 10);  // CE, CSN
const byte address[5] = "hjfhg";
int rawData[4];
int data[4];
void setup() {
  strip.begin();
  strip.clear();
  strip.setBrightness(100);
  strip.show();
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(10);
  radio.startListening();
  Serial.println("Đang chờ tín hiệu...");

  pinMode(in1a, OUTPUT);
  pinMode(in2a, OUTPUT);
  pinMode(in3a, OUTPUT);
  pinMode(in4a, OUTPUT);


  pinMode(in1b, OUTPUT);
  pinMode(in2b, OUTPUT);
  pinMode(in3b, OUTPUT);
  pinMode(in4b, OUTPUT);
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 0);
}
void stop() {
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 0);
  Serial.println("stop");
}
void cw() {
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 1);
  digitalWrite(in3a, 1);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 1);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 1);

  Serial.println("cw");
}
void ccw() {
  digitalWrite(in1a, 1);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 1);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 1);
  digitalWrite(in3b, 1);
  digitalWrite(in4b, 0);

  Serial.println("ccw");
}
void _0() {
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 1);
  digitalWrite(in3a, 1);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 1);
  digitalWrite(in3b, 1);
  digitalWrite(in4b, 0);

  Serial.println("0");
}
void _45() {
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 1);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 1);
  digitalWrite(in4b, 0);

  Serial.println("45");
}
void _90() {
  digitalWrite(in1a, 1);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 1);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 1);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 1);
  digitalWrite(in4b, 0);
  Serial.println("90");
}
void _135() {
  digitalWrite(in1a, 1);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 1);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 0);
  Serial.println("135");
}
void _180() {
  digitalWrite(in1a, 1);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 1);


  digitalWrite(in1b, 1);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 1);
  Serial.println("180");
}
void _225() {
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 0);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 1);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 0);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 1);
  Serial.println("225");
}
void _270() {
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 1);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 1);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 1);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 1);
  Serial.println("270");
}
void _315() {
  digitalWrite(in1a, 0);
  digitalWrite(in2a, 1);
  digitalWrite(in3a, 0);
  digitalWrite(in4a, 0);


  digitalWrite(in1b, 0);
  digitalWrite(in2b, 1);
  digitalWrite(in3b, 0);
  digitalWrite(in4b, 0);
  Serial.println("315");
}


void loop() {
  unsigned long currentMillis = millis();

  if (!isWaiting) {

    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;

      if (currentPixel <= 6) {
        strip.setPixelColor(currentPixel, strip.Color(255, 255, 0));
        strip.show();
        currentPixel++;
      } else {
        strip.clear();
        strip.show();
        isWaiting = true;
        currentPixel = 0;
      }
    }
  } else {

    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      isWaiting = false;
    }
  }
  if (radio.available()) {
    radio.read(data, sizeof(data));
    RXV[0] = map(data[0], 503, 1023, 0, 2);
    RXV[1] = map(data[1], 517, 1023, 0, 2);
    RXV[2] = map(data[2], 497, 1023, 0, 2);
    lastRecvTime = millis();
    Serial.print(data[0]);
    Serial.print("   ");
    Serial.print(data[1]);
    Serial.print("   ");
    Serial.print(data[2]);
    Serial.print("   ");
    //hướng chạy
  }
  if (millis() - lastRecvTime < timeout) {
    if (RXV[0] > 0 && RXV[1] == 0)
      _90();
    else if (RXV[0] < 0 && RXV[1] == 0)
      _270();
    else if (RXV[0] == 0 && RXV[1] > 0)
      _0();
    else if (RXV[0] == 0 && RXV[1] == 0 && RXV[2] > 0)
      cw();
    else if (RXV[0] == 0 && RXV[1] < 0)
      _180();
    else if (RXV[0] == 0 && RXV[1] == 0 && RXV[2] < 0)
      ccw();
    else if (RXV[0] > 0 && RXV[1] > 0)
      _45();
    else if (RXV[0] > 0 && RXV[1] < 0)
      _135();
    else if (RXV[0] < 0 && RXV[1] > 0)
      _315();
    else if (RXV[0] < 0 && RXV[1] < 0)
      _225();
    else {
      stop();
    }
  } else {
    stop();
  }
}
