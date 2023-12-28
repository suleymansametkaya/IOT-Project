#include <DHT.h>

#define DHTPIN 2     // DHT sensörünün bağlı olduğu pin
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Toprak nem sensörü pinini belirtin
int toprakNemPin = A5;

// MQ-135 hava kalite sensörü pinini belirtin
int havaKalitePin = A4;

// LDR sensörü pinini belirtin
int ldrPin = A3;

// Su seviye sensörü pinlerini belirtin
int suSeviyePin = A2;

void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  // Toprak nem sensöründen veri oku
  int toprakNemDegeri = analogRead(toprakNemPin);

  // Toprak nem değerini 0 ile 100 arasına ölçeklendir
  int scaledNemDegeri = map(toprakNemDegeri, 0, 1023, 0, 100);

  // DHT sensöründen sıcaklık ve nem oku
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // MQ-135 hava kalite sensöründen veri oku
  int havaKaliteDegeri = analogRead(havaKalitePin);

  // LDR sensöründen ışık seviyesi oku
  int ldrDegeri = analogRead(ldrPin);

  // Su seviye sensörlerinden su seviyesi oku
  int suSeviyeDegeri = analogRead(suSeviyePin);

  // NodeMCU'ya nem, sıcaklık, hava kalite, ışık seviyesi ve su seviyesi değerlerini gönder
  Serial.print(scaledNemDegeri);
  Serial.print(",");
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(havaKaliteDegeri);
  Serial.print(",");
  Serial.print(ldrDegeri); // Ölçeklendirme olmadan LDR değerini kullan
  Serial.print(",");
  Serial.println(suSeviyeDegeri); // Ölçeklendirme olmadan su seviye değerini kullan

  delay(1000); // 1 saniye bekleme süresi (isteğe bağlı)
}
s