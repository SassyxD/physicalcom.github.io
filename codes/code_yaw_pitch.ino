#include <Servo.h>

int joystick_axis_x = A0;
int joystick_axis_y = A1;
int left_button = 5;
int right_button = 3;
int yawServoPin = 9;
int pitchServoPin = 8;
int gripperServoPin = 13;

Servo yawServo;
Servo pitchServo;
Servo gripperServo;

int currentYaw = 90;
int currentPitch = 90;
int gripperClose = 0;
int gripperOpen = 90;

void setup() {
  yawServo.attach(yawServoPin);
  pitchServo.attach(pitchServoPin);
  gripperServo.attach(gripperServoPin);
  
  yawServo.write(currentYaw);
  pitchServo.write(currentPitch);
  gripperServo.write(gripperOpen);
  
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  int joystickX = analogRead(joystick_axis_x);
  int joystickY = analogRead(joystick_axis_y);
  
  int targetYaw = map(joystickX, 0, 1023, 0, 180);
  int targetPitch = map(joystickY, 0, 1023, 0, 180);

  if (currentYaw < targetYaw) {
    currentYaw++;
  } else if (currentYaw > targetYaw) {
    currentYaw--;
  }

  if (currentPitch < targetPitch) {
    currentPitch++;
  } else if (currentPitch > targetPitch) {
    currentPitch--;
  }

  yawServo.write(currentYaw);
  pitchServo.write(currentPitch);

  if (digitalRead(left_button) == LOW) {
    gripperServo.write(gripperClose);
    Serial.println("Gripper Closed");
  } 
  else if (digitalRead(right_button) == LOW) {
    gripperServo.write(gripperOpen);
    Serial.println("Gripper Opened");
  } 
  else {
    Serial.println("Gripper Idle");
  }

  Serial.print("Yaw Angle = ");
  Serial.print(currentYaw);
  Serial.print(" | Pitch Angle = ");
  Serial.println(currentPitch);

  delay(20);
}
