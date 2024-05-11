/*
  robo_movel.h - Auxiliary library created to help students to get and set sensors data from a mobile differential robot

  Created by Mario Rodrigues. May 10, 2024.
*/

#ifndef robo_movel_h
#define robo_movel_h

#include "Arduino.h"
#include <Ultrasonic.h>

// CONSTANTES
#define RIGHT_MOTOR_1 10
#define RIGHT_MOTOR_2 9

#define LEFT_MOTOR_1 7
#define LEFT_MOTOR_2 8

#define SPEED_LEFT_MOTOR 5
#define SPEED_RIGHT_MOTOR 6

#define ENCODER_LEFT 3
#define ENCODER_RIGHT 2
#define ENCODER_RIGHT_DIR 1
#define ENCODER_LEFT_DIR 13
#define ENCODER_DENSITY 20

#define MAX_DISTANCE 20

#define MIN_PWM_VALUE 0
#define MAX_PWM_VALUE 255
#define TGT_PWM_VALUE 255

#define R 3.2
#define L 15.3

void incrementLeftCounter();

void incrementRightCounter();

void move(char* direction);

void rotate(char* direction, long millisec);

void stop();

void setupConfig(long serialRate);

void wallTracker();

float getRightMotorRPM();

float getLeftMotorRPM();

float getRightMotorDistance();

float getLeftMotorDistance();

#endif