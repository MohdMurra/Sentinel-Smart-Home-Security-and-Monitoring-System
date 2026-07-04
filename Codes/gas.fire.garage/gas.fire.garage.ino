#include <Servo.h>
Servo servo;
#define redled 13
#define blueled 12
#define buzzer 7
#define servoPin1 2
#define sensorPin A0
#define redled 13
const int flameSensorPin = 8;
int currentAngle = 90;
int Pbutton = 11;
int count;

void setup() {
Serial.begin(9600);
pinMode(redled, OUTPUT);
pinMode(blueled, OUTPUT);
servo.attach(servoPin1);
pinMode(buzzer, OUTPUT);
pinMode(Pbutton, INPUT);
servo.write(currentAngle);
pinMode(flameSensorPin, INPUT);
}

void loop() {
float sensorVoltage;
  float sensorValue;
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue;
  Serial.println("sensorVoltage :");
  Serial.print(sensorVoltage);
  if (sensorVoltage > 140) {
    digitalWrite(blueled,HIGH);
    digitalWrite(redled,LOW);
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(buzzer, LOW);
  }
  int flameState = digitalRead(flameSensorPin);
  Serial.println("Flame sensor state: ");
  Serial.print(flameState);
  if (flameState == LOW) {
    Serial.println("Flame detected!");
    digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(redled, HIGH);
    delay(400);
    digitalWrite(blueled, LOW);
  } else {
    Serial.println("No flame detected.");
    digitalWrite(buzzer, LOW);
    digitalWrite(redled, LOW);
    digitalWrite(blueled, LOW);
  }
  delay(800);

  if (digitalRead(Pbutton) == HIGH) {
    count++;
    delay(200);  // Debounce delay to prevent multiple counts from one press
  }

  if (count == 1) {
    // Move the servo from 90 to 0 degrees gradually
    for (int angle = currentAngle; angle >= 0; angle--) {
      servo.write(angle);
      delay(15);  // Adjust this delay to change the speed of the movement
    }
    currentAngle = 0;  // Update the current angle
  }
  else if (count == 2) {
    // Move the servo from 0 to 90 degrees gradually
    for (int angle = currentAngle; angle <= 90; angle++) {
      servo.write(angle);
      delay(15);  // Adjust this delay to change the speed of the movement
    }
    currentAngle = 90;  // Update the current angle
  }
  else if (count > 2) {
    count = 0;  // Reset count after two presses
  }
  
  delay(100);  // Short delay to allow for button reading
}
