//----------------------------------------------------------
//
// Gestion barre à leds multicolore
//
// Test ok 1/08/16
// Version serveur Web
//
//To do list : 
//            -si wifi indisponible, l'ESP doit créer un wifi pour donner la possibilité à l'utilisateur de se connecter et de reconfigurer les paramètres wifi de la box
//            -faire clignoter certaines LEDs pour indiquer l'adresse IP de la lampe ou seulement le dernier nombre
//            -
//            -
// 
// Compilateur version 1.6.10
//----------------------------------------------------------

#include <WS2812FX.h>
#include <ESP8266WiFi.h>

//Identifiants du WiFi de la maison
const char* ssid     = "Led_RGB_wifi";
const char* password = "tours2016";

//Nombre de WS2812
#define LED_COUNT 78
// Pin sortie données
#define LED_PIN 9

//Instanciation de l'objet représentant le ruban
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 10000; 

int effet = -1;

//Configuration
void setup() {
// Initialisation
  ws2812fx.init();
//Luminosité sur 1/4 du maximun (255)
  ws2812fx.setBrightness(25);
// Réglage de la vitesse des effets  
  ws2812fx.setSpeed(500);
// Connexion à la box WiFi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    //------------------REALISER UN AFFICHAGE LED PARTICULIER EN ATTENDANT D'ETRE CONNECTE AU WIFI--------------------------
  }
  //--------------------REALISER UN AFFICHAGE LED PARTICULIER POUR INFORMER LA CONNEION AU WIFI-----------------------------
//Un arc en ciel glissant  
  ws2812fx.setColor(255, 255, 0);
  ws2812fx.setMode(FX_MODE_CHASE_RAINBOW);
// Demarrage  
  ws2812fx.start();
  Serial.begin(115200);
}

void loop() {

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
