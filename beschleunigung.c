//beschleunigung
int ledPin = 5;
int inpin = 8;
int val;
void setup() {

  Serial.begin( 9600 );

  pinMode(ledPin , OUTPUT);
  pinMode(inpin , INPUT_PULLUP );
  
}

void loop() {
  
  int value;

  val = !digitalRead(inpin);

  if( val == HIGH ) { 
      
      for( value = 255; value > 0 ; value-- ) 
      {
        analogWrite( ledPin , value);
        delay(20);    
      }  
    }
    else 
    {
      digitalWrite( ledPin , HIGH );
    }
 }