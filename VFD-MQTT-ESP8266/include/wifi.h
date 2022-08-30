// Copyright (c) 2022 Esteban Cadic
// This code is licensed under MIT license (see LICENSE file for details)

#ifndef __WIFI_H__
#define __WIFI_H__

#include <ESP8266WiFi.h>

extern WiFiClient wifiClient;

// Setup WiFi client
extern void wifiSetup(void);

#endif