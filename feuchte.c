//feuchte
int val;
void setup ()
{
Serial.begin(9600);
}

void loop()
{
val = analogRead(5);
Serial.print("Moisture is ");
if(val < 20)
{
  Serial.print("dry");
}
if(val > 20 && val < 999)
{
  Serial.print("moist");
}
if(val > 999)
{
  Serial.print("wet");
}
Serial.println();
delay(333);
}