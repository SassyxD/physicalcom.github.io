#include <Servo.h>

Servo myServo;                  
const int buttonLeftPin = 2;   
const int buttonRightPin = 3;  
const int servoPin = 9;        

int servoAngle = 90;           
bool lastLeftState = HIGH;     
bool lastRightState = HIGH;    

void setup() {
  Serial.begin(9600);                     
  myServo.attach(servoPin);               
  myServo.write(servoAngle);              

  pinMode(buttonLeftPin, INPUT_PULLUP);   
  pinMode(buttonRightPin, INPUT_PULLUP);  
}

void loop() {
  bool currentLeftState = digitalRead(buttonLeftPin);
  bool currentRightState = digitalRead(buttonRightPin);

  Serial.print("Left Button State: ");
  Serial.print(currentLeftState);
  Serial.print(" | Right Button State: ");
  Serial.println(currentRightState);

  if (currentLeftState == LOW && lastLeftState == HIGH) {
    servoAngle = max(0, servoAngle - 10);  
    myServo.write(servoAngle);              
    Serial.print("Moving Left to: ");
    Serial.println(servoAngle);
    delay(200);                             
  }

  if (currentRightState == LOW && lastRightState == HIGH) {
    servoAngle = min(180, servoAngle + 10); 
    myServo.write(servoAngle);              
    Serial.print("Moving Right to: ");
    Serial.println(servoAngle);
    delay(200);                             
  }

  lastLeftState = currentLeftState;
  lastRightState = currentRightState;
}
