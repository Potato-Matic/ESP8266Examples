// WiFi information
const char WIFI_SSID[] = "<your WiFi SSID here>";
const char WIFI_PSK[] = "<you WiFi PSK password here>";

// Remote site information
const char fingerprint[] = "66 53 78 0C FF 9B F4 FB FE 3F 6F 0B E2 05 EC E4 8F C9 C4 55"; //google's fingerprint, as of this time of writing
const char https_site[] = "https://script.google.com/macros/s/edit_to_match_your_google_scripts_url/exec";

//POST config data
const char key[] = "<put your key here>";
const char app[] = "<Temperature+Logging>";

//time between requests
long interval = 600000; //ten min POST interval

//delay when checking WiFi
long WiFiDelay = 5000;

//DHT sensor config
#define DHTPIN 2
#define DHTTYPE DHT11
