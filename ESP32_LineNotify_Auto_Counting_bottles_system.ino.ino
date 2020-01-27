/*
  Include Library TridentTD_LineNotify version 2.1 ส่งไลน์
  http://www.mediafire.com/file/3szq0oevu0dt5hg/TridentTD_LineNotify-master.zip/file
  Include Library Arduino-LiquidCrystal-I2C-library-master
  https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


#include <TridentTD_LineNotify.h>

#define SSID        "OPPOA3s"      // บรรทัดที่ 11 ให้ใส่ ชื่อ Wifi ที่จะเชื่อมต่อ
#define PASSWORD    "1212312121"     // บรรทัดที่ 12 ใส่ รหัส Wifi
#define LINE_TOKEN1   "Do8mU9HtAfovRX02Oyl1D1nEB8NGnWRVRRRD52grWIR" //ใส่ Line Token ที่ขอมา สามารถใส่ได้มากกว่า 1 
#define LINE_TOKEN2   "LuJyeldo8QeFAL67d8Ub4IUiEfZDwlUKZF3P4KFBL7s"
const int trigPin = 18;
const int echoPin = 19;
int buzzer = 23;

long duration;
int distance;
int NumberOFBottles;
int total;

void setup() {
  WiFi.begin( SSID, PASSWORD );
  while (!WiFi.isConnected()) delay(400);
  Serial.println( WiFi.localIP());

  String  message = "Messeage to LINE";
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzer, HIGH);
  lcd.begin();
  total = 90;
}

void loop() {
  if(total >= 100){
    }
    else{
      ULTRASONIC();
      }
}
void ULTRASONIC() {
  delay(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(50);

  BottleWater();
}
// ถ้าระยะทางน้อยกว่าหรือเท่ากับ 10 จะนับขวด และแสดงผลผ่านหน้าจอ
void BottleWater() {
  if (distance <= 10) {
    NumberOFBottles = NumberOFBottles + 1;
    total = total + 1;
    Serial.print("Bottle water: ");
    Serial.println(NumberOFBottles);
    LCDI2C();
    linenotify();
    delay(1000);
  }
}
void linenotify() {
  if (NumberOFBottles >= 10) {
    NumberOFBottles = 0;
    Serial.println("Line");
    LINE.setToken(LINE_TOKEN1); LINE.notify("");
    LINE.setToken(LINE_TOKEN1); LINE.notify("");
    LINE.setToken(LINE_TOKEN2); LINE.notify(total);

    delay(2000);
  }
}

void Buzzer() {
  digitalWrite(buzzer, LOW); //ลำโพงเปิด
  delay(100);
  digitalWrite(buzzer, HIGH); //ลำโพงปิด
  delay(10);
}
void LCDI2C() {
  if (NumberOFBottles < 10) {
    lcd.backlight();
    lcd.clear();
    // lcd.setCursor("ตัวอักษรเริ่มต้นที่ช่อง 0-15, บรรทัดที่ 0=บน 1=ล่าง")
    lcd.setCursor(1, 0);
    lcd.print("Bottle Now:");
    lcd.setCursor(12, 0);
    lcd.print("0");
    lcd.setCursor(13, 0);
    lcd.print(NumberOFBottles);
    Buzzer();

  }
  else  {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Bottle Now:");
    lcd.setCursor(12, 0);
    lcd.print(NumberOFBottles);
    Buzzer();
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Thank YOU!");
    lcd.setCursor(3, 1);
    lcd.print("Total:");
    lcd.setCursor(10, 1);
    lcd.print(total);

    delay(3000);
    lcd.clear();
    lcd.noBacklight();
  }
}
