#include <encode.h>
#include <Wire.h>

/*  Source Code for Arduino 1
 * This Arduino will be...
 * Sending an encrypted message
 * Sending an encryption key
 * encrypting and decrypting messages
 * sending an encrypted message back
 */



//Variables
int reciverPin;
int senderPin;
int encryptionKey;
char encryptedMessage[140];
char decryptedMessage[140];
byte x = 1;


//SEND METHODS

void setEncryptionKey(char encrypt){
  switch(encrypt){
    case 'A':
       encryptionKey = 1;
       break;
    case 'B':
       encryptionKey = 2;
       break;
    case 'C':
       encryptionKey = 3;
       break;
    case 'D':
       encryptionKey = 4;
       break;
  }
}



//Setup method
void setup() {

  Wire.begin();
  
  Serial.begin(9600);

}

//Loop Method
void loop() {
  if(Serial.available() > 0){
    byte x = Serial.read();
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write("message received");        // sends five bytes
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
}
