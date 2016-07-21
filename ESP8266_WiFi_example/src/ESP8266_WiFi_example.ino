#include <ESP8266WiFi.h>

#include <config.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial started.");

  Serial.println("WiFi init.");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  Serial.print("Starting WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Failed.");
    Serial.print("Retrying WiFi...");
    delay(1000);
  }
  Serial.println("Done.");
}

void loop()
{

}
