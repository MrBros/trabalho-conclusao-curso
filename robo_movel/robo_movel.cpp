/*
  robo_movel.cpp - Auxiliary library created to help students to get and set sensors data from a mobile differential robot

  Created by Mario Rodrigues. May 10, 2024.
*/

#include "Arduino.h"
#include "robo_movel.h"

// VARIAVEIS
volatile byte rpmLeftCounter;
volatile byte rpmRightCounter;
volatile long distanceRightCounter;
volatile long distanceLeftCounter;
volatile byte rotateRightCounter;
volatile byte rotateLeftCounter;
long leftTimeold;
long rightTimeold;

int movementOrientation = 0;

int SPEED_RIGHT_MOTOR_VALUE = TGT_PWM_VALUE;
int SPEED_LEFT_MOTOR_VALUE  = TGT_PWM_VALUE;

char* action;

float distance;

Ultrasonic UltrassonicSensor(11, 12);

// FUNCOES
void incrementLeftCounter() {
  rpmLeftCounter += movementOrientation;
  distanceLeftCounter += movementOrientation;
  rotateLeftCounter += 1;
}

void incrementRightCounter() {
  rpmRightCounter += movementOrientation;
  distanceRightCounter += movementOrientation;
  rotateRightCounter += 1;
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

void rotate(char* direction, char* pivot, float ang) {
  float rad = ang * (PI / 180);
  float rightTargetDistance, leftTargetDistance, rightCurrentDistance, leftCurrentDistance;
  

  // Velocidade motor lado esquerdo
  analogWrite(SPEED_LEFT_MOTOR, SPEED_LEFT_MOTOR_VALUE);
  // Velocidade motor lado direito
  analogWrite(SPEED_RIGHT_MOTOR, SPEED_RIGHT_MOTOR_VALUE);


  if(direction == "clockwise") {
    if(pivot == "center") {
      rotateRightCounter = 0;
      rotateLeftCounter  = 0;
      rightCurrentDistance = 0;
      leftCurrentDistance = 0;
      rightTargetDistance = (L / 2) * rad;
      leftTargetDistance  = (L / 2) * rad;


      // Motor lado esquerdo para frente
      digitalWrite(LEFT_MOTOR_1, HIGH);
      digitalWrite(LEFT_MOTOR_2, LOW);

      // Motor lado direito para trás
      digitalWrite(RIGHT_MOTOR_1, LOW);
      digitalWrite(RIGHT_MOTOR_2, HIGH);


      while(rightCurrentDistance < rightTargetDistance || leftCurrentDistance < leftTargetDistance) {
        detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
        rightCurrentDistance = 2 * PI * R * (float(rotateRightCounter) / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, FALLING);

        detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
        leftCurrentDistance  = 2 * PI * R * (float(rotateLeftCounter)  / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, FALLING);
      };

    } else if(pivot == "right") {
      rotateRightCounter = 0;
      rotateLeftCounter  = 0;
      rightCurrentDistance = 0;
      leftCurrentDistance = 0;
      rightTargetDistance = 0;
      leftTargetDistance  = L * rad;

      // Motor lado esquerdo para frente
      digitalWrite(LEFT_MOTOR_1, HIGH);
      digitalWrite(LEFT_MOTOR_2, LOW);

      // Motor lado direito parado
      digitalWrite(RIGHT_MOTOR_1, LOW);
      digitalWrite(RIGHT_MOTOR_2, LOW);

      while(leftCurrentDistance < leftTargetDistance) {
        detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
        leftCurrentDistance  = 2 * PI * R * (float(rotateLeftCounter)  / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, FALLING);
      };

    } else if(pivot == "left") {
      rotateRightCounter = 0;
      rotateLeftCounter  = 0;
      rightCurrentDistance = 0;
      leftCurrentDistance = 0;
      rightTargetDistance = L * rad;
      leftTargetDistance  = 0;

      // Motor lado esquerdo parado
      digitalWrite(LEFT_MOTOR_1, LOW);
      digitalWrite(LEFT_MOTOR_2, LOW);

      // Motor lado direito para trás
      digitalWrite(RIGHT_MOTOR_1, LOW);
      digitalWrite(RIGHT_MOTOR_2, HIGH);


      while(rightCurrentDistance < rightTargetDistance) {
        detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
        rightCurrentDistance = 2 * PI * R * (float(rotateRightCounter) / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, FALLING);

      };
    }
  } else if(direction == "antiClockwise") {
    if(pivot == "center") {
      rotateRightCounter = 0;
      rotateLeftCounter  = 0;
      rightCurrentDistance = 0;
      leftCurrentDistance = 0;
      rightTargetDistance = (L / 2) * rad;
      leftTargetDistance  = (L / 2) * rad;

      // Motor lado esquerdo para trás
      digitalWrite(LEFT_MOTOR_1, LOW);
      digitalWrite(LEFT_MOTOR_2, HIGH);

      // Motor lado direito para frente
      digitalWrite(RIGHT_MOTOR_1, HIGH);
      digitalWrite(RIGHT_MOTOR_2, LOW);

      while(rightCurrentDistance < rightTargetDistance || leftCurrentDistance < leftTargetDistance){
        detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
        rightCurrentDistance = 2 * PI * R * (float(rotateRightCounter) / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, FALLING);

        detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
        leftCurrentDistance  = 2 * PI * R * (float(rotateLeftCounter)  / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, FALLING);

      };

    } else if(pivot == "right") {
      rotateRightCounter = 0;
      rotateLeftCounter  = 0;
      rightCurrentDistance = 0;
      leftCurrentDistance = 0;
      rightTargetDistance = 0;
      leftTargetDistance  = L * rad;

      // Motor lado esquerdo para trás
      digitalWrite(LEFT_MOTOR_1, LOW);
      digitalWrite(LEFT_MOTOR_2, HIGH);

      // Motor lado direito para parado
      digitalWrite(RIGHT_MOTOR_1, LOW);
      digitalWrite(RIGHT_MOTOR_2, LOW);

      while (leftCurrentDistance < leftTargetDistance) {
        detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
        leftCurrentDistance  = 2 * PI * R * (float(rotateLeftCounter)  / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, FALLING);
      }

    } else if(pivot == "left") {
      rotateRightCounter = 0;
      rotateLeftCounter  = 0;
      rightCurrentDistance = 0;
      leftCurrentDistance = 0;
      rightTargetDistance = L * rad;
      leftTargetDistance  = 0;

      // Motor lado esquerdo parado
      digitalWrite(LEFT_MOTOR_1, LOW);
      digitalWrite(LEFT_MOTOR_2, LOW);

      // Motor lado direito para frente
      digitalWrite(RIGHT_MOTOR_1, HIGH);
      digitalWrite(RIGHT_MOTOR_2, LOW);
      
      while(rightCurrentDistance < rightTargetDistance) {
        detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
        rightCurrentDistance = 2 * PI * R * (float(rotateRightCounter) / ENCODER_DENSITY);
        attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, FALLING);

      };
    }
  }
  
  stop();
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

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, FALLING);

  Serial.begin(serialRate); 

  rpmRightCounter = 0;
  distanceRightCounter = 0;
  rotateRightCounter = 0;
  rightTimeold = millis();

  rpmLeftCounter = 0;
  distanceLeftCounter = 0;
  rotateLeftCounter = 0;
  leftTimeold = millis();
}

void wallTracker() {
  distance = UltrassonicSensor.Ranging(CM);

  if(distance < MAX_DISTANCE) {
    Serial.println("ACAO: Para!\n");
    stop();
    delay(500);

    Serial.print("DISTANCIA DO OBSTACULO: ");
    Serial.print(distance);
    Serial.println(" cm\n");

    Serial.println("ACAO: Move para trás...\n");
    move("backward");
    delay(200);

    Serial.println("ACAO: Para!\n");
    stop();
    delay(500);

    Serial.println("ACAO: Rotaciona no sentido horário com o eixo na roda direita...\n");
    rotate("clockwise", "right", 90);

    Serial.println("Stop!");
    stop();
    delay(500);

    distance = UltrassonicSensor.Ranging(CM);
    Serial.print("DISTANCIA DO OBSTACULO: ");
    Serial.print(distance);
    Serial.println(" cm\n");

    if(distance < MAX_DISTANCE) {
    Serial.println("Lado direito Bloqueado!\nACAO: Rotaciona sobre o próprio eixo no sentido anti-horário...\n");
      rotate("antiClockwise", "center", 90);

      Serial.println("Stop!");
      stop();
      delay(500);
    }
  } else {
    Serial.println("ACAO: Move para frente...\n");
    move("forward");
  } 

  delay(10);
}

float getRightMotorRPM() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
  float rpm = ((60000 / ENCODER_DENSITY) / (millis() - rightTimeold)) * rpmRightCounter;
  rightTimeold = millis();
  rpmRightCounter = 0;
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, FALLING);

  return rpm;
}

float getLeftMotorRPM() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
  float rpm = ((60000 / ENCODER_DENSITY) / (millis() - leftTimeold)) * rpmLeftCounter;
  leftTimeold = millis();
  rpmLeftCounter = 0;
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, FALLING);

  return rpm;
}

float getRightMotorDistance() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
  float distance = 2 * PI * R * (float(distanceRightCounter) / ENCODER_DENSITY);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), incrementRightCounter, FALLING);

  return  distance;
}

float getLeftMotorDistance() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
  float distance = 2 * PI * R * (float(distanceLeftCounter) / ENCODER_DENSITY);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), incrementLeftCounter, FALLING);

  return  distance;
}
