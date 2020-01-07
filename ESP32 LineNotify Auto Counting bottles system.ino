#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


#include <TridentTD_LineNotify.h>

#define SSID        "OPPOA3s"      // บรรทัดที่ 11 ให้ใส่ ชื่อ Wifi ที่จะเชื่อมต่อ
#define PASSWORD    "1212312121"     // บรรทัดที่ 12 ใส่ รหัส Wifi
#define LINE_TOKEN1   "S8H3wVmfY3pIzYNM6kUTGzxwRgUUQQElaMQzKOJpyuc" //เครื่องเก็บขวด
#define LINE_TOKEN2   "GzUKjiUiCoC8m0MjSbEPKGsRCuoGZo0MrxIelQX6t69" // ยอดรวม
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
  total = 1;
}

void loop() {
  ULTRASONIC();
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

void BottleWater() {
  if (distance <= 10) {
    NumberOFBottles = NumberOFBottles + 1;
    Buzzer();
    Serial.print("Bottle water: ");
    Serial.println(NumberOFBottles);
    LCDI2C();
    linenotify();
    BottlesTotal();
    delay(1000);
  }
}
void linenotify() {
  if (NumberOFBottles >= 10) {
    NumberOFBottles = 0;
    Serial.println("Line");
    LINE.setToken(LINE_TOKEN1); LINE.notify("เครื่องเก็บขวด: เครื่องได้มีการใส่ขวดครบ10ขวด💧 ได้รับคะแนนจิตอาสา 10นาที🕘  ♻ ขอบคุณที่ช่วยแยกขยะ ♻ _____________________________ เครื่องเก็บขวดอัตโนมัติ ESP32 ตัวอย่างโค๊ด:https://github.com/ThaksinCK/Automatic-Bottle-Counting-System/commit/1a67be4834e0e502cf1c511cacabb8941be7ded3");
    LINE.setToken(LINE_TOKEN1); LINE.notifyPicture("https://www.img.in.th/image/4NskrA");
    LINE.setToken(LINE_TOKEN2); LINE.notify(total);

    delay(2000);
  }
}

void BottlesTotal() {
  if (NumberOFBottles >= 0) {
    total = total + 1;
  }
}

void Buzzer() {
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
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

  }
  else  {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Bottle Now:");
    lcd.setCursor(12, 0);
    lcd.print(NumberOFBottles);
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
