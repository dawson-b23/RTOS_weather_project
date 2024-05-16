/**
 * @file index.h
 * @author Alphonse Crittenden
 * 
 * @brief This is the webpage for the ESP32 site
 * 
 * We can display whatever we want on this website that will be hosted on the ESP32
 * 
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
const char index_html[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
    <head>
        <title>Weather Data Server</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="data:,">
        <style>
            html {
                font-family: Arial, Helvetica, sans-serif;
                text-align: center;
            }
            body {
                background-color: black;
            }
            h1 {
                font-size: 1.8rem;
                color: white;
            }
            body {
                margin: 0;
            }
        </style>
    </head>
    <body>
        <h1>Weather Data Server - RTOS Final Project</h1>
        <h1>By: Dawson Burgess, Alphonse Crittenden, and Lucien Lee</h1>
    </body>
</html>
)=====";