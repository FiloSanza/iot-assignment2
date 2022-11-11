#ifndef __CONSTS_H_INCLUDED
#define __CONSTS_H_INCLUDED

// Light Sensor
constexpr int VIN = 5;
constexpr int LIGHT_SENSOR_RESITOR = 10000;

// Button
constexpr int BUTTON_BOUNCING_DELAY = 50;

// LCD
constexpr int LCD_I2C_ADDRESS = 0x27;
constexpr int DEFAULT_LCD_ROWS = 2;
constexpr int DEFAULT_LCD_COLUMNS = 16;

// Sonar
constexpr int MAX_DISTANCE = 100;

// Scheduler
constexpr int MAX_NUMBER_OF_TASKS = 20;

// Print Debug Task
constexpr int MAX_NUMBER_OF_COMPONENTS = 10;

#endif