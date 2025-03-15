#ifndef ESP32S_LIBRARY_H
#define ESP32S_LIBRARY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <VL53L0X.h>
#include <LittleFS.h>

#define SHT31_ADDR 0x44
#define MPU6050_ADDR 0x68
#define BATTERY_PIN 35

// TFT Display
class TFT_Display {
public:
    TFT_Display(Adafruit_ST7735 &tft) : tft(tft) {}
    void begin();
    void printText(const char *text, int x, int y, uint16_t color);
private:
    Adafruit_ST7735 &tft;
};

// Temperature & Humidity Sensor
class TempHumiditySensor {
public:
    bool begin();
    float readTemperature();
    float readHumidity();
private:
    Adafruit_SHT31 sht31;
};

// IMU Sensor (MPU6050)
class IMUSensor {
public:
    bool begin();
    sensors_event_t getAccelData();
private:
    Adafruit_MPU6050 mpu;
};

// Laser Distance Sensor (VL53L0X)
class LaserDistanceSensor {
public:
    bool begin();
    uint16_t readDistance();
private:
    VL53L0X sensor;
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
