#ifndef ESP32S_LIBRARY_H
#define ESP32S_LIBRARY_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SHT31.h>
#include <LITTLEFS.h>

// Pin definitions
#define TFT_CS   5
#define TFT_RST  4
#define TFT_DC   2
#define SHT31_ADDR 0x44
#define MPU6050_ADDR 0x68
#define FLASH_CS 15
#define BUTTON1  14
#define BUTTON2  27
#define BATTERY_PIN 34

// TFT Display
class TFT_Display {
public:
    Adafruit_ST7735 tft;
    TFT_Display() : tft(TFT_CS, TFT_DC, TFT_RST) {}
    void begin();
    void printText(const char *text, int x, int y, uint16_t color);
};

// SHT31 Sensor
class TempHumiditySensor {
public:
    Adafruit_SHT31 sht31;
    bool begin();
    float readTemperature();
    float readHumidity();
};

// MPU6050 Sensor
class IMUSensor {
public:
    Adafruit_MPU6050 mpu;
    bool begin();
    sensors_event_t getAccelData();
};

// VL53L0X Laser Distance Sensor
class LaserDistanceSensor {
public:
    VL53L0X sensor;
    bool begin();
    uint16_t readDistance();
};

// Flash Storage
class FlashMemory {
public:
    bool begin();
    bool writeFile(const char *path, const char *message);
};

// Button Handler
class ButtonHandler {
public:
    ButtonHandler(uint8_t pin);
    bool isPressed();
private:
    uint8_t pin;
};

// Battery Monitor
class BatteryMonitor {
public:
    float readVoltage();
};

#endif
