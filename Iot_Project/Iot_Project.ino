#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
char BLYNK_TOKEN[] = "9LH61pYPxKyv7yn-k9Xl74Ry04rrVIYi";
char WIFI_ADI[] = "TurkTelekom_TPACE2_2.4GHz";
char WIFI_SIFRE[] = "d4uAWbhTVHj3";

BlynkTimer timer;

#define GAZ_SENSORU_PIN A0
#define YESIL_LED_PIN 14 //D5
#define KIRMIZI_LED_PIN 12 //D6
#define BUZZER_PIN 0 //D3
#define Sinir 450

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_TOKEN, WIFI_ADI, WIFI_SIFRE);
  pinMode(YESIL_LED_PIN, OUTPUT);
  pinMode(KIRMIZI_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  timer.setInterval(1000L, VeriYolla);
}

void loop() {
  timer.run();
  Blynk.run();
}
void VeriYolla() {
  int veri = analogRead(GAZ_SENSORU_PIN);
  Blynk.virtualWrite(V0, veri);
  if (veri > Sinir) {
    Blynk.notify("Gaz Sensörü Çalıştı!");
    digitalWrite(YESIL_LED_PIN, 0);
    for(int i=0;i<3;i++){
      digitalWrite(KIRMIZI_LED_PIN, 1);
      tone(BUZZER_PIN, 1000);
      delay(200);
      digitalWrite(KIRMIZI_LED_PIN, 0);
      noTone(BUZZER_PIN);
      delay(200);
    }
  }
  else {
    digitalWrite(YESIL_LED_PIN, 1);
    digitalWrite(KIRMIZI_LED_PIN, 0);
    noTone(BUZZER_PIN);
  }
}
