#include <robo_movel.h>

void setup() {
  setupConfig(115200);
  delay(3000);
}

void loop() {
  wallTracker();
  
  Serial.print("RIGHT MOTOR:");
  Serial.print(getRightMotorRPM());
  Serial.print(" RPM - ");
  Serial.print(getRightMotorDistance());
  Serial.println(" cm");

  Serial.print("LEFT MOTOR:");
  Serial.print(getLeftMotorRPM());
  Serial.print(" RPM - ");
  Serial.print(getLeftMotorDistance());
  Serial.println(" cm");
}

