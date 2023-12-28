#define BLYNK_TEMPLATE_ID "BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "BLYNK_TEMPLATE_NAME"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "BLYNK_TEMPLATE_AUTH";
char ssid[] = "ssid";
char pass[] = "pass";

#define VIRTUAL_BUTTON_PIN V2
#define RELAY_PIN D3

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Röle pinini çıkış olarak ayarla
  pinMode(RELAY_PIN, OUTPUT);

  // Röleyi başlangıçta kapalı konumda bırak
  digitalWrite(RELAY_PIN, LOW);

  // Sanal butonun durumunu takip et
  Blynk.virtualWrite(VIRTUAL_BUTTON_PIN, 0);

  // Sanal butona bir olay dinleyici ekleyin
  Blynk.syncVirtual(VIRTUAL_BUTTON_PIN);
}

void loop()
{
  Blynk.run();

  // Arduino'dan gelen veriyi oku
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int commaIndex1 = data.indexOf(',');
    int commaIndex2 = data.indexOf(',', commaIndex1 + 1);
    int commaIndex3 = data.indexOf(',', commaIndex2 + 1);
    int commaIndex4 = data.indexOf(',', commaIndex3 + 1);
    int commaIndex5 = data.lastIndexOf(',');

    String toprakNem = data.substring(0, commaIndex1);
    String havaNem = data.substring(commaIndex1 + 1, commaIndex2);
    String sicaklik = data.substring(commaIndex2 + 1, commaIndex3);
    String havaKalite = data.substring(commaIndex3 + 1, commaIndex4);
    String isikSeviyesi = data.substring(commaIndex4 + 1, commaIndex5);
    String suSeviye = data.substring(commaIndex5 + 1);

    // Blynk uygulamasına nem, sıcaklık, hava kalite, ışık seviyesi ve su seviyesi değerlerini gönder
    Blynk.virtualWrite(V3, toprakNem.toInt());
    Blynk.virtualWrite(V1, havaNem.toFloat());
    Blynk.virtualWrite(V0, sicaklik.toFloat());
    Blynk.virtualWrite(V4, havaKalite.toInt());
    Blynk.virtualWrite(V5, isikSeviyesi.toInt());
    Blynk.virtualWrite(V6, suSeviye.toInt());
  }
}

// Sanal buton durumu değiştiğinde çağrılır
BLYNK_WRITE(VIRTUAL_BUTTON_PIN) {
  int buttonState = param.asInt();

  if (buttonState == HIGH) {
    // Sanal buton açıkken röleyi aktifleştir (su pompasını aç)
    digitalWrite(RELAY_PIN, LOW);
  } else {
    // Sanal buton kapalıyken röleyi devre dışı bırak (su pompasını kapat)
    digitalWrite(RELAY_PIN, HIGH);
  }
}