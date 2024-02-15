//gaspedal//
int ledPin = 5;
int inpin = 1;
int val;
void setup() {
  pinMode(ledPin , OUTPUT);
  pinMode(inpin , INPUT);
  
}

void loop() {
val = digitalRead(inpin);
if(val== LOW)
{
digitalWrite(ledPin , LOW);
}
else
{
digitalWrite(ledPin , HIGH);
}

}
