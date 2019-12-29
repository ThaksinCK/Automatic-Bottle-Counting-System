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

}

void loop() {
  delay(250);
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
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(1, 0);         //บรรทัดบน=0
    lcd.print("Bottle Now:");
    lcd.setCursor(12, 0);       //บรรทัดล่าง=1
    lcd.print(NumberOFBottles);
    delay(750);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Thank YOU!");
    lcd.setCursor(0, 1);
    lcd.print("Have a nice day!");


  }
}
