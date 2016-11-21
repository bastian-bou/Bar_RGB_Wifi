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

//chaine de caractère contenant la page HTML
String web_page = "";

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
  web_page = "<h1>Commande de la bar LED</h1>";
  web_page += " <p>";
  web_page += "     <select name=\"formal\" onchange=\"javascript:handleSelect(this)\">";
  web_page += "         <option >Choix de la luminosité</option>";
  web_page += "         <option value=\"Val0\">0%</option>";
  web_page += "         <option value=\"Val1\">25%</option>";
  web_page += "         <option value=\"Val2\">50%</option>";
  web_page += "         <option value=\"Val3\">75%</option>";
  web_page += "         <option value=\"Val4\">100%</option>";
  web_page += "     </select>";
  web_page += " </p>";
  web_page += "<script type=\"text/javascript\">";
  web_page += "function handleSelect(elm)";
  web_page += "{";
  web_page += "window.location = elm.value;";
  web_page += "}";
  web_page += "</script>";
  web_page += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"Test1\"><button>ON</button></a>&nbsp;<a href=\"Test2\"><button>OFF</button></a></p>";

  server.send(200, "text/html", web_page);
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
//lancement de la page web
  server.on("/", handleRoot);

  server.on("/Val0", [](){
    server.send(200, "text/html", web_page);
    ws2812fx.setBrightness(0);
  });
  server.on("/Val1", [](){
    server.send(200, "text/html", web_page);
    ws2812fx.setBrightness(64);
  });
  server.on("/Val2", [](){
    server.send(200, "text/html", web_page);
    ws2812fx.setBrightness(128);
  });
  server.on("/Val3", [](){
    server.send(200, "text/html", web_page);
    ws2812fx.setBrightness(192);
  });
  server.on("/Val4", [](){
    server.send(200, "text/html", web_page);
    ws2812fx.setBrightness(255);
  });

  
  server.begin();
  Serial.println("Serveur accessible");
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
