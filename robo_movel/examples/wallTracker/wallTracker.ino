#include <robo_movel.h>

void setup() {
  setupConfig(115200);
  delay(3000);
}

void loop() {
  wallTracker();
  
  // Motor direito
  Serial.println("\n=== MOTOR DIREITO ===\n");
  Serial.print("VELOCIDADE: ");
  Serial.print(getRightMotorRPM());
  Serial.println(" RPM");
  Serial.print("DISTANCIA PERCORRIDA: ");
  Serial.print(getRightMotorDistance());
  Serial.println(" cm");

  // Motor esquerdo
  Serial.println("\n=== MOTOR ESQUERDO ===\n");
  Serial.print("VALOCIDADE: ");
  Serial.print(getLeftMotorRPM());
  Serial.println(" RPM");
  Serial.print("DISTANCIA PERCORRIDA: ");
  Serial.print(getLeftMotorDistance());
  Serial.println(" cm");
}

