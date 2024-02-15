//servo 90
#include <Servo.h>
int pos = 0;
int val = 0;
int inpin = 4;
Servo myservo; 
void setup ()
{
  myservo.attach (9);
  pinMode (inpin, INPUT);

}
void loop ()
{
  val = digitalRead (inpin);
  if (val== LOW){
    for(pos = 0; pos <=90; pos++ )
    {
      myservo.write (pos);
      delay(15);
    }
  }
}