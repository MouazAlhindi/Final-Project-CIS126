#include <encode.h>
extern "C" byte decrypt(byte, byte);

byte c;
byte d;
byte shift = 2;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


  while(Serial.available() > 0)
  {
      c = Serial.read();
      Serial.println((char)encode(c, shift));  
      Serial.println((char)decrypt((encode(c, shift)), shift));
    
  }
}
