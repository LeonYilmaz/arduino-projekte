//infrarot sensor
void setup()
{
  Serial.begin(9600);
  pinMode (2, INPUT);
  pinMode (13, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (6, OUTPUT);
}
void loop()
{
  Serial.println(digitalRead(2));
  delay(500);
  if(digitalRead (2)== 1)
  {
    digitalWrite(13, HIGH);
    digitalWrite (6,HIGH);
  }
  else
  {
    digitalWrite (13, LOW); 
     digitalWrite (6,LOW);
  }
}