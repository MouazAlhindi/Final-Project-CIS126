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
char message[64]; // char array that holds decrypted message
char encryptedMessage[64]; //char array that hold encrypted message
int encryptionKey; // Encryption key that is a factor to the encryption logic
boolean valid = false; // user validation of hardware
int delayLED = 500;  //delay for blinking LED 


/* List of user IDs. 
 * Each user id holds a diffrent encryption key
 * This will improve security if one of the user ID is compramised
 * IMPORTANT NOTE: Both arduinos should use the same user ID to beable to communicate
 */
String userID[] = {"Alpha", "Bravo", "Charlie", "Delta", "Echo" };
String currentUser; // String that holds the current User ID

/*SET ENCRYPTION KEY
 * Logic that determines the encryption key based off the userID
 */
void setEncryptionKey(){

  char charE = currentUser.charAt(0); // char that holds the first char of the current user
  
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

void blinkNotValid(){
  int count = 4;

  while(count > 0){
    digitalWrite(12, LOW);
    delay(delayLED);
    digitalWrite(12, HIGH);
    count--;
  }
}

/* VALIDATE USER FUNCTION
 * Takes a string parameter that compares the string
 * to the registered users in the system.
 * Logic to validate the users
 */
void validateUser(String x){
  Serial.println("Validating User...");
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
    blinkNotValid();
    Serial.println("User Validation Failed. Try Again!");
  }
}

/* Clear Message Function
 * Logic that clears the chars that are already in the
 * arrays that hold the encrypted and decrepted string
 * from the previous message and set each char to null
 */
void clearMessages(){
  for( int i = 0; i < sizeof(encryptedMessage);  ++i ){
   encryptedMessage[i] = (char)0;
   message[i] = (char)0;
  }
}

/* FUNCTION THAT DECODES AN ENCRYPTED MESSAGE
 * Function that uses the library File encode.h
 * Will use the externed method decrypt(char, Key);
 */
void decodeMessage(){
  String mess = encryptedMessage;
  char decr[mess.length()];
  for(int i = 0; i < mess.length(); i++){
    decr[i] = mess.charAt(i);
    message[i] = decrypt(decr[i], encryptionKey);
  }
}

/* FUNCTION THAT ENCODES A REGULAR MESSAGE
 * function that uses the libaray file encode.h
 * will use the externed method encode(char, key);
 */
void encryptMessage(){
  String mess = message;
  char encr[mess.length()];
  for(int i = 0; i < mess.length(); i++){
    encr[i] = mess.charAt(i);
    encryptedMessage[i] = encode(encr[i], encryptionKey);
  }
}

void blinkRecieve(){
    int count = 6;
     
     //while loop for blinking green LED
     while(count > 0 && valid){
      delay(delayLED);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      delay(delayLED);
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      count--;
     }  
}

//SETUP FUNCTION
void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);

  blinkNotValid();
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

  if(valid == true){
    clearMessages(); //Clear char arrays that hold 
    int count = 0; //Var for loop logic
    Serial.println("Receiving Message");
    while (0 < Wire.available() && valid) { // loop through all but the last
      
      char c = Wire.read(); // receive byte as a character
      encryptedMessage[count] = c; // save the received encrypted chars in array
      count++; //increment count var
    }
  
    blinkRecieve();
    decodeMessage(); //Call method to decode the recieved incryption String
    //Print format
    Serial.println("Message Recvied");
    Serial.println("Encrypted Format: " + (String)(encryptedMessage));
    Serial.println("Decrypted Format: " + (String)(message));
  } else {
      Serial.println("Incoming Message: WARNING! USER MUST BE VALIDATED");
      blinkNotValid();
      clearMessages();
      int i = 0;
      while(0 < Wire.available()){
        char c = Wire.read();
        encryptedMessage[i];
        i++;
      }
  }
}
