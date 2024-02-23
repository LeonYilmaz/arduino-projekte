#include <Servo.h>              //libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define GAS A0                  //zuwesung aller pins
#define LDR A1
#define TEMP A2
#define MOIS A3
#define INFR A5
#define BUZZ 3
#define BTN 4
#define BTN2 8
#define LED 5
#define LED2 13
#define FAN 6
#define FAN2 7
#define SERVO 9
#define SERVO2 10
#define REL 12

float lorawanZeit = 30;


int Hellichkeit;
int feuchte;
int Gase;
int IRS;
float temperature = 0;
char buffer[20] = "";                 //buffer für messung der temperatur

int BtnVal ;
int BtnVal2 ;
int lastBtnVal ;
int klingel = 0;

int MenuRotation = 0;
int taster = 0;
int i = 0;
unsigned long lastDebounceTime = 0;   
unsigned long debounceDelay = 50;

float lorawanZeiger = millis();

char feuchteStr[10];             //hex-Strings für zusammenstellen der payload initialisiert
char GasStr[10];
char HellichkeitStr[10];
char temperaturStr[10];
char klingelString[ 10 ];
char Payload [100];

LiquidCrystal_I2C mylcd(0x27, 16, 2);       //initialisieren des OneWire bus /essentiell für den temperaturen messer
OneWire oneWire(TEMP); 
DallasTemperature sensors(&oneWire); 

SoftwareSerial mySerial( 13,12 );

void setup() {
  mylcd.init();
  mylcd.backlight();

  pinMode(GAS, INPUT);
  pinMode(LDR, INPUT);
  pinMode(TEMP, INPUT);
  pinMode(MOIS, INPUT);
  pinMode(INFR, INPUT);
  pinMode(BTN, INPUT);
  pinMode(BTN2, INPUT);

  pinMode(BUZZ, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(FAN2, OUTPUT);
  pinMode(SERVO, OUTPUT);
  pinMode(SERVO2, OUTPUT);
  pinMode(REL, OUTPUT);

  mySerial.begin( 9600 );
  Serial.begin(9600); 
  sensors.begin(); 

  Serial.println( "Start" );
}
void lnclear()
{
  mylcd.setCursor(0, 1);
  mylcd.print("                ");
}

void messen()                                           //funktion zum messen aller werte
{
  feuchte = analogRead(A3);
  Hellichkeit = analogRead(A1);
  Gase = analogRead(A0);
  IRS = digitalRead(A5);
  sensors.requestTemperatures(); 
  temperature = sensors.getTempCByIndex(0);

}

void feuchtee()
{
  lnclear();
if(feuchte < 20)
{
  mylcd.setCursor (0, 0);
  mylcd.print ("Luftfeuchtigkeit:");
  mylcd.setCursor (0, 1);
  mylcd.print("trocken");
}
if(feuchte > 20 && feuchte < 700)
{
  mylcd.setCursor (0, 0);
  mylcd.print ("Luftfeuchtigkeit:");
  mylcd.setCursor (0, 1);
  mylcd.print("feucht");
}
if(feuchte > 700 && feuchte < 1020)
{
  mylcd.setCursor (0, 0);
  mylcd.print ("Luftfeuchtigkeit:");
  mylcd.setCursor (0, 1);
  mylcd.print("nass");
}
if(feuchte > 1020)
{ 
  mylcd.setCursor (0, 0);
  mylcd.print ("Luftfeuchtigkeit:");
  mylcd.setCursor (0, 1);
  mylcd.print("Unter Wasser?");
}
}


void loop()                             
{
  BtnVal2 = digitalRead(8);
  if (BtnVal2 == LOW)
  {
    digitalWrite(6, HIGH);
  }
  if (BtnVal2 == HIGH)
  {
    digitalWrite(6, LOW);
  } 

  messen();                               //werte messen, die später in der revolverschaltung ausgegeben werden
  BtnVal = digitalRead(BTN);              //maßnahmen gegen taster prallen

  int BtnVal = digitalRead(BTN);

 
if (BtnVal != lastBtnVal && millis() - lastDebounceTime > debounceDelay) 
{
  lastDebounceTime = millis(); 
  lastBtnVal = BtnVal;
  if (BtnVal == LOW) 
  {
      lnclear();
      MenuRotation++;
      taster = 0;
  }
}

if (MenuRotation >= 5)
{
  MenuRotation = 0;
}                                                           //

switch(MenuRotation){
  
  case 0:
    mylcd.setCursor(0, 0);
    mylcd.print("temperatur:    ");
    mylcd.setCursor(0, 1); 
    mylcd.print(dtostrf(temperature, 5, 2, buffer)); 
    mylcd.print(" Grad ");
    break;
  case 1:
    lnclear();
    mylcd.setCursor (0, 0);
    mylcd.print ("Luftreinheit:    ");
    mylcd.setCursor (0, 1);
    mylcd.print(Gase);
    break;
  case 2:
    lnclear();
    mylcd.setCursor (0, 0);
    mylcd.print ("Hellichkeit:    ");
    mylcd.setCursor (0, 1);
    mylcd.print(Hellichkeit);
    break;
  case 3:
    feuchtee();
    break;
  case 4:
    Serial.println(IRS);
    mylcd.setCursor (0, 0);
    mylcd.print ("IR strahlung:    ");
    mylcd.setCursor (0, 1);
    mylcd.print(IRS);
    break;

}

sprintf(feuchteStr, "%04X", feuchte);                 //verarbeitung der werte in 4 stelligen hex string
sprintf(GasStr, "%04X", Gase);
sprintf(HellichkeitStr, "%04X", Hellichkeit);
sprintf(temperaturStr, "%04X", (int)((temperature + 20) * 10));
sprintf( klingelString, "%02X", (int) klingel );


snprintf(Payload, sizeof(Payload), "%s%s%s%s%s", HellichkeitStr, feuchteStr, temperaturStr, GasStr, klingelString );    //zusammenstellen der payload
code haus fertig
Serial.println(Payload);

float aktZeiger = millis();

/*
Serial.print( aktZeiger );
Serial.print( " " );
Serial.print( lorawanZeiger );
*/

if( aktZeiger > lorawanZeiger ) {

  mySerial.print( Payload );

  lorawanZeiger = aktZeiger + ( lorawanZeit * 1000 );

  Serial.print( millis() );
  Serial.println( " Schuss") ;

}
Serial.println();


delay( 100 );

}