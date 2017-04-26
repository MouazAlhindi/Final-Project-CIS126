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
int encryptionKey;
char encryptedMessage[140];
char decryptedMessage[140];
byte x = 1;
boolean valid = false;  //boolean for validity
String userID[] = {"Alpha", "Bravo", "Charlie", "Delta", "Echo" };  
String messageInput;  //user input

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

void validateUser(String x){
  
  Serial.println("Validating User....");
  
  for(int i = 0; i < sizeof(userID); i++){
      if(userID[i].equals(x)){
        valid = true;
        Serial.println("User Validation Completed");
      }
  }
  
  if(valid == false){
       Serial.println("User Validation Failed. Try Again!");
  }
}


void sendEncryptedMessage(String s){

  s.toUpperCase();

  //Encrypts the Data
  if(Serial.available() > 0 && valid){
    messageInput = Serial.readString();
    messageI
    
    byte x = Serial.read();
    Wire.beginTransmission(8); // transmit to device #8
    
    
    byte c = encode(x, encryptionKey);  // sends one byte and encrypts it
    //Wire.endTransmission();    // stop transmitting
  }
}




//Loop Method
void loop() {

  //Validating the user
  if(valid == false && Serial.available() > 0){
    String user = Serial.readString();
    validateUser(user);
  }

  //Send the Data
  if(Serial.available() > 0 && valid){
    byte x = Serial.read();
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(x);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
}
