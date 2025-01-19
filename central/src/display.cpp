#include "./display.h"
#include "../lib/net/secrets.h"

#include <WiFi.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 27, 26, 25, 33, 32);

void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  lcd.setCursor(15, 1);
  lcd.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    lcd.setCursor(0, 1);
    lcd.println("Connection Err");
    return;
  }

  lcd.setCursor(8, 0);
  lcd.println(&timeinfo, "%H:%M:%S");

  lcd.setCursor(0, 1);
  lcd.println(&timeinfo, "%d/%m/%Y   %Z");
}

void beginWifi(){

  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print("WiFi ");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("Online");
  lcd.setCursor(0, 1);
  lcd.println("Updating time...");
}