//#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library
#include "DHT.h"

#define TFT_CS    8      // TFT CS  pin is connected to arduino pin 8
#define TFT_RST   9      // TFT RST pin is connected to arduino pin 9
#define TFT_DC    10     // TFT DC  pin is connected to arduino pin 10
#define LIME 0x07E0
#define WHITE 0xFFFF
#define GOLD 0xFEA0
#define CYAN 0x07FF
#define GREEN 0x07E0
#define BLACK 0x0000
// initialize ILI9341 TFT library
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {50, 51, 52, 53};
byte colPins[COLS] = {49, 48, 47};
Keypad cusKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int LeftMotorForward = 22;
int LeftMotorReverse = 23;
int RightMotorForward = 24;
int RightMotorReverse = 25;

#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

char temperature[] = "Temp = 00.0 C";
char humidity[]    = "RH   = 00.0 %";

int gasSensor = 14;

bool start = false;
String password = "8094";
String entered_password = "";
String hide_password = "";

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.fillScreen(BLACK);
  tft.setCursor(20, 0);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Welcome To");
  tft.setCursor(65, 23);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Hydro");
  tft.setCursor(32, 48);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("Automation");
  tft.setCursor(65, 72);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("System");
  tft.setCursor(0, 110);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Enter Password:");
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorReverse, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorReverse, OUTPUT);
  dht.begin();
  pinMode(gasSensor, INPUT);
}

void loop() {
  enterPassword();
}

void enterPassword() {
  if (!start) {
    char key = cusKeypad.getKey();
    if (key) {
      entered_password += String(key);
      hide_password += '*';
      tft.setCursor(0, 125);
      tft.setTextSize(2);
      tft.setTextColor(WHITE);
      tft.print(hide_password);
      if (entered_password.length() >= 4) {
        if (entered_password == password) {
          tft.setCursor(0, 135);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.print("Correct Password");
          start = true;
          tft.fillScreen(BLACK);
          startSystem();
        } else {
          tft.setCursor(0, 135);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.print("Wrong Password");
          entered_password = "";
          hide_password = "";
          tft.fillScreen(BLACK);
          tft.setCursor(20, 0);
          tft.setTextSize(3);
          tft.setTextColor(WHITE);
          tft.print("Welcome To");
          tft.setCursor(65, 23);
          tft.setTextSize(3);
          tft.setTextColor(WHITE);
          tft.print("Hydro");
          tft.setCursor(32, 48);
          tft.setTextSize(3);
          tft.setTextColor(WHITE);
          tft.print("Automation");
          tft.setCursor(65, 72);
          tft.setTextSize(3);
          tft.setTextColor(WHITE);
          tft.print("System");
          tft.setCursor(0, 110);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.print("Enter Password:");
          enterPassword();
        }
      }
      //delay(200);
    }
  } else {
    //tft.fillScreen(BLACK);
    startSystem();
  }
}

void startSystem() {
  int RH = dht.readHumidity() * 10;
  int Temp = dht.readTemperature() * 10;
  if (isnan(RH) || isnan(Temp)) {
    //lcd.clear();
    //lcd.setCursor(5, 0);
    //lcd.print("Error");
    return;
  }
  if (Temp < 0) {
    temperature[6] = '-';
    Temp = abs(Temp);
  }
  else {
    temperature[6]   = ' ';
  }
  temperature[7]   = (Temp / 100) % 10  + 48;
  temperature[8]   = (Temp / 10)  % 10  + 48;
  temperature[10]  =  Temp % 10 + 48;
  temperature[11]  = 223;
  if (RH >= 1000) {
    humidity[6]    = '1';
  }
  else {
    humidity[6]      = ' ';
  }
  humidity[7]      = (RH / 100) % 10 + 48;
  humidity[8]      = (RH / 10) % 10 + 48;
  humidity[10]     =  RH % 10 + 48;
  tft.drawRoundRect(0, 0, 300, 30, 8, BLACK);
  tft.fillRoundRect(0, 0, 300, 30, 8, BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print(temperature);
  if (digitalRead(gasSensor) == HIGH) { 
    tft.drawRoundRect(0, 23, 300, 30, 8, BLACK);
    tft.fillRoundRect(0, 23, 300, 30, 8, BLACK);
    tft.setCursor(0, 23);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    tft.print("Gas");
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorReverse, HIGH);
    digitalWrite(LeftMotorReverse, LOW);
  }
  else {
    tft.drawRoundRect(0, 23, 300, 30, 8, BLACK);
    tft.fillRoundRect(0, 23, 300, 30, 8, BLACK);
    tft.setCursor(0, 23);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    tft.print("No Gas");
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorReverse, LOW);
    digitalWrite(LeftMotorReverse, LOW);
  }
  delay(400);
}
