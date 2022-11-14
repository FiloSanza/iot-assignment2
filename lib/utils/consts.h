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

// Scheduler
constexpr int MAX_NUMBER_OF_TASKS = 20;

// Print Debug Task
constexpr const char* DEFAULT_PRINT_DEBUG_TASK_NAME = "PrintDebug";
constexpr int MAX_NUMBER_OF_COMPONENTS = 10;

// Smart Light
constexpr const char* DEFAUL_SMART_LIGHT_TASK_NAME = "SmartLight";
constexpr const char* SMART_LIGHT_FORCE_OFF_MSG = "System OFF.";
constexpr const char* SMART_LIGHT_HIGH_AMBIENT_LIGHT = "Ambient light detected, LED OFF.";
constexpr const char* SMART_LIGHT_MOVEMENT_DETECTED = "Movement detected, LED ON.";
constexpr const char* SMART_LIGHT_LED_TIMEOUT = "No momvement detected in a while, LED OFF.";
constexpr int LIGHT_OFF_DELAY = 3000; // ms
constexpr int LIGHT_SENSOR_THRESHOLD = 100;

// Smart Bridge Task
constexpr int WATER_LEVEL_1 = 0;
constexpr int WATER_LEVEL_2 = 10;
constexpr int WATER_LEVEL_MAX = 100;
constexpr int MESSAGE_LINES = 2;
constexpr timestamp_t PE_NORMAL = 10000;
constexpr timestamp_t PE_PREALARM = 100;
constexpr timestamp_t PE_ALARM = 10; 
constexpr timestamp_t PE_BEGIN = 0;

#endif