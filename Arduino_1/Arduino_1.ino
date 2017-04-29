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
char encryptedMessage[64]; //char array that holds the encrypted message
char decryptedMessage[64]; //char array that hold the decrypted message
boolean valid = false;  //boolean for user validity
String userID[] = {"Alpha", "Bravo", "Charlie", "Delta", "Echo" }; //list of verified users
String currentUser; // string that holds the current user
int encryptionKey; // holds the encryption key
String messageInput;  //user input
int delayLED = 100;  //delay for blinking LED

//SEND METHODS

/*SET ENCRYPTION KEY
 * Logic that determines the encryption key based off the userID
 */
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

/* VALIDATE USER FUNCTION
 * Takes a string parameter that compares the string
 * to the registered users in the system.
 * Logic to validate the users
 */
void validateUser(String x){
 
  Serial.println("Validating User....");
  
  for(int i = 0; i < sizeof(userID); i++){
      if(userID[i].equals(x)){
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
        valid = true;
        currentUser = userID[i];
        setEncryptionKey();
        Serial.println("User Validation Completed");
      }
  }
  if(valid == false){
       digitalWrite(13, LOW);
       Serial.println("User Validation Failed. Try Again!");
       blinkNotValid();
  }
}

/* Clear Message Function
 * Logic that clears the chars that are already in the
 * arrays that hold the encrypted and decrepted string
 * from the previous message and set each char to null
 */
void clearMessage(){
  for( int i = 0; i < sizeof(encryptedMessage);  ++i ){
   encryptedMessage[i] = (char)0;
   decryptedMessage[i] = (char)0;
  }
}

/* Send Encrypted message
 *  function will turn all chars in desired message to capital letters
 *  clear the arrays that hold the message and encrypted message
 *  loop through each char in the string and encrypt the message
 *  store encrypted message in the encryptedMessage[]
 */
void setEncryptedMessage(String s){
  s.toUpperCase();
  clearMessage();
  for (int i = 0; i < s.length(); i++){
       byte x = (byte)(s.charAt(i)); 
       encryptedMessage[i] = (char)encode(x, encryptionKey);  //adds encrypted byte to encrypted message  
    }
  }

void blinkMessageRecieved(){
  int count = 4;

  while(count > 0){
    delay(delayLED);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    delay(delayLED);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    count--;
  }
  
  digitalWrite(13, HIGH);
}

void blinkSend(){
  int count = 4;
     
     //while loop for blinking green LED
     while(count > 0){
      delay(delayLED);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      delay(delayLED);
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      count--;
     }
}

void blinkNotValid(){
  int count = 3;

  while(count > 0){
    delay(delayLED);
    digitalWrite(12, LOW);
    delay(delayLED);
    digitalWrite(12, HIGH);
    count--;
  }
}

//Setup method
void setup() {
  Wire.begin();
  Serial.begin(9600);
  

  pinMode(13, OUTPUT);  //green LED
  pinMode(12, OUTPUT);  //red LED
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
}

//Main Loop Method
void loop() {

  //Validating the user
  if(valid == false && Serial.available() > 0){
    String user = Serial.readString();
    validateUser(user);
  }

  //Send the Data
  if(Serial.available() > 0 && valid){    
    
    String message = Serial.readString(); // reads string that is inputed by the user
    setEncryptedMessage(message); // method to encrypt the method
    Wire.beginTransmission(8); // transmit to device #8 (Arduino 2)
    Wire.write(encryptedMessage);   // sends one char/byte at a time
    Serial.println("Message Sending....");
    Wire.endTransmission();    // stop transmitting

    blinkSend();

    Wire.requestFrom(8, 1);
    int slaveKey = (int)Wire.read();

    if(slaveKey == encryptionKey){
      Serial.println("Message Recieved by Slave Device");
      Serial.println("value of Slave device encryption Key: " + (String)slaveKey);
      blinkMessageRecieved();
    } else {
      Serial.println("WARNING: Message Recieved by slave Device");
      Serial.println("Slave device has wrong encryption key");
      Serial.println("Slave Device may not be validated yet");
      digitalWrite(13, LOW);
      blinkNotValid();
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
  }
}
