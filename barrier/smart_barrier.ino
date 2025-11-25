#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo bariera;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

long durata;
int distanta;

void setup() {
  Serial.begin(9600);
  bariera.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistem parcare");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Masoara distanta
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  durata = pulseIn(echoPin, HIGH);
  distanta = durata * 0.034 / 2;

  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distanta);
  lcd.print(" cm   ");

  if (distanta < 15) {
    lcd.setCursor(0, 1);
    lcd.print("LOC OCUPAT      ");
    bariera.write(90); // Deschide bariera
  } else {
    lcd.setCursor(0, 1);
    lcd.print("LOC LIBER       ");
    bariera.write(0); // Inchide bariera
  }

  delay(500);
}
