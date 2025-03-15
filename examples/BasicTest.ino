#include <ESP32S_Library.h>

// Khởi tạo đối tượng phần cứng
TFT_Display display;
TempHumiditySensor tempHumid;
IMUSensor imu;
LaserDistanceSensor laser;
FlashMemory flash;
ButtonHandler button1(BUTTON1);
ButtonHandler button2(BUTTON2);
BatteryMonitor battery;

void setup() {
    Serial.begin(115200);
    
    // Khởi động màn hình TFT
    display.begin();
    display.printText("ESP32S Ready", 10, 10, ST77XX_WHITE);
    
    // Khởi động cảm biến nhiệt độ và độ ẩm
    if (tempHumid.begin()) {
        Serial.println("SHT31 Sensor Ready!");
    } else {
        Serial.println("Failed to initialize SHT31.");
    }

    // Khởi động cảm biến gia tốc
    if (imu.begin()) {
        Serial.println("MPU6050 Sensor Ready!");
    } else {
        Serial.println("Failed to initialize MPU6050.");
    }

    // Khởi động cảm biến đo khoảng cách
    if (laser.begin()) {
        Serial.println("VL53L0X Sensor Ready!");
    } else {
        Serial.println("Failed to initialize VL53L0X.");
    }

    // Khởi động bộ nhớ Flash
    if (flash.begin()) {
        Serial.println("Flash Memory Ready!");
    } else {
        Serial.println("Failed to initialize Flash Memory.");
    }
}

void loop() {
    // Đọc dữ liệu từ cảm biến nhiệt độ và độ ẩm
    float temp = tempHumid.readTemperature();
    float humid = tempHumid.readHumidity();

    // Đọc dữ liệu từ cảm biến khoảng cách
    uint16_t distance = laser.readDistance();

    // Đọc điện áp pin
    float voltage = battery.readVoltage();

    // Kiểm tra nếu nút được nhấn
    bool button1Pressed = button1.isPressed();
    bool button2Pressed = button2.isPressed();

    // Hiển thị trên Serial Monitor
    Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
    Serial.print("Humidity: "); Serial.print(humid); Serial.print(" %, ");
    Serial.print("Distance: "); Serial.print(distance); Serial.print(" mm, ");
    Serial.print("Battery: "); Serial.print(voltage); Serial.print(" V, ");
    Serial.print("Button1: "); Serial.print(button1Pressed ? "Pressed" : "Not Pressed");
    Serial.print(", Button2: "); Serial.println(button2Pressed ? "Pressed" : "Not Pressed");

    // Cập nhật hiển thị lên màn hình TFT
    display.printText("Temp: ", 10, 30, ST77XX_WHITE);
    display.printText(String(temp).c_str(), 60, 30, ST77XX_WHITE);
    
    display.printText("Humid: ", 10, 50, ST77XX_WHITE);
    display.printText(String(humid).c_str(), 60, 50, ST77XX_WHITE);

    display.printText("Dist: ", 10, 70, ST77XX_WHITE);
    display.printText(String(distance).c_str(), 60, 70, ST77XX_WHITE);

    display.printText("Batt: ", 10, 90, ST77XX_WHITE);
    display.printText(String(voltage).c_str(), 60, 90, ST77XX_WHITE);

    display.printText("BTN1: ", 10, 110, button1Pressed ? ST77XX_GREEN : ST77XX_RED);
    display.printText(button1Pressed ? "ON" : "OFF", 60, 110, button1Pressed ? ST77XX_GREEN : ST77XX_RED);

    display.printText("BTN2: ", 10, 130, button2Pressed ? ST77XX_GREEN : ST77XX_RED);
    display.printText(button2Pressed ? "ON" : "OFF", 60, 130, button2Pressed ? ST77XX_GREEN : ST77XX_RED);

    delay(1000);
}
