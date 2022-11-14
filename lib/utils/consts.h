#ifndef __CONSTS_H_INCLUDED
#define __CONSTS_H_INCLUDED

#include "types.h"

// Light Sensor
constexpr int VIN = 5;
constexpr int LIGHT_SENSOR_RESITOR = 1000; // ms

// Button
constexpr int BUTTON_BOUNCING_DELAY = 50; // ms

// LCD
constexpr int LCD_I2C_ADDRESS = 0x27;
constexpr int DEFAULT_LCD_ROWS = 2;
constexpr int DEFAULT_LCD_COLUMNS = 16;
constexpr int FIRST_LINE = 1;
constexpr int SECOND_LINE = 0;
constexpr int FIRST_COLUMN = 0;

// Sonar
constexpr float SPEED_OF_SOUND = 343; // m/s @ ~20°C
constexpr float US_TO_S = 1.0f / 1000000.0f;
constexpr float M_TO_CM = 100.0f;

// Servo
constexpr int SERVO_LOWER_BOUND = 0;
constexpr int SERVO_UPPER_BOUND = 180;

// Blinking Led
constexpr timestamp_t BLINKING_PERIOD = 2000; // ms

// Scheduler
constexpr int MAX_NUMBER_OF_TASKS = 20;

// Print Debug Task
constexpr const char* DEFAULT_PRINT_DEBUG_TASK_NAME = "PrintDebug";
constexpr int MAX_NUMBER_OF_COMPONENTS = 10;

// Smart Light
constexpr const char* DEFAULT_SMART_LIGHT_TASK_NAME = "SmartLight";
constexpr const char* SMART_LIGHT_FORCE_OFF_MSG = "System OFF.";
constexpr const char* SMART_LIGHT_HIGH_AMBIENT_LIGHT = "Ambient light detected, LED OFF.";
constexpr const char* SMART_LIGHT_ALWAYS_ON = "Always on enabled, LED ON.";
constexpr const char* SMART_LIGHT_MOVEMENT_DETECTED = "Movement detected, LED ON.";
constexpr const char* SMART_LIGHT_LED_TIMEOUT = "No momvement detected in a while, LED OFF.";
constexpr int LIGHT_OFF_DELAY = 3000; // ms
constexpr int LIGHT_SENSOR_THRESHOLD = 100;

// Smart Bridge Task
constexpr const char* DEFAULT_SMART_BRIDGE_TASK_NAME = "SmartBridge";

// Threshold levels are reveted, the sonar will measure from the bridge,
// the higher the water the smaller the measurement.
constexpr int WATER_LEVEL_1 = 50;
constexpr int WATER_LEVEL_2 = 25;
constexpr int WATER_LEVEL_MAX = 0;
constexpr int MESSAGE_LINES = 2;
constexpr timestamp_t PE_NORMAL = 2000;
constexpr timestamp_t PE_PREALARM = 1000;
constexpr timestamp_t PE_ALARM = 100;
constexpr timestamp_t PE_BEGIN = 0;
constexpr int WATER_LEVEL_READS = 5;

// Pins
constexpr int BUTTON_PIN = 12;
constexpr int POT_PIN = A0;
constexpr int SERVO_PIN = 9;
constexpr int SONAR_TRIGGER_PIN = 11;
constexpr int SONAR_ECHO_PIN = 10;
constexpr int PIR_PIN = 3;
constexpr int LED_A_PIN = 6;
constexpr int LED_B_PIN = 7;
constexpr int LED_C_PIN = 8;
constexpr int LIGHT_SENSOR_PIN = A1;

#endif