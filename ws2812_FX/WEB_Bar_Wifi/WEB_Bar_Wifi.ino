//----------------------------------------------------------
//
// Gestion barre à leds multicolore
//
// Test ok 1/08/16
// 
// Compilateur version 1.6.10
//----------------------------------------------------------

#include <WS2812FX.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "Led_RGB";
const char *password = "Tours2016";

ESP8266WebServer server(80);

//Nombre de WS2812
#define LED_COUNT 78
// Pin sortie données
#define LED_PIN 0

//Instanciation de l'objet représentant le ruban
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 10000; 

int effet = -1;

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

//Configuration
void setup() {
// Initialisation
  ws2812fx.init();
//Luminosité sur 1/4 du maximun (255)
  ws2812fx.setBrightness(25);
// Réglage de la vitesse des effets  
  ws2812fx.setSpeed(500);
//Un arc en cile glissant  
  ws2812fx.setColor(255, 255, 0);
  ws2812fx.setMode(FX_MODE_CHASE_RAINBOW);
// Demarrage  
  ws2812fx.start();
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.begin();
}

void loop() {

  server.handleClient();
  
//Rafraichissement de l'animation  
  ws2812fx.service();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    ws2812fx.stop();
    effet++;
    if(effet >= MODE_COUNT) effet = 0;
    Serial.println(ws2812fx.getModeName(effet));
    ws2812fx.setMode(effet);
    ws2812fx.start();
    previousMillis = currentMillis;
  }
}
