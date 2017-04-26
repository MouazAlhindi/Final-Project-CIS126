#include <encode.h>
#include <Wire.h>

/*  Source Code for Arduino 2
 * This Arduino will be...
 * Reciving an encrypted message
 * Reciving an encryption key
 * encrypting and decrypting messages
 * sending an encrypted message back
 */

void receiveEvent(int y){
  while(Wire.available() > 1){
    byte x = Wire.read();
    Serial.println(x);
  }
}

void setup() {

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600);
}

void loop() {
 delay(100);

}
