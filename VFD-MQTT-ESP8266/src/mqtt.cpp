// Copyright (c) 2022 Esteban Cadic
// This code is licensed under MIT license (see LICENSE file for details)

#include <Arduino.h>
#include <PubSubClient.h>

#include "mqtt.h"
#include "wifi.h"
#include "vfd.h"
#include "credentials.h"

PubSubClient mqttClient;

// When a new MQTT message is published
void mqttCallback(char *topic, byte *payload, unsigned int length)
{
	vfdClear();

	Serial.print("Message arrived in topic: ");
	Serial.println(topic);

	Serial.print("Message: ");
	for (unsigned int i = 0; i < length; i++)
	{
		Serial.print((char)payload[i]);
		vfdWrite(payload[i]);
	}

	Serial.println();
	Serial.println("-----------------------");
}

void mqttSetup(void)
{
	mqttClient.setClient(wifiClient);
	mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
	mqttClient.setCallback(mqttCallback);

	while (!mqttClient.connected())
	{
		Serial.println("Connecting to MQTT...");

		if (mqttClient.connect(MQTT_CLIENT, MQTT_USER, MQTT_PASS))
		{
			Serial.println("Connected to the MQTT broker!");
		}
		else
		{
			Serial.print("Failed with state ");
			Serial.println(mqttClient.state());
			delay(2000);
		}
	}

	mqttClient.subscribe(MQTT_CHAN);
}

void mqttLoop(void)
{
	mqttClient.loop();
}