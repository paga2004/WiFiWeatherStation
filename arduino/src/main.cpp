#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>


#include "settings.h"

#define HYT939_ADDR 0x28





void setup()
{

    Serial.begin(9600);

    Wire.begin();

    //Connect D0 with rst
    pinMode(D0, WAKEUP_PULLUP);

    Serial.println();
    Serial.println();
    Serial.println();

    for (uint8_t t = 4; t > 0; t--)
    {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }


    //turn off AP (access point)
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("");
}

void loop()
{
    

//Skalierungsfaktoren laut Datenblatt
#define TFACTOR 99.2909
#define TDELTA 40.0
#define HFACTOR 163.83

    unsigned int traw;
    unsigned int hraw;

    double temp;
    double hum;
    int i;
    unsigned char buffer[4];

    //Messung starten
    Wire.beginTransmission(HYT939_ADDR); // transmit to device #44 (0x2c)
    Wire.endTransmission();              // stop transmitting

    //100ms warten
    delay(100);

    //4 Bytes vom Sensor lesen

    Wire.requestFrom(HYT939_ADDR, 4, true);

    i = 0;

    while (Wire.available())
    {

        char c = Wire.read(); // receive a byte as character

        buffer[i] = c;

        i++;
    }

    //Rohdaten aus Puffer lesen
    traw = buffer[2] * 256 + buffer[3];
    hraw = buffer[0] * 256 + buffer[1];

    //Daten laut Datenblatt maskieren

    traw &= 0xfffc;
    hraw &= 0x3fff;

    traw = traw / 4;

    /*
//Rohdaten ausgeben, zur eventuellen Fehlersuche
Serial.print("\r\nTemp Raw:");
Serial.println(traw);
Serial.print("Hum Raw:");
Serial.println(hraw);
*/

    //Rohdaten Umrechnen
    temp = (double)traw / TFACTOR;
    temp = temp - TDELTA;

    hum = (double)hraw / HFACTOR;

    Serial.print("Temp:");
    Serial.print(temp);
    Serial.print(';');

    Serial.print("Hum:");
    Serial.print(hum);

    WiFiClient client;

    HTTPClient http;

    Serial.print("\n\n[HTTP] begin...\n");
    if (http.begin(client, url))
    {


        int httpCode = http.POST("temp=" + String(temp) + "&humidity=" + String(hum));

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] POST... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                String payload = http.getString();
                Serial.println(payload);
            }
        }
        else
        {
            Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
        Serial.printf("Sleeping for %d seconds...\n", sleepSeconds);
        ESP.deepSleep(sleepSeconds * 1000000);
    }
    else
    {
        Serial.printf("[HTTP} Unable to connect\n");
    }
}
