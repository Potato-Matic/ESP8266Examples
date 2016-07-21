#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

#include <config.h>

HTTPClient http;

long timestamp;

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial started.");

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
    Serial.print("Preforming a GET request on: ");
    Serial.println(https_site);

    if (!getPage())
    {
      Serial.println("GET request failed.");
    }
    else
    {
      Serial.println("GET request finished.");
    }

    timestamp = millis();
  }
}

bool getPage()
{

  if(!http.begin(https_site, fingerprint))
  {
    return false;
  }

  Serial.print("GET returned code:");
  Serial.println(http.GET());
  Serial.println(http.getString());
  http.end();

  return true;
}
