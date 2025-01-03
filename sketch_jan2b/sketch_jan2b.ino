#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();  // Erstellen eines Display-Objekts

void setup() {
  Serial.begin(115200);
  Serial.println("START ...");
  Serial.println("TFT_SCLK");
  Serial.println(TFT_SCLK);
  tft.init();
  tft.setRotation(1);  // Rotation: 0-3 für verschiedene Ausrichtungen
  tft.fillScreen(TFT_BLACK);
  tft.drawCircle(64, 64, 30, TFT_RED);  // Zeichnet einen roten Kreis
}

void loop() {
  // Hier kann weitere Logik hinzugefügt werden
}
