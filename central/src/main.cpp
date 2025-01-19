#include <WiFi.h>
#include <Wire.h>
#include "./mqtt.h"
#include "../lib/net/secrets.h"
#include "./command.h"
#include "../lib/net/ntp.h"
#include "display.h"
#include "input.h"
#include "state.h"

void setup() {
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);

  new_once_command("Clear", "x",obliviate);
  new_command("Refresh time","",nullptr,printLocalTime,2000);
  new_command("Handle state","",nullptr,handleState,0);
  new_command("Senha 1", "1234",handleArm, nullptr,  0);

  Serial.begin(115200);

  beginWifi();
}

void loop() {
  char key = NO_KEY;

  if (key = assimilate() != NO_KEY ) {
    reflect();
  }

  review();

  patience();
}