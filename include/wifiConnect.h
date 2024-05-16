/**
 * @file wifiConnect.h
 * @author Dawson Burgess (dawsonhburgess@gmail.com), Lucien Lee, Alphonse Crittenden
 * 
 * @brief This header file is only for the wifi information for the project.
 * It will not be pushed on additional commits after the first one
 * 
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// #define LUCIENMOBILE 1
//#define LUCIENNETWORK 1

#define ALNET0 1

//#define DAWSON_MOBILE 1
//#define DAWSON_NETWORK



// Networks for WIFI connection for Lucien 
#ifdef LUCIENMOBILE
    // Add your mobile hotspot information here
    #define SECRET_SID "Memento Mori"
    #define SECRET_PASS "Gabagool"
#endif

#ifdef LUCIENNETWORK
    // Add your personal network here
    #define SECRET_SSID "Ziply-0700"
    #define SECRET_PASS "415sAlmon"
#endif

#if defined(ALNET0)
    #define SECRET_SSID "Cougar Den"
    #define SECRET_PASS "nestvalley025"
#elif defined(ALNET1)
    #define SECRET_SSID "ALS-PC"
    #define SECRET_PASS "aaaaaaaa"
#endif

// WIFI connectivity via mobile hotspot for Dawson 
#ifdef DAWSON_MOBILE
    // Add your mobile hotspot information here
    #define SECRET_SSID "Dawsons_Phone"
    #define SECRET_PASS "quentintanner"
#endif

// WIFI connectivity via home network for Dawson 
#ifdef DAWSON_NETWORK
    // Add your mobile hotspot information here
    #define SECRET_SSID "Gritman State University"
    #define SECRET_PASS "YUMYUMCRANS"
#endif
