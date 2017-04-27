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
int charCount = 64;
char encryptedMessage[64];
char decryptedMessage[64];
boolean valid = false;  //boolean for validity
String userID[] = {"Alpha", "Bravo", "Charlie", "Delta", "Echo" };
String currentUser;
int encryptionKey; 
String messageInput;  //user input

//SEND METHODS

void setEncryptionKey(){

  char charE = currentUser.charAt(0);
  
  switch(charE){
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
    case 'E':
       encryptionKey = 5;
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
        currentUser = userID[i];
        setEncryptionKey();
        Serial.println("User Validation Completed");
      }
  }
  if(valid == false){
       Serial.println("User Validation Failed. Try Again!");
  }
}

void clearMessages(){
  encryptedMessage[64];
  decryptedMessage[64];
  
}

void sendEncryptedMessage(String s){
  s.toUpperCase();
  clearMessages();
  for (int i = 0; i < s.length(); i++){
       byte x = (byte)(s.charAt(i)); 
       encryptedMessage[i] = (char)encode(x, encryptionKey);  //adds encrypted byte to encrypted message  
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
    String message = Serial.readString();
    sendEncryptedMessage(message);
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(encryptedMessage);              // sends one byte
    Wire.endTransmission();    // stop transmitting
  }
}
