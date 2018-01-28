#include <Wire.h>
#include <OLED.h>
#include <ESP8266WiFi.h>
#include <string.h>

//WIFI_Kit_8's OLED connection:
//SDA -- GPIO4 -- D2
//SCL -- GPIO5 -- D1
//RST -- GPIO16 -- D0

#define RST_OLED 16
#define LINES 4
OLED display(4, 5);
int scan_results = 0;

// If you bought WIFI Kit 8 before 2017-8-20, you may try this initial
//#define RST_OLED D2
//OLED display(SDA, SCL);

void setup() {
  WiFi.mode(WIFI_STA);
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, LOW);   // turn D2 low to reset OLED
  delay(50);
  digitalWrite(RST_OLED, HIGH);    // while OLED is running, must set D2 in high

  display.begin();
  display.clear();

  WiFi.scanNetworksAsync(cb_scan, false);
  while (1) {
    display.print("Scanning", 0, 0);

    for (int i = 0; i < LINES; i++) {
      int j = i ? 0 : 8; // strlen("Scanning")
      for (; j < 16; j++) {
        display.print(".", i, j);
        if (scan_results)
          return;
        delay(50);
      }
    }
    display.clear();
  }
}

void loop() {
  if (scan_results) {
    print_ssid(scan_results);
    WiFi.scanNetworksAsync(cb_scan, false);
  }
}

void cb_scan(int n)
{
  scan_results = n;
}

void print_ssid(int n)
{
  scan_results = 0;
  display.clear();

  int i = 0;
  do {
    int line = 0;
    display.clear();
    switch(n-i) {
      default:
        display.print((char*)WiFi.SSID(i+line).c_str(), line);
        line++;
      case 3:
        display.print((char*)WiFi.SSID(i+line).c_str(), line);
        line++;
      case 2:
        display.print((char*)WiFi.SSID(i+line).c_str(), line);
        line++;
      case 1:
        display.print((char*)WiFi.SSID(i+line).c_str(), line);
        line++;
    }
    delay(1000);
    i++;
  } while (n-i >= LINES);

  delay(10000);
}
