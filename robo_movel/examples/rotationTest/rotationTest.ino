#include <robo_movel.h>

void setup() {
  setupConfig(115200);
  delay(3000);
}

long time;

void loop() {
  time = millis();
  rotate("clockwise","right", 105);
  Serial.print("Time: ");
  Serial.println(millis() - time);
  delay(1000);

  stop();
  delay(1000);

  time = millis();
  rotate("clockwise","left", 85);
  Serial.print("Time: ");
  Serial.println(millis() - time);
  delay(1000);

  stop();
  delay(1000);
  
  time = millis();
  rotate("antiClockwise","right", 360);
  Serial.print("Time: ");
  Serial.println(millis() - time);
  delay(1000);

  stop();
  delay(1000);

  time = millis();
  rotate("antiClockwise","left", 360);
  Serial.print("Time: ");
  Serial.println(millis() - time);
  delay(1000);

  stop();
  delay(2000);
}
