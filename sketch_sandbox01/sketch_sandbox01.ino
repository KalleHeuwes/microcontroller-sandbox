#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the TFT_eSPI class
int xC = 150;

void setup() {
  Serial.begin(115200);
  Serial.println("Sandbox Start ...");
  tft.begin(); // Initialize the TFT display
  tft.setRotation(1); // Set the display rotation to landscape
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color
}

void loop() {
  tft.fillScreen(TFT_BLACK);
  xC = xC + 5; // Center x-coordinate of the arc
  int yC = 120; // Center y-coordinate of the arc
  int rad = 100; // Radius of the arc
  int ir = 80; // Radius of the arc
  uint32_t startAngle = 0; // Starting angle of the arc (in degrees)
  uint32_t endAngle = 210; // Ending angle of the arc (in degrees)
  uint32_t fg_color = TFT_RED; // Color of the arc
  uint32_t bg_color = TFT_BLUE; // Color of the arc

  //tft.drawArc(int32_t x, int32_t y, int32_t r, int32_t ir, uint32_t startAngle, uint32_t endAngle, uint32_t fg_color, uint32_t bg_color)
  tft.drawArc(xC, yC, rad, ir, startAngle, endAngle, fg_color, bg_color); // Draw the arc

  delay(1000); // Wait for 1 second
}