#include <encode.h>
#include <Wire.h>

/*  Source Code for Arduino 2
 * This Arduino will be...
 * Reciving an encrypted message
 * Reciving an encryption key
 * encrypting and decrypting messages
 * sending an encrypted message back
 */

//VARS
char message[64];
char encryptedMessage[64];
int encryptionKey;
boolean valid = false;
String userID[] = {"Alpha", "Bravo", "Charlie", "Delta", "Echo" };
String currentUser;

//SET ENCRYPTION KEY
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

//VALIDATE USER FUNCTION
void validateUser(String x){
  Serial.println("Validating User...");
  for(int i = 0; i < sizeof(userID); i++){
      if(userID[i].equals(x)){
        valid = true;
        currentUser = userID[i];
        Serial.println("User Validation Complete");
      }
  }

  if(valid == false){
    Serial.println("User Validation Failed. Try Again!");
  }
}

//FUNCTION USED TO SET THE ENCRYPTION KEY
void setEncryptionKey(int x){
  encryptionKey = x;
}

void clearMessages(){
  message[64];
  encryptedMessage[64];
}

//FUNCTION THAT DECODES AN ENCRYPTED MESSAGE
void decodeMessage(){
  String mess = encryptedMessage;
  char decr[mess.length()];
  for(int i = 0; i < mess.length(); i++){
    decr[i] = mess.charAt(i);
    message[i] = decrypt(decr[i], encryptionKey);
  }
}

//FUNCTION THAT ENCODES A REGULAR MESSAGE
void encryptMessage(){
  String mess = message;
  char encr[mess.length()];
  for(int i = 0; i < mess.length(); i++){
    encr[i] = mess.charAt(i);
    encryptedMessage[i] = encode(encr[i], encryptionKey);
  }
}

void sendMessage(){
  
}

//SETUP FUNCTION
void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

//MAIN LOOP FUNCTION
void loop() {
  delay(100);
  if(Serial.available() > 0){
      String uID = Serial.readString();
      validateUser(uID);
  }
}

//RECIEVE EVENT FUNCTION
//IS CALLED EVERYTIME THE MASTER SENDER
//TRYS TO COMMUNICATE WITH THE 
void receiveEvent(int howMany) {
  if(valid == false){
      Serial.println("Incoming Message: WARNING! USER MUST BE VALIDATED");
  }

  int count = 0;
  
  while (0 < Wire.available() && valid) { // loop through all but the last
      
      char c = Wire.read(); // receive byte as a character
      encryptedMessage[count] = c;
      count++;
  }

  Serial.println("Message Recvied");
  Serial.println("Encrypted Format: ");
  Serial.print(encryptedMessage);
  Serial.println("Decrypted Format: ");
  Serial.print(message);
  
}
