#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const int relayPins[] = {13, 12, 11, 10};  // Pins for the 4-channel relay module
const int targetHour = 21;                 // Define the target hour for relay activation
const int targetMinute = 43;               // Define the target minute for relay activation
const int targetSecond = 0;               // Define the target second for relay activation
const unsigned long relayActivationDuration = 10 * 1000;  // Define the duration in milliseconds for which relays are closed

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time to default");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);
  }
}

void loop() {
  DateTime now = rtc.now();

  // Print current time for debugging
  Serial.print("Current Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());

  // Check if it's the target activation time
  if (now.hour() == targetHour && now.minute() == targetMinute && now.second() == targetSecond) {
    closeAllRelays();
  }

  delay(1000);
}

void closeAllRelays() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(relayPins[i], LOW);
  }
  delay(relayActivationDuration);
  for (int i = 0; i < 4; i++) {
    digitalWrite(relayPins[i], HIGH);
  }
}