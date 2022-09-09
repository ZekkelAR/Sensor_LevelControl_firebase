/*
 * Project Arduino Relay + Level Control
 * Update :
 * [1] Added Danger Tools, if OFF Button pressed in website / Android Application
 *     Relay will off
 * 
 * 0xMoirai x Metalurgi2020
 */
 

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Auth key 
#define FIREBASE_HOST "Your Firebase Host"
#define FIREBASE_AUTH "Your firebase Auth"
#define WIFI_SSID "MARSELA"
#define WIFI_PASSWORD "P@ssw0rd"


//Pin Relay and Level Control
static const uint8_t RELAY_PIN   = 16;
#define echoPin 4 
#define trigPin 5 


//Attachment for Level Control
long duration; 
int distance; 

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Connect to Firebase account
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  Serial.print("Distance: ");
  Serial.println(String(distance));
  Firebase.setString("/DATA/SENSOR_LEVEL", String(distance));  
  
  if (distance < 17){
      int fireStatus = 0;
      fireStatus = Firebase.getInt("/DATA/PUMP_ONE");
      if (fireStatus == 0){
        digitalWrite(RELAY_PIN, HIGH);
      }
      else{
        digitalWrite(RELAY_PIN, LOW);
      }
  }
  else{
    digitalWrite(RELAY_PIN, HIGH);
  }
  delay(1000);
}
