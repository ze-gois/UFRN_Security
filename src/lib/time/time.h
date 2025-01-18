#pragma once

#include <NTPClient.h>
#include <WiFiUdp.h>

#define ntp_url "pool.ntp.org"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntp_url);