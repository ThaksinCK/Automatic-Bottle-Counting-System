/*
  void Line_Notify(String message) ;

  #include <ESP8266WiFi.h>
  #include <WiFiClientSecureAxTLS.h> // กรณีขึ้น Error ให้เอาบรรทัดนี้ออก

  // Config connect WiFi
  #define WIFI_SSID "YOUR WIFINAME"
  #define WIFI_PASSWORD "YOUR WIFIPASSWORD"

  // Line config
  #define LINE_TOKEN "LINE ACCESS TOKEN"

  String message = "โดนกด"; // ArduinoIDE เวอร์ชั่นใหม่ ๆ ใส่ภาษาไทยลงไปได้เลย
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
int NumberOFBottles;

void setup() {
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.init();
  /*
    pinMode(SW, INPUT);

    Serial.begin(9600);

    WiFi.mode(WIFI_STA);
    // connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");

    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
  */


}

void loop() {
  AllSystem();
}
void AllSystem() {
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
  lineNOtfly();
}

void BottleWater() {
  if (distance <= 10) {
    NumberOFBottles = NumberOFBottles + 1;
    Serial.print("Bottle water: ");
    Serial.println(NumberOFBottles);
    LCDI2C();
    delay(1000);
  }
}
void lineNOtfly() {
  if (NumberOFBottles >= 10) {
    NumberOFBottles = 0;
    Serial.println("Line");
    // Line_Notify(message); ลบตัวบนใส่ตัวนี้แทน
    delay(2000);
  }
}
void LCDI2C() {
  NUMBER();

}
void NUMBER() {
  if (NumberOFBottles < 10) {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(1, 0);         //บรรทัดบน=0
    lcd.print("Bottle Now:");
    lcd.setCursor(12, 0);
    lcd.print("0");
    lcd.setCursor(13, 0);       //บรรทัดล่าง=1
    lcd.print(NumberOFBottles);

  }
  else  {
    lcd.clear();
    lcd.setCursor(1, 0);         //บรรทัดบน=0
    lcd.print("Bottle Now:");
    lcd.setCursor(12, 0);       //บรรทัดล่าง=1
    lcd.print(NumberOFBottles);
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Thank YOU!");
    lcd.setCursor(0, 1);
    lcd.print("Have a nice day!");
    delay(3000);
    lcd.clear();
    lcd.noBacklight();

  }
}
/*
   ///////////////////////////////////////////
  void Line_Notify(String message) {
  axTLS::WiFiClientSecure client; // กรณีขึ้น Error ให้ลบ axTLS:: ข้างหน้าทิ้ง

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  // Serial.println(req);
  client.print(req);

  delay(20);

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
  }
*/
/////////////////////////////////////////////////////////
