// Copyright (c) 2022 Esteban Cadic
// This code is licensed under MIT license (see LICENSE file for details)

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "wifi.h"
#include "mqtt.h"
#include "vfd.h"

void setup()
{
	Serial.begin(115200);

	wifiSetup();
	mqttSetup();
	vfdSetup();
}

void loop()
{
	mqttLoop();

	delay(50);
}