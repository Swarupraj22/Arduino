void setup() {
pinMode(13, OUTPUT); // Set GPIO2 (built-in LED) as an output pin
}

// The loop function runs repeatedly
void loop() {
analogWrite(13,255);
delay(1000);
analogWrite(13,100);
delay(1000);
analogWrite(13,0);
delay(1000);
}