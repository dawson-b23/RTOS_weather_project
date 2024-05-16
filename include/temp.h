/**
 * @file temp.h
 * @author Dawson Burgess (dawsonhburgess@gmail.com)
 * 
 * @brief This is for getting data from the tempurature and humidity sensor
 * and relaying that information to other parts of the program
 * 
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Wire.h"
#include <math.h>

// Define the registers for temp/hum sensor data
#define HDC1080ADDRESS 0x40
#define MANDEVICEIDREG 0xFE
#define SERIALREG1 0xFB
#define SERIALREG2 0xFC
#define SERIALREG3 0xFD
#define DEVICEID 0xFF
#define TEMPERATUREREG 0x00
#define CONFIGREG 0x02
#define HUMIDREG 0x01

// Global tempurature + humidity
float temperatureCelcius = 0;
float temperatureFarenheit = 0;
float humidity_ = 0;

/**
 * @brief Function to get and return the temperature in degrees celsius
 * 
 * @return float; temperature in celcius
 */
float getTempC(){
    Wire.beginTransmission(HDC1080ADDRESS);
    Wire.write(TEMPERATUREREG);
    Wire.endTransmission();

    // Delay to allow the sensor to get the data needed
    vTaskDelay(pdMS_TO_TICKS(100));

    // Get the temperature value
    Wire.requestFrom(HDC1080ADDRESS, 2);
    uint16_t rawTemp = Wire.read() << 8 | Wire.read();

    float temperature = ((float)rawTemp / 65536.0) * 165.0 - 40.0;

    return temperature;
}

/**
 * @brief Function to get and return the humidity
 * 
 * @return float; humidty
 */
float getHumidity()
{
    Wire.beginTransmission(HDC1080ADDRESS);
    Wire.write(HUMIDREG);
    Wire.endTransmission();

    // Delay to allow the sensor to get the data needed
    vTaskDelay(pdMS_TO_TICKS(100));


    // Get the humidity value
    Wire.requestFrom(HDC1080ADDRESS, 2);
    uint16_t rawHum = Wire.read() << 8 | Wire.read();

    float humidity = ((float)rawHum / 65536.0) * 100.0;

    return humidity;
}

/**
 * @brief Function to get the degrees in F
 * 
 * @param c ; temperature in C
 * @return float ; temperatre in F
 */
float getTempF(float c){
    float far = c * 9 / 5 + 32;
    return far;
}

/**
 * @brief Task to update the temperature information
 * 
 * @param pvParam standard param for FreeRTOS
 */
void getTemperatureTask(void* pvParam){
    while(true){
        // read the temperature sensor
        temperatureCelcius = getTempC();
        Serial.print("The temperature in C is: "); Serial.println(temperatureCelcius);
        temperatureFarenheit = getTempF(temperatureCelcius);
        Serial.print("The temperature in F is: "); Serial.println(temperatureFarenheit);

        if(currentScreen == 3)
        {
            displayRoomTemp();
        }

        // Delay/update every 5 seconds
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

/**
 * @brief function for handling and storing temperature/humidity data on webserver 
 * 
 */
void handleRoomTemp() {
    JsonDocument doc;
    doc["temp"] = String(temperatureFarenheit, 2);

    String output;
    serializeJson(doc, output);
    server.send(200, "application/json", output);
}

