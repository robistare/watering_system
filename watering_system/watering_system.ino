// Define relay pins
const int relayPins[] = {13, 12, 11, 10}; // Relay 1 is pin 13, Relay 2 is pin 12, etc.

// Number of relays
const int numRelays = sizeof(relayPins) / sizeof(relayPins[0]);

void setup() {
  // Initialize relay pins as OUTPUT
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Turn off all relays initially
  }
}

void loop() {
  // Turn on each relay in sequence
  for (int i = 0; i < numRelays; i++) {
    digitalWrite(relayPins[i], LOW); // Turn on current relay
    delay(1000); // Wait for 1 second
    digitalWrite(relayPins[i], HIGH); // Turn off current relay
  }
  
  // Turn off all relays and wait for 2 seconds
  for (int i = 0; i < numRelays; i++) {
    digitalWrite(relayPins[i], HIGH); // Turn off all relays
  }
  delay(2000); // Wait for 2 seconds before restarting the cycle
}