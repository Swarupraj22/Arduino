void setup() {
  Serial.begin(115200);
  pinMode(32, INPUT);   // LDR sensor input
  pinMode(13, OUTPUT);  // LED output
}

void loop() {
  int ldrValue = analogRead(32);  // Read LDR (0–4095 on ESP32)
  Serial.println(ldrValue);

  int threshold = 2000;  // Adjust this based on your environment

  // Reverse the output logic
  if (ldrValue > threshold) {
    // Bright → LED OFF
    digitalWrite(13, HIGH);
  } else {
    // Dark → LED ON
    digitalWrite(13, LOW);
  }

  delay(200);
}

// void setup() {
//   Serial.begin(115200);
//   pinMode(32, INPUT);   // LDR sensor input
//   pinMode(13, OUTPUT);  // LED output
// }

// void loop() {
//   int ldrValue = analogRead(32);  // Read LDR (0–4095)
//   Serial.println(ldrValue);

//   int threshold = 2000;  // Adjust this based on your environment

//   if (ldrValue > threshold) {
//     // Bright → LED OFF
//     digitalWrite(13, LOW);
//   } else {
//     // Dark → LED ON
//     digitalWrite(13, HIGH);
//   }

//   delay(200); // small delay for stability
// }