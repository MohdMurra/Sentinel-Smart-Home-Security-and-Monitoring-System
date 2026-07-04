#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define buzzer 3
#define servoPin1 2
#define redled 4
#define greenled 7

String UID = "40 C6 15 D3";//Enter your card ID
byte lock = 0;

Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  servo.write(0);
  lcd.init();
  lcd.backlight();
  servo.attach(servoPin1);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(buzzer, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  if (ID.substring(1) == UID && lock == 0 ) {
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    digitalWrite(redled,LOW);
    digitalWrite(greenled,LOW);
    servo.write(0);
    delay(100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Locked");
    delay(3000);
    lcd.clear();
    lock = 1;
  } else if (ID.substring(1) == UID && lock == 1 ) {
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);
    servo.write(90);
    delay(100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unlocked");
    delay(3000);
    lcd.clear();
    lock = 0;
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    servo.write(0);
    digitalWrite(redled,HIGH);
    delay(200);
    digitalWrite(greenled,LOW);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(redled,LOW);
    delay(200);
    delay(3000);
    lcd.clear();
  }
}