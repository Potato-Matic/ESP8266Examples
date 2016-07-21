#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <config.h>

long timestamp;
bool connected = false;

WiFiClient client;

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

  // Attempt to connect to website
  if (!getPage())
  {
    Serial.println("GET request failed.");
  }
  else
  {
    connected = true;
  }
  timestamp = millis();
}

void loop()
{
  while(client.available())
  {
    char c = client.read();
    Serial.print(c);
    delay(0);
  }

  // If the server has disconnected, stop the client and WiFi
  if(!client.connected() && connected)
  {
    Serial.println();
    client.stop();
    Serial.println("Finished GET request.");
    connected = false;
  }

  if((millis() > (timestamp + interval)) && !connected)
  {
    if (!getPage())
    {
      Serial.println("GET request failed.");
    }
    else
    {
      connected = true;
    }
    timestamp = millis();
  }
}

// Perform an HTTP GET request to a remote page
bool getPage()
{
  if (!client.connect(http_site, http_port))
  {
    return false;
  }

  // Make an HTTP GET request
  client.println("GET / HTTP/1.1");
  Serial.println("REQUESTING:GET / HTTP/1.1");
  client.print("Host: ");
  Serial.print("REQUESTING:Host: ");
  client.println(http_site);
  Serial.print("REQUESTING:");
  Serial.println(http_site);
  client.println("Connection: close");
  Serial.println("REQUESTING:Connection: close");
  client.println();
  Serial.println("REQUESTING:");

  return true;
}
