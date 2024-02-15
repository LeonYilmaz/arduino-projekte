int ledPin = 4;
void setup() {
  pinMode(ledPin , OUTPUT);
}

void loop() {
  for (int value = 0; value<255; value = value + 1)
  {
    analogWrite (ledPin , value);
    delay (100);
  }
   for (int value = 255; value>0; value = value - 1)
   {
   analogWrite (ledPin , value);
   delay (100);

   }

}
