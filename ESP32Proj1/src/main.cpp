

#include <WiFi.h>
#include <WebServer.h> 

// SSID and password of Wifi connection:
const char* ssid = "Keanu's iPhone";
const char* password = "hello123";

String website = "";
String website1 = "<!DOCTYPE html><html><head><title>Page Title</title></head><body style='background-color:white'><span style='color:black;'><h1>Sensor Readings</h1><p>The dry bulb temperature is: ";
String website2 = "</p><p>The wet bulb temperature is: ";
String website3 = "</p><p>The wind speed is: ";
String website4 = "</p><p>The radiometer value is: ";
String website5 = "</p></span></body></html>";

int drytemp = 0;
int wettemp = 0;
int windspeed = 0;
int radiometer = 0;
int interval = 5000; 
unsigned long previousMillis = 0; 

WebServer server(80);

void setup() {
  Serial.begin(115200);                 
 
  WiFi.begin(ssid, password);
  Serial.println("Establishing connection to WiFi with SSID: " + String(ssid));
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Connected to network with IP address: ");
  Serial.println(WiFi.localIP());
  
  website = website1 + String(drytemp) + website2 + String(wettemp) + website3 + String(windspeed) + website4 + String(radiometer) + website5;
  server.on("/", []() {
  server.send(200, "text/html", website);
  });
  server.begin(); 
}

void loop() {
  server.handleClient();  

  unsigned long currentMillis = millis(); 
  if ((unsigned long)(currentMillis - previousMillis) >= interval) { 
    drytemp = random(90,100);
    wettemp = random(80,90);
    windspeed = random(0,5);
    radiometer = random(0,10);
    website = website1 + String(drytemp) + website2 + String(wettemp) + website3 + String(windspeed) + website4 + String(radiometer) + website5;
  }
}
