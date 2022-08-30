// Copyright (c) 2022 Esteban Cadic
// This code is licensed under MIT license (see LICENSE file for details)

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "wifi.h"
#include "credentials.h"

WiFiClient wifiClient;

void wifiSetup(void)
{
	WiFi.begin(WIFI_SSID, WIFI_PASS);

	Serial.println("Connecting to WiFi..");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println();
	Serial.print("Connected to the WiFi network! IP : ");
	Serial.println(WiFi.localIP());
}