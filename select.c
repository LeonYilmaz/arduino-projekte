#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27,16,2);
int inpin = 7;
int inpin2 = 8;
int val;
int val2;
int ledpin = 4;
int ledpin2 = 5;
void setup ()
{
  lcd.init();
  lcd.backlight();
  pinMode (inpin, INPUT); // 
  pinMode (inpin2, INPUT);
  pinMode (ledpin, OUTPUT);
  pinMode (ledpin2, OUTPUT);
  lcd.setCursor (2,0);
  lcd.print ("Select light");
  lcd.setCursor (1,1);
  lcd.print ("Yellow   White");


}
void clear()
  {
    lcd.setCursor (1,0);
    lcd.print("               ");
    lcd.setCursor (1,1);
    lcd.print("               ");
  }
  void reset()
  {
    delay (5000);
     lcd.setCursor (2,0);
  lcd.print ("Select light");
  lcd.setCursor (1,1);
  lcd.print ("Yellow   White");
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);

  }
void loop()
{
  val = digitalRead (inpin);
  val2 = digitalRead (inpin2);
  if (val == LOW)
  {
    clear();
    digitalWrite (4, LOW);
    digitalWrite (5, HIGH);
    lcd.setCursor (2,0);
    lcd.print ("You Selected:");
    lcd.setCursor (1,1);
    lcd.print ("Yellow ");
    reset();
  }
  if (val2 == LOW)
  {
    clear();
    digitalWrite (5, LOW);
    digitalWrite (4, HIGH);
    lcd.setCursor (2,0);
    lcd.print ("You Selected:");
    lcd.setCursor (11,1);
    lcd.print ("White ");
    reset();

  }
  
}