/*
  robo_movel.cpp - Auxiliary library created to help students to get and set sensors data from a mobile differential robot

  Created by Mario Rodrigues. May 10, 2024.
*/

#include "Arduino.h"
#include "robo_movel.h"

// VARIAVEIS
volatile byte leftCounter;
volatile byte rightCounter;
volatile long totalRightCounter;
volatile long totalLeftCounter;
long leftTimeold;
long rightTimeold;

int movementOrientation = 0;

int SPEED_RIGHT_MOTOR_VALUE = TGT_PWM_VALUE;
int SPEED_LEFT_MOTOR_VALUE  = TGT_PWM_VALUE;

Ultrasonic UltrassonicSensor(11, 12);

// FUNCOES
void incrementLeftCounter() {
  leftCounter += movementOrientation;
  totalLeftCounter += movementOrientation;
}

void incrementRightCounter() {
  rightCounter += movementOrientation;
  totalRightCounter += movementOrientation;
}

void move(char* direction) {
    // Velocidade motor lado esquerdo
    analogWrite(SPEED_LEFT_MOTOR, SPEED_LEFT_MOTOR_VALUE);
    // Velocidade motor lado direito
    analogWrite(SPEED_RIGHT_MOTOR, SPEED_RIGHT_MOTOR_VALUE);

  if(direction == "forward") {
    // Motor lado esquerdo para frente
    digitalWrite(LEFT_MOTOR_1, HIGH);
    digitalWrite(LEFT_MOTOR_2, LOW);

    // Motor lado direito para frente
    digitalWrite(RIGHT_MOTOR_1, HIGH);
    digitalWrite(RIGHT_MOTOR_2, LOW);

    movementOrientation = 1;

  } else if(direction == "backward") {
    // Motor lado esquerdo para trás
    digitalWrite(LEFT_MOTOR_1, LOW);
    digitalWrite(LEFT_MOTOR_2, HIGH);

    // Motor lado direito para trás
    digitalWrite(RIGHT_MOTOR_1, LOW);
    digitalWrite(RIGHT_MOTOR_2, HIGH);

    movementOrientation = -1;
  } 
}

void rotate(char* direction, long millisec) {
    // Velocidade motor lado esquerdo
    analogWrite(SPEED_LEFT_MOTOR, SPEED_LEFT_MOTOR_VALUE);
    // Velocidade motor lado direito
    analogWrite(SPEED_RIGHT_MOTOR, SPEED_RIGHT_MOTOR_VALUE);

  if(direction == "clockwise") {
    // Motor lado esquerdo para frente
    digitalWrite(LEFT_MOTOR_1, HIGH);
    digitalWrite(LEFT_MOTOR_2, LOW);

    // Motor lado direito para trás
    digitalWrite(RIGHT_MOTOR_1, LOW);
    digitalWrite(RIGHT_MOTOR_2, HIGH);

  } else if(direction == "antiClockwise") {
    // Motor lado esquerdo para trás
    digitalWrite(LEFT_MOTOR_1, LOW);
    digitalWrite(LEFT_MOTOR_2, HIGH);

    // Motor lado direito para frente
    digitalWrite(RIGHT_MOTOR_1, HIGH);
    digitalWrite(RIGHT_MOTOR_2, LOW);
  }
  
  movementOrientation = 0;
  delay(millisec);
}

void stop() {
  // Motor lado esquerdo desliga
  digitalWrite(LEFT_MOTOR_1, LOW);
  digitalWrite(LEFT_MOTOR_2, LOW);

  // Motor lado direito desliga
  digitalWrite(RIGHT_MOTOR_1, LOW);
  digitalWrite(RIGHT_MOTOR_2, LOW);

  movementOrientation = 0;
}


void setupConfig(long serialRate) {
  pinMode(LEFT_MOTOR_1,  OUTPUT);
  pinMode(LEFT_MOTOR_2,  OUTPUT);
  pinMode(RIGHT_MOTOR_1, OUTPUT);
  pinMode(RIGHT_MOTOR_2, OUTPUT);

  pinMode(ENCODER_LEFT,      INPUT);
  pinMode(ENCODER_RIGHT,     INPUT);
  pinMode(ENCODER_LEFT_DIR,  INPUT);
  pinMode(ENCODER_RIGHT_DIR, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, RISING);

  Serial.begin(serialRate); 

  rightCounter = 0;
  totalRightCounter = 0;
  rightTimeold = millis();

  leftCounter = 0;
  totalLeftCounter = 0;
  leftTimeold = millis();
}

void wallTracker() {
  float distance = UltrassonicSensor.Ranging(CM);
  Serial.print(distance);
  Serial.println(" cm");
  
  if(distance >= MAX_DISTANCE) {
    move("forward");
    Serial.println("Move forward...");
  } else {
    Serial.println("Stop!");
    stop();
    delay(500);

    Serial.println("Rotate Clockwise...");
    rotate("clockwise", 300);

    Serial.println("Stop!");
    stop();
    delay(500);

    distance = UltrassonicSensor.Ranging(CM);
    Serial.print(distance);
    Serial.println(" cm");
    if(distance < MAX_DISTANCE) {
      Serial.println("Blocked!\nRotate Anticlockwise...");
      rotate("antiClockwise", 600);

      Serial.println("Stop!");
      stop();
      delay(500);
    }
  }
  delay(100);
}

float getRightMotorRPM() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
  float rpm = ((60000 / ENCODER_DENSITY) / (millis() - rightTimeold)) * rightCounter;
  rightTimeold = millis();
  rightCounter = 0;
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, RISING);

  return rpm;
}

float getLeftMotorRPM() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
  float rpm = ((60000 / ENCODER_DENSITY) / (millis() - leftTimeold)) * leftCounter;
  leftTimeold = millis();
  leftCounter = 0;
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, RISING);

  return rpm;
}

float getRightMotorDistance() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
  float distance = 2 * PI * R * (float(totalRightCounter) / ENCODER_DENSITY);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, RISING);

  return  distance;
}

float getLeftMotorDistance() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
  float distance = 2 * PI * R * (float(totalLeftCounter) / ENCODER_DENSITY);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, RISING);

  return  distance;
}
