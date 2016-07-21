#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"

#include <config.h> //you will have to set up this file using the provided template

/*
This post example is intended to post to the Google Scripts logging service,
the source of which should also be available on github.
(See the github readme file for more)

It posts some values obtained from a DHT11 temperature/humidity sensor to one
of the first working 'apps' that have been implemented.
(the temperature logger)
*/

HTTPClient http;
DHT dht(DHTPIN, DHTTYPE);

long timestamp;

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial started.");

  dht.begin();
  Serial.println("DHT sensor library started.");

  Serial.println("WiFi init.");
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.println(".");
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  Serial.print("Waiting for Wifi to connect...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed.");
    Serial.print("Waiting for Wifi to connect...");
    delay(WiFiDelay);
  }
  Serial.println("Done.");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  timestamp = millis();
}

void loop()
{
  if(millis() > (timestamp + interval))
  {
    Serial.println("Reading DHT Sensor.");

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
      Serial.println("Failed to read from DHT sensor.");
    }
    else
    {
      Serial.println("Sensor results:");
      Serial.print("\tTemperature: ");
      Serial.println(dht.readTemperature());
      Serial.print("\tHumidity: ");
      Serial.println(dht.readHumidity());

      Serial.print("Preforming a POST request on: ");
      Serial.println(https_site);

      if (!POSTData(dht.readTemperature(), dht.readHumidity()))
      {
        Serial.println("POST request failed.");
      }
      else
      {
        Serial.println("POST request finished.");
      }
    }

    timestamp = millis();
  }
}

bool POSTData(float temp, float humid)
{

  if(!http.begin(https_site, fingerprint))
  {
    return false;
  }

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String data = "";//construction of the URL encoded data to be POSTed
  data += "Temperature=";
  data += temp;
  data += "&Humidity=";
  data += humid;
  data += "&key=";
  data += key;
  data += "&app=";
  data += app;
  Serial.print("POST returned code:");
  Serial.println(http.POST(data));
  Serial.println("Returned data:");
  Serial.println(http.getString());
  http.end();

  return true;
}
