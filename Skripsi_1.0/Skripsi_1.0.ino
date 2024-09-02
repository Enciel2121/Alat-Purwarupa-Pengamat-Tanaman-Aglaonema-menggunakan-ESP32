#define BLYNK_TEMPLATE_ID "TMPL6vykiTo6x"
#define BLYNK_TEMPLATE_NAME "Monitor Aglaonema"
#define BLYNK_AUTH_TOKEN "Rt4atWe9B3XixmTdxu3eF80W2cwuLnR-"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define ldrPin 32 // Sensor Cahaya
#define soilPin 34 // Sensor Kelembaban
#define waterPin 4 // Pompa Air

char ssid[] = "fhtdxy";
char pass[] = "asdfg12345";

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(waterPin, OUTPUT);
  digitalWrite(waterPin, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendSensor);
}

void sendSensor()
{

  int ldrAnalog = analogRead(ldrPin);
  int soilAnalog = analogRead(soilPin);

  Serial.print(ldrAnalog);
  Serial.print(";");
  Serial.println(soilAnalog);
  
  if (soilAnalog > 3000) {
    digitalWrite(waterPin, LOW);
  } else {
    digitalWrite(waterPin, HIGH);
  }

  Blynk.virtualWrite(V7, ldrAnalog);
  Blynk.virtualWrite(V8, soilAnalog);
}

void loop()
{
  Blynk.run();
  sendSensor();
}
