#include "ESP32S_Library.h"

// TFT Display
void TFT_Display::begin() {
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);
}

void TFT_Display::printText(const char *text, int x, int y, uint16_t color) {
    tft.setTextColor(color);
    tft.setCursor(x, y);
    tft.print(text);
}

// Temperature & Humidity Sensor
bool TempHumiditySensor::begin() {
    return sht31.begin(SHT31_ADDR);
}

float TempHumiditySensor::readTemperature() {
    return sht31.readTemperature();
}

float TempHumiditySensor::readHumidity() {
    return sht31.readHumidity();
}

// IMU Sensor (MPU6050)
bool IMUSensor::begin() {
    return mpu.begin(MPU6050_ADDR);
}

sensors_event_t IMUSensor::getAccelData() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    return a;
}

// Laser Distance Sensor (VL53L0X)
bool LaserDistanceSensor::begin() {
    Wire.begin();
    return sensor.init();
}

uint16_t LaserDistanceSensor::readDistance() {
    return sensor.readRangeSingleMillimeters();
}

// Flash Storage
bool FlashMemory::begin() {
    return LittleFS.begin();
}

bool FlashMemory::writeFile(const char *path, const char *message) {
    File file = LittleFS.open(path, "w");
    if (!file) return false;
    file.print(message);
    file.close();
    return true;
}

// Button Handler
ButtonHandler::ButtonHandler(uint8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool ButtonHandler::isPressed() {
    return digitalRead(pin) == LOW;
}

// Battery Monitor
float BatteryMonitor::readVoltage() {
    int adcValue = analogRead(BATTERY_PIN);
    return (adcValue / 4095.0) * 7.4;
}
