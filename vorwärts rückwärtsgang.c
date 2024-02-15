//vorwärts rückwärtsgang
int inpin = 3;
int inpin2 = 4; 
int val;
int val2;
void setup ()

{
pinMode (inpin, INPUT);
pinMode (inpin2, INPUT);
pinMode (7, OUTPUT); 
pinMode (6, OUTPUT);
}

void loop()
{
  val = digitalRead(inpin);
  val2 = digitalRead(inpin2);
  if(val == LOW)
  {
    digitalWrite(6, HIGH);
    delay(1000);
    digitalWrite(6,LOW);
  }
  if(val2 == LOW)
  {
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
  }
}