/**
 * @file gps.h
 * @author Dawson Burgess (dawsonhburgess@gmail.com)
 * @brief This is for all of the GPS functionality so we can get the weather data based on where the GPS
 * is located. This will be the main driving force for the entire project, as much
 * of the functionality of the assignment is going to be driven based off of the GPS
 * 
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <TinyGPSPlus.h>

// Global Defines
float glongitude;
float glattitude; 

TinyGPSPlus gps;
HardwareSerial GPSSerial(2);
int getGPSTrue = 1;

// Include the other libraries
#include "buttons.h"

/**
 * @brief This function will get the longitude and lattitude from the GPS
 * 
 * @return int; returns 1 if connection is not established and location is invalid
 */
int getGPSCoord(){
    while(GPSSerial.available() > 0){
        gps.encode(GPSSerial.read());
    }

    if(gps.location.isValid()){
        // Print out the GPS information here
        glattitude = gps.location.lat();
        glongitude = gps.location.lng();

        //set time offset
        setOffset();
        return 0;
    }else{
        return 1;
    }
}

/**
 * @brief This is the task to run the GPS connunication for testing
 * 
 * @param pvParam standard param for FreeRTOS
 */
void gpsInfoTask(void* pvParam){
    int startButtonTask = 0;
    while(true){
        getGPSTrue = getGPSCoord();  
        if(getGPSTrue == 0){
            Serial.print(glattitude); Serial.print(" , "); Serial.println(glongitude);
            if(startButtonTask == 0){
                xTaskCreate(getButtonPressedTask, "getButtonPressedTask", 4096, NULL, 1, NULL);
                xTaskCreate(testLightSensorTask, "testLightSensorTask", 4096, NULL, 2, NULL);
                xTaskCreate(getTemperatureTask, "getTemperatureTask", 4096, NULL, 2, NULL);
                startButtonTask = 1;
            }
        }else{
            Serial.println("ERROR: There has not been a location specified for the GPS Coordinates...");
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

/**
 * @brief function for handling and storing gps data on webserver 
 * 
 */
void handleGPSData() {
    JsonDocument doc;
    doc["lat"] = String(glattitude, 6); 
    doc["lng"] = String(glongitude, 6);

    String output;
    serializeJson(doc, output);
    server.send(200, "application/json", output);
}