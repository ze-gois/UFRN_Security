#include <WiFi.h>
#include <Wire.h>
#include "../lib/net/secrets.h"
#include "./command.h"
#include "../lib/net/ntp.h"
#include "display.h"
#include "input.h"
#include "state.h"

void setup() {
  // new_command("Turn ON/OFF", "w",toggle_on, loop_off);
  // new_once_command("Decrease Volume","-",decrease_volume);
  // new_once_command("Increase Volume","+",increase_volume);
  new_once_command("Clear", "x",obliviate);
  // new_command("Whatever","19812019p",secret,secret_loop);

  new_command("Refresh time","",nullptr,printLocalTime,2000);
  new_command("Keypad watcher","",nullptr,detect_key,0);
  new_command("Handle state","",nullptr,handleState,0);
  
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);

  Serial.begin(115200);

  beginWifi();
}

void loop() {
  // reflect();

  review();

  patience();
}
