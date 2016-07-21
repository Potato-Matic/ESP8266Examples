// WiFi information
const char WIFI_SSID[] = "<your WiFi SSID here>";
const char WIFI_PSK[] = "<you WiFi PSK password here>";

// Remote site information
const char fingerprint[] = "66 53 78 0C FF 9B F4 FB FE 3F 6F 0B E2 05 EC E4 8F C9 C4 55"; //example fingerprint for google.ca
const char https_site[] = "https://www.google.ca";

//time between requests
long interval = 5000;

//delay when checking WiFi
long WiFiDelay = 5000;
