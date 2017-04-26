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

void validateUser(String x){
  for(int i = 0; i < sizeof(userID); i++){
      if(userID[i].equals(x)){
        valid = true;
      }
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

void receiveEvent(int howMany) {
  
  while (1 < Wire.available()) { // loop through all but the last
    if(valid == false){
      char h = Wire.read();
      Serial.println("Incoming Message: WARNING! USER MUST BE VALIDATED");
    } else {
      char c = Wire.read(); // receive byte as a character
      Serial.print(c);         // print the character
    }
  }
    int x = Wire.read();    // receive byte as an integer
    Serial.println(x);         // print the integer
}
