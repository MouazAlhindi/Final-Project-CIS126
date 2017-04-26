#include <encode.h>
#include <Wire.h>

/*  Source Code for Arduino 2
 * This Arduino will be...
 * Reciving an encrypted message
 * Reciving an encryption key
 * encrypting and decrypting messages
 * sending an encrypted message back
 */

boolean valid = false;
String userID[] = {"Alpha", "Bravo", "Charlie", "Delta", "Echo" };

//VALIDATE USER FUNCTION
void validateUser(String x){
  for(int i = 0; i < sizeof(userID); i++){
      if(userID[i].equals(x)){
        valid = true;
      }
  }
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
//TRYS TO COMMUNIFCATE WITH THE 
void receiveEvent(int howMany) {
  if(valid == false){
      Serial.println("Incoming Message: WARNING! USER MUST BE VALIDATED");
  }
  while (1 < Wire.available()) { // loop through all but the last
      char c = Wire.read(); // receive byte as a character
      Serial.print(c);         // print the character
  }
  
}
