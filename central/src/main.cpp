#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "../lib/net/secrets.h"

LiquidCrystal lcd(12, 27, 26, 25, 33, 32);

#include <Keypad.h>

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'x' },
  { '4', '5', '6', 'o' },
  { '7', '8', '9', '^' },
  { '<', '0', '>', 'v' }
};

uint8_t colPins[COLS] = { 18, 5, 4, 2 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 23, 22, 21, 19}; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0

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

void setup() {
  Serial.begin(115200);

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

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

unsigned long tempo = 0;
void loop() {
  if (millis()-tempo>250){
    printLocalTime();
    tempo = millis();
  }

  char key = keypad.getKey();

  if (key != NO_KEY){  
    Serial.println(key);
  }

}
