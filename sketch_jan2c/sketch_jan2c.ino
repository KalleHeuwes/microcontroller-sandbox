#include "SPI.h"
#include "TFT_eSPI.h"
#include <ESP8266WiFi.h>
#include "time.h"

int clock_center_y = 120;
int clock_center_x = 120;

int y, x, y_1, x_1;
int minutes = 0;
int hours = 0;
int seconds = 0;

const char* ssid = "Casa Heuwes";        // Eigene SSID eingeben
const char* password = "HeuwesNet0808#!";   // Eigenes Passwort eingeben

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;

double pi = 3.14159;
TFT_eSPI tft = TFT_eSPI();
time_t now;
tm tm;

void setup() { 
  Serial.begin(115200);
  Serial.println("Verbinde WLAN ...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("... erledigt");
  configTime(3600, 3600, ntpServer);
  struct tm tm;
  if(!getLocalTime(&tm)){
    return;
  }
  Serial.println("... Zeit geholt");
  seconds = tm.tm_sec;
  minutes = tm.tm_min;
  hours = tm.tm_hour;
  
  Serial.println(tft.width());
  tft.init();
  Serial.println("... tft.init erledigt");
  tft.fillScreen(0x000000);
  drawClockFace();
  Serial.println("Hallo, Welt !");
} 

void drawClockFace(){
  for (int i=1;i<12;i++){
   y= (120*cos(pi-(2*pi)/12*i))+clock_center_y;
   x =(120*sin(pi-(2*pi)/12*i))+clock_center_x;
   y_1= (110*cos(pi-(2*pi)/12*i))+clock_center_y;
   x_1 =(110*sin(pi-(2*pi)/12*i))+clock_center_x;
   tft.drawLine(x_1,y_1,x,y,TFT_WHITE);
  }
 
  tft.drawCircle(26*sin(pi)+clock_center_x, (26*cos(pi))+clock_center_y, 6, TFT_BLACK);
  tft.fillCircle(26*sin(pi)+clock_center_x, (26*cos(pi))+clock_center_y, 5, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(clock_center_x-10, 0);
  tft.println(F("12"));
}

void redrawClockFaceElements(){
    tft.drawCircle(clock_center_x, clock_center_y,3, TFT_WHITE);
    tft.fillCircle(clock_center_x, clock_center_y,3, TFT_WHITE);
    tft.setCursor(clock_center_x-10, 0);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.println(F("12"));
}

void drawHour(int hour, int minute, int mode){
  int l = 70;
   y= (l*cos(pi-(2*pi)/12*hour-(2*PI)/720*minute))+clock_center_y;
   x =(l*sin(pi-(2*pi)/12*hour-(2*PI)/720*minute))+clock_center_x;
   if (mode==1){
    tft.drawLine(clock_center_x,clock_center_y,x,y,TFT_ORANGE);
    tft.drawLine(clock_center_x+1,clock_center_y+1,x+1,y+1,TFT_ORANGE);
   }
   else{
    tft.drawLine(clock_center_x,clock_center_y,x,y,TFT_BLACK);
    tft.drawLine(clock_center_x+1,clock_center_y+1,x+1,y+1,TFT_BLACK);
   }  
}

void drawMinute(int minute, int mode){
  int l  = 110;
   y= (l*cos(pi-(2*pi)/60*minute))+clock_center_y;
   x =(l*sin(pi-(2*pi)/60*minute))+clock_center_x;
   if (mode==1)tft.drawLine(clock_center_x,clock_center_y,x,y,TFT_CYAN); 
   else tft.drawLine(clock_center_x,clock_center_y,x,y,TFT_BLACK);
}

void drawSecond(int second, int mode){
  int l = 100;
  double rad = pi-(2*pi)/60*second;
  y= (l*cos(rad))+clock_center_y;
  x =(l*sin(rad))+clock_center_x;
  if (mode==1) tft.drawCircle(x, y, 3, TFT_WHITE);
  else tft.drawCircle(x, y, 3, TFT_BLACK);
}

void date() {
  struct tm tm;
  while(!getLocalTime(&tm)){
    return;
  }
  if((tm.tm_hour == 3 || tm.tm_hour == 9 || tm.tm_hour == 15 || tm.tm_hour == 21) && (tm.tm_min == 0 && tm.tm_sec <= 3)) tft.fillScreen(0x000000);
  if((tm.tm_hour > 3 && tm.tm_hour < 9) || (tm.tm_hour > 15 && tm.tm_hour < 21)) { //datum oben -> zeiger unten
    tft.fillRect(70,90,110,25,TFT_BLACK);
    tft.setCursor(60,97);
    tft.setTextColor(TFT_PINK);
    tft.setTextSize(2);
    tft.printf("%02d.%02d.%04d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  }
  else {
    tft.fillRect(70,130,110,25,TFT_BLACK);
    tft.setCursor(60,137);
    tft.setTextColor(TFT_PINK);
    tft.setTextSize(2);
    tft.printf("%02d.%02d.%04d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  }
}
 
 void loop() {
  Serial.println("...Schleife");
  struct tm tm;
  while(!getLocalTime(&tm)){
    return;
  }
  drawSecond(seconds,0);
  drawMinute(minutes,0);
  drawHour(hours,minutes,0);
  seconds = tm.tm_sec;
  minutes = tm.tm_min;
  hours = tm.tm_hour;
  drawSecond(seconds,1);
  drawMinute(minutes,1);
  drawHour(hours,minutes,1);
  redrawClockFaceElements();
  date();
  delay(500);
}
