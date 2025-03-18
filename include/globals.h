#ifndef MAIN_GLOBALS_H
#define MAIN_GLOBALS_H

#include <Arduino.h>

#define LED_PIN 2

#define ROLL_PIN 34
#define PITCH_PIN 35
#define YAW_PIN 32
#define THROTTLE_PIN 33

#define THROTTLE_INVERTED 1
#define YAW_INVERTED -1
#define PITCH_INVERTED -1
#define ROLL_INVERTED 1

#define NUM_CALIBRATION_SAMPLES 1000
#define NUM_CALIBRATION_SAMPLES_CENTER 500
#define READ_INTERVAL 50

#define START_BYTE 0xAA
#define END_BYTE 0xFE

const uint8_t RECEIVER_MAC[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

#define BUZZER_PIN 26

#endif